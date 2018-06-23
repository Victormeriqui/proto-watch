/*
Victor Meriqui
Created 05/06/2018
*/

#ifndef BUTTON_H
#define BUTTON_H

#include "Control.h"

#include <Arduino.h>

class Button : public Control
{
	
	public:

		Button();
		~Button();
		
		Button(char* text);
		
		void Draw(OLED* oled, uint8_t x, uint8_t y);
};

#endif