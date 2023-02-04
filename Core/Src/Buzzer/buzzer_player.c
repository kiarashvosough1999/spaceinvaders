/*
 * buzzer_player.c
 *
 *  Created on: Jan 13, 2023
 *      Author: kiarashvosough
 */


#include <Buzzer/buzzer_player.h>
#include <Buzzer/monarch_tones.h>

void init_buzzer_player(Buzzer_Player* player, TIM_HandleTypeDef *buzzerPwmTimer, int buzzerPwmChannel) {
	Buzzer_Player new_player = {
			buzzerPwmTimer,
			buzzerPwmChannel,
			play,
			100,
			0,
			sizeof(imperialmarch)/sizeof(imperialmarch[0]),
			0
	};
	*player = new_player;
	HAL_TIM_PWM_Start(buzzerPwmTimer, buzzerPwmChannel);
}

void buzzerChangeTone(Buzzer_Player* player, int freq) {

	if (freq == 0 || freq > 20000) {
		__HAL_TIM_SET_COMPARE(player->buzzerPwmTimer, player->buzzerPwmChannel, 0);
	} else {
		const uint32_t internalClockFreq = HAL_RCC_GetSysClockFreq();
		const uint32_t prescaler = 1 + internalClockFreq / freq / 60000;
		const uint32_t timerClock = internalClockFreq / prescaler;
		const uint32_t periodCycles = timerClock / freq;
		const uint32_t pulseWidth = player->volume * periodCycles / 1000 / 2;

		player->buzzerPwmTimer->Instance->PSC = prescaler - 1;
		player->buzzerPwmTimer->Instance->ARR = periodCycles - 1;
		player->buzzerPwmTimer->Instance->EGR = TIM_EGR_UG;

		__HAL_TIM_SET_COMPARE(player->buzzerPwmTimer, player->buzzerPwmChannel, pulseWidth);
	}
}

void update_melody(Buzzer_Player* player) {

    if ((HAL_GetTick() > player->current_tone_end) && (player->current_tone_number < player->notes_count)) {
    	buzzerChangeTone(player, 0);

    	const Tone active_tone = *(imperialmarch + player->current_tone_number);
    	int divider = active_tone.duration;
    	int noteDuration = 0;
    	const int tempo = 120;
    	const int wholenote = (60000 * 4) / tempo;

    	if (divider > 0) {
	      // regular note, just proceed
	      noteDuration = (wholenote) / divider;
	    } else if (divider < 0) {
	      // dotted notes are represented with negative durations!!
	      if (divider < 0) {
		      noteDuration = (wholenote) / (-divider);
	      } else {
		      noteDuration = (wholenote) / divider;
	      }
	      noteDuration *= 1.5; // increases the duration in half for dotted notes
	    }

        buzzerChangeTone(player, active_tone.frequency);
        player->current_tone_end = HAL_GetTick() + noteDuration;
        player->current_tone_number++;
    } else if (player->current_tone_number >= player->notes_count) {
    	// for reseting player when reaching end of notes
    	player->current_tone_end = 0;
    	player->current_tone_number = 0;
    }
}


void buzzer_play(Buzzer_Player* player) {
	player->state = play;
}

void buzzer_play_if_possible(Buzzer_Player* player) {
	if (player->state == play) {
		update_melody(player);
	} else {
		__HAL_TIM_SET_COMPARE(player->buzzerPwmTimer, player->buzzerPwmChannel, 0);
	}
}

void buzzer_change_volume(Buzzer_Player* player, int volume) {
	player->volume = volume;
}

void buzzer_pause(Buzzer_Player* player) {
	player->state = pause;
	__HAL_TIM_SET_COMPARE(player->buzzerPwmTimer, player->buzzerPwmChannel, 0);
}






