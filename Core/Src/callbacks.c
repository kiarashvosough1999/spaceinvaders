/*
 * callbacks.c
 *
 *  Created on: Dec 30, 2022
 *      Author: kiarashvosough
 */

#include "main.h"
#include <math.h>
#include "Managers/keypad_manager.h"
#include "game_configuration_state.h"
#include "Managers/time_manager.h"
#include "PageStuff/page_printer.h"
#include "app_action.h"
#include <Buzzer/buzzer_player.h>
#include "Managers/uart_manager.h"

extern App_Action action;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {

	if (hadc->Instance == ADC4) {
		buzzer_change_volume(action.player, adc_get_scaled_value(action.adc_manager));
		adc_start(action.adc_manager);
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM2) {
		HAL_TIM_Base_Stop_IT(htim);
		timer_2_did_triggered(&action, HAL_GetTick());
		HAL_TIM_Base_Start_IT(htim);
	} else if (htim->Instance == TIM3) {}
}

////////////////////////////////////////////////////////////////
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	extern TIM_HandleTypeDef htim2;
	HAL_TIM_Base_Stop_IT(&htim2);
	extern KeyPad_Manager keypad_manager;
    if (GPIO_Pin == GPIO_PIN_0) {
    	find_button(&keypad_manager, GPIO_Pin);
    } else if (GPIO_Pin == GPIO_PIN_1) {
    	find_button(&keypad_manager, GPIO_Pin);
    } else if (GPIO_Pin == GPIO_PIN_2) {
    	find_button(&keypad_manager, GPIO_Pin);
    } else if (GPIO_Pin == GPIO_PIN_3) {
    	find_button(&keypad_manager, GPIO_Pin);
    }
    HAL_TIM_Base_Start_IT(&htim2);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	extern App_Action action;

	if(huart->Instance == USART1) {
		uart_did_received_message(&action);
	}

	get_message_from_uart(action.uart_manager);
}






