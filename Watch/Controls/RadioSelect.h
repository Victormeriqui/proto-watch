/*
Victor Meriqui
Created 12/06/2018
*/

#ifndef RADIOSELECT_H
#define RADIOSELECT_H

#include "Controls/Control.h"

#include <Arduino.h>

class RadioSelect : public Control
{
	char* values[10];
	int values_c;
		
	uint8_t choice_idx;	
	uint8_t cursor_idx;
	
	public:

		RadioSelect();
		~RadioSelect();
		
		RadioSelect(char* name);
		
		void Draw(OLED* oled, uint8_t x, uint8_t y);
		
		void AddValue(char* value);
		
		const char* GetValue(int index);
		uint8_t GetValuesCount();
		const char* GetChosenValue();
				
		void Up();
		void Down();
		void Enter();
};

#endif