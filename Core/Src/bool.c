/*
 * bool.c
 *
 *  Created on: Jan 29, 2023
 *      Author: kiarashvosough
 */


#include <bool.h>
#include <stdlib.h>

bool random_bool() {
	int random_bool = rand() % 2;
	return random_bool == 1 ? true : false;
}
