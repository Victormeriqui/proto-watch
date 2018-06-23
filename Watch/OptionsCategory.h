/*
Victor Meriqui
Created 23/05/2018
*/

#ifndef OPTIONSCATEGORY_H
#define OPTIONSCATEGORY_H

#include "OLED.h"
#include "Bitmap.h"
#include "Controls/Control.h"
#include "Controls/Button.h"

enum OptionsCategoryState
{
	SELECTING_CATEGORY, //selecting control
	FOCUSED_CATEGORY, //using control
	LEAVING_CATEGORY
};

class OptionsCategory
{	
	char* name;
	Bitmap* icon;
	char* description;

	//unique controls
	Control* control_list[10];
	uint8_t control_list_c;
	
	OptionsCategoryState state;

	uint8_t cursor_idx;//cursor	
	
	public:
		
		OptionsCategory();
		~OptionsCategory();
		
		OptionsCategory(const char* title, uint8_t* iconbuff, const char* desc);
		
		void Draw(OLED* oled);

		void Up();
		void Down();
		void Enter();
		
		OptionsCategoryState GetState();
		void SetState(OptionsCategoryState state);
		
		const char* GetName();
		Bitmap* GetIcon();
		const char* GetDescription();
		
		void AddControl(Control* control);
		Control* GetControl(int index);
		Control* GetControl(const char* name);
		uint8_t GetControlCount();
		
};

#endif