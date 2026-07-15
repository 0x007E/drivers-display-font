/**
 * @file font.c
 * @brief Source file containing character lookup function for text rendering.
 * 
 * This file defines the font data table map function. The character table entries represent the bitmap patterns for individual characters, which are selected by the lookup function `font_get_bitmap()`. This function handles bounds checking and optional conversion of lowercase to uppercase letters when enabled, to optimize memory usage. The table and accessor function are designed for use in embedded systems with constrained storage, such as microcontrollers, where font data is read for graphical text displays.
 *
 * The configuration macros allow customization:
 * - `FONT_STORE_IN_EEPROM`: Store font table in EEPROM.
 * - `FONT_STORE_IN_PROGMEM`: Store font table in PROGMEM.
 * - `FONT_IGNORE_LOWER_CASE`: Do not store or display lowercase letters, saving memory.
 * - `FONT_ASCII_START_CHAR` / `FONT_ASCII_END_CHAR`: Configure supported character range.
 *
 * @author g.raf
 * @date 2026-07-15
 * @version 1.0 Release
 * @copyright
 * Copyright (c) 2026 g.raf
 * Released under the GPLv3 License. (see LICENSE in repository)
 *
 * @note This file is part of a larger project and subject to the license specified in the repository. For updates and the complete revision history, see the GitHub repository.
 *
 * @see https://github.com/0x007e/drivers-display-font "Drivers Display Font GitHub Repository"
 */

#include "font.h"

extern const uint8_t font_ascii_table[][FONT_WIDTH];

static unsigned char font_map_char(char character)
{
	if(character < FONT_ASCII_START_CHAR || character > FONT_ASCII_END_CHAR)
	{
		character = '?';
	}
	
	#ifdef FONT_IGNORE_LOWER_CASE
		character = toupper(character);
		
		if(character > 'z')
		{
			character = character - ('z' - 'a');
		}
	#endif

	return (character - FONT_ASCII_START_CHAR);
}

/**
 * @brief Retrieves the bitmap array for a given ASCII character from the font table.
 * 
 * @param character The ASCII character to retrieve the bitmap for.
 * @param bitmap Pointer to a array for storing the bitmap bytes representing the character.
 * 
 * @details
 * This function maps an input ASCII character to its corresponding bitmap pattern stored in the font table. If the character is outside the supported ASCII range defined by `FONT_ASCII_START_CHAR` and `FONT_ASCII_END_CHAR`, it defaults is the '?' character. When the macro `FONT_IGNORE_LOWER_CASE` is defined, lowercase letters are converted to uppercase to save memory, and adjustments are made to the character code accordingly.
 * 
 * @note The bitmap data is read from either EEPROM or program memory (PROGMEM) depending on the macro `FONT_STORE_IN_EEPROM`. The data is copied into an array pointed to. The operator has to prevent the correct size of this array!
 */
void font_get_bitmap(char character, unsigned char *bitmap)
{
    unsigned char character = font_map_char(character);

    for (unsigned char i=0; i < sizeof(font_ascii_table[0])/sizeof(font_ascii_table[0][0]); i++)
	{
		#ifdef FONT_STORE_IN_EEPROM
			bitmap[i] = eeprom_read_byte(&font_ascii_table[character][i]);
		#else
			#ifdef FONT_STORE_IN_PROGMEM
				bitmap[i] = pgm_read_byte(&font_ascii_table[character][i]);
			#else
				bitmap[i] = font_ascii_table[character][i];
			#endif
		#endif
	}
}