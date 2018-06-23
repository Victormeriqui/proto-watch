/*
Victor Meriqui
Created 11/06/2018
*/

#ifndef NUMERICUPDOWN_H
#define NUMERICUPDOWN_H

#include "Control.h"
#include "Bitmap.h"

#include <Arduino.h>


	
class NumericUpDown : public Control
{
	int16_t value;
	
	int16_t minvalue;
	int16_t maxvalue;
	
	public:

		NumericUpDown();
		~NumericUpDown();
		
		NumericUpDown(char* name, int16_t minvalue, int16_t maxvalue);
		
		void Draw(OLED* oled, uint8_t x, uint8_t y);
		
		int16_t GetValue();
		int16_t GetMinValue();
		int16_t GetMaxValue();
		
		void Up();
		void Down();
		void Enter();
};

#endif