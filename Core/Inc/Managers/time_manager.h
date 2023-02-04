/*
 * time_manager.h
 *
 *  Created on: Jan 11, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_TIME_MANAGER_H_
#define INC_TIME_MANAGER_H_

#include "main.h"

typedef struct {
	RTC_HandleTypeDef* hrtc;
} Time_Manager;

void init_time_manager(Time_Manager* manager, RTC_HandleTypeDef* hrtc);

void get_system_date(Time_Manager* manager, RTC_DateTypeDef* date);

void get_system_time(Time_Manager* manager, RTC_TimeTypeDef* time);

#endif /* INC_TIME_MANAGER_H_ */
