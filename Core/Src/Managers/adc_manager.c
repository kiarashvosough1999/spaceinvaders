/*
 * adc_manager.c
 *
 *  Created on: Feb 4, 2023
 *      Author: kiarashvosough
 */


#include <Managers/adc_manager.h>

void init_adc_manager(ADC_Manager* manager, ADC_HandleTypeDef* hadc4) {
	ADC_Manager new_manager = {
			hadc4
	};
	 *manager = new_manager;
}

void adc_start(ADC_Manager* manager) {
	HAL_ADC_Start_IT(manager->hadc4);
}

void adc_stop(ADC_Manager* manager) {
	HAL_ADC_Stop_IT(manager->hadc4);
}

int adc_get_scaled_value(ADC_Manager* manager) {
	return HAL_ADC_GetValue(manager->hadc4) * 1000 / 4095 / 10;
}
