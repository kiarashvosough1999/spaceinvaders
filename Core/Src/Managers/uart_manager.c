/*
 * uart_manager.c
 *
 *  Created on: Jan 20, 2023
 *      Author: kiarashvosough
 */


#include "Managers/uart_manager.h"
#include "string.h"

#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

void init_uart_manager(UART_Manager* manager, UART_HandleTypeDef* huart1) {
	UART_Manager new_manager = {
			huart1,
			""
	};

	*manager = new_manager;
}

void get_message_from_uart(UART_Manager* manager) {
	HAL_UART_Receive_IT(manager->huart1, manager->received_data, 10);
}

void send_message_through_uart(UART_Manager* manager, char message[10]) {
	HAL_UART_Transmit(manager->huart1, message, sizeof(message), 1000);
}

void send_message_through_uart_unlimited(UART_Manager* manager, char* message) {
	HAL_UART_Transmit(manager->huart1, message, NELEMS(message) * sizeof(char*), 1000);
}

void remove_all_chars(char* str, char c) {
    char *pr = str, *pw = str;
    while (*pr) {
        *pw = *pr++;
        pw += (*pw != c);
    }
    *pw = '\0';
}

void get_received_message(UART_Manager* manager, char message[10]) {
	char new_message[10];
	strcpy(new_message, manager->received_data);
//	remove_all_chars(new_message, '*');
	strcpy(message, new_message);
}






