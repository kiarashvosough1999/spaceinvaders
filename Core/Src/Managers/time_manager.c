/*
 * time_manager.c
 *
 *  Created on: Jan 11, 2023
 *      Author: kiarashvosough
 */

#include "Managers/time_manager.h"

void init_system_time(Time_Manager* manager) {

	RTC_TimeTypeDef time;
	time.Hours = 12;
	time.Minutes = 0;
	time.Seconds = 0;

	HAL_RTC_SetTime(manager->hrtc, &time, RTC_FORMAT_BIN);

	RTC_DateTypeDef rtcDate;
	rtcDate.Year = 22;
	rtcDate.Month = 12;
	rtcDate.Date = 24;

	HAL_RTC_SetDate(manager->hrtc, &rtcDate, RTC_FORMAT_BIN);

	HAL_RTC_GetTime(manager->hrtc, &time, RTC_FORMAT_BIN);
	srand(time.Seconds);
}

void init_time_manager(Time_Manager* manager, RTC_HandleTypeDef* hrtc) {
	Time_Manager new_manager = {
			hrtc
	};
	*manager = new_manager;
	init_system_time(manager);
}

void get_system_date(Time_Manager* manager, RTC_DateTypeDef* date) {
	HAL_RTC_GetDate(manager->hrtc, date, RTC_FORMAT_BIN);
}

void get_system_time(Time_Manager* manager, RTC_TimeTypeDef* time) {
	HAL_RTC_GetTime(manager->hrtc, time, RTC_FORMAT_BIN);
}
