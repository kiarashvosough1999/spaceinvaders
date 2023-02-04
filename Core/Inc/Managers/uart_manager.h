/*
 * uart_manager.h
 *
 *  Created on: Jan 20, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_UART_MANAGER_H_
#define INC_UART_MANAGER_H_

#include "main.h"

typedef struct {
	UART_HandleTypeDef* huart1;
	uint8_t received_data[10];

} UART_Manager;

void init_uart_manager(UART_Manager* manager, UART_HandleTypeDef* huart1);

void get_message_from_uart(UART_Manager* manager);

void send_message_through_uart(UART_Manager* manager, char message[10]);

void send_message_through_uart_unlimited(UART_Manager* manager, char* message);

void get_received_message(UART_Manager* manager, char message[10]);

#endif /* INC_UART_MANAGER_H_ */
