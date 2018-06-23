/*
Victor Meriqui
Created 07/06/2018
*/

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "Control.h"

#include <Arduino.h>

class Checkbox : public Control
{
	bool checked;
	
	public:

		Checkbox();
		~Checkbox();
		
		Checkbox(char* name);
		
		void Draw(OLED* oled, uint8_t x, uint8_t y);

		bool IsChecked();
		
		void Up();
		void Down();
		void Enter();
};

#endif