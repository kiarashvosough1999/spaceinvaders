/*
 * custom_character_byte_code.h
 *
 *  Created on: Jan 27, 2023
 *      Author: kiarashvosough
 */

#ifndef INC_CUSTOM_CHARACTER_BYTE_CODE_H_
#define INC_CUSTOM_CHARACTER_BYTE_CODE_H_

typedef unsigned char byte;

byte senior_enemy_char[] = {
		  0x00,
		  0x04,
		  0x14,
		  0x0D,
		  0x0D,
		  0x14,
		  0x04,
		  0x00
};

byte mid_enemy_char[] = {
		  0x00,
		  0x00,
		  0x16,
		  0x0D,
		  0x0D,
		  0x16,
		  0x00,
		  0x00
};

byte junior_enemy_char[] = {
		  0x00,
		  0x00,
		  0x10,
		  0x0D,
		  0x0D,
		  0x10,
		  0x00,
		  0x00
};

byte player_char[] = {
		  0x00,
		  0x00,
		  0x12,
		  0x1D,
		  0x1D,
		  0x12,
		  0x00,
		  0x00
};


byte shot_char[] = {
  0x00,
  0x00,
  0x00,
  0x1F,
  0x1F,
  0x00,
  0x00,
  0x00
};
#endif /* INC_CUSTOM_CHARACTER_BYTE_CODE_H_ */
