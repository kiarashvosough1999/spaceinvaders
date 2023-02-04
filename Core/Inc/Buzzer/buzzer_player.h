/*
 * buzzer_player.h
 *
 *  Created on: Jan 13, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_BUZZER_PLAYER_H_
#define INC_BUZZER_PLAYER_H_

#include "main.h"

typedef enum {
	play, pause
} State;

typedef struct {
	TIM_HandleTypeDef *buzzerPwmTimer;
	int buzzerPwmChannel;
	State state;
	int volume;
	int current_tone_number;
	int notes_count;
	int current_tone_end;

} Buzzer_Player;

typedef struct {
    uint32_t frequency;
    int duration;
} Tone;

void init_buzzer_player(Buzzer_Player* player, TIM_HandleTypeDef *buzzerPwmTimer, int buzzerPwmChannel);

void buzzer_play(Buzzer_Player* player);

void buzzer_play_if_possible(Buzzer_Player* player);

void buzzer_change_volume(Buzzer_Player* player, int volume);

void buzzer_pause(Buzzer_Player* player);

void update_melody(Buzzer_Player* player);
#endif /* INC_BUZZER_PLAYER_H_ */
