/*
Victor Meriqui
Created 12/06/2018
*/

#ifndef PASSCODE_H
#define PASSCODE_H

#include "Control.h"

#include <Arduino.h>

class PassCode : public Control
{
	uint8_t values[10];
	uint8_t values_c;
	
	uint8_t cursor_idx;
	bool focused;
	
	public:

		PassCode();
		~PassCode();
		
		PassCode(char* name, uint8_t digit_count);
		
		void Draw(OLED* oled, uint8_t x, uint8_t y);
		
		uint8_t GetValue(int index);
		uint8_t GetValuesCount();
		uint32_t GetFullValue();
		
		void Up();
		void Down();
		void Enter();
};

#endif