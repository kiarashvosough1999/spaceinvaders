/*
 * adc_manager.h
 *
 *  Created on: Feb 4, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_MANAGERS_ADC_MANAGER_H_
#define INC_MANAGERS_ADC_MANAGER_H_

#include <main.h>

typedef struct {
	ADC_HandleTypeDef* hadc4;
} ADC_Manager;

void init_adc_manager(ADC_Manager* manager, ADC_HandleTypeDef* hadc4);

void adc_start(ADC_Manager* manager);

void adc_stop(ADC_Manager* manager);

int adc_get_scaled_value(ADC_Manager* manager);

#endif /* INC_MANAGERS_ADC_MANAGER_H_ */
