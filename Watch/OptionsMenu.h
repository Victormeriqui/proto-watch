/*
Victor Meriqui
Created 23/05/2018
*/

#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include <Arduino.h>

#include "OptionsCategory.h"
#include "Bitmap.h"

enum OptionsMenuState
{
	SELECTING_OPTIONS, //selecting category
	INSIDE_OPTIONS, //inside category
	LEAVING_OPTIONS
};

class OptionsMenu
{
	OptionsCategory* category_list[10];
	uint8_t category_list_c;
	
	uint8_t cursor_idx;
	
	OptionsMenuState state;
	
	void PopulateCategories();
	
	public:
	
		OptionsMenu();
		~OptionsMenu();

		void Draw(OLED* oled);

		void Up();
		void Down();
		void Enter();
		void Home();		

		OptionsCategory* GetCategory(char* str);
		
		OptionsMenuState GetState();
		void SetState(OptionsMenuState state);
};

#endif