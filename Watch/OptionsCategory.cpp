#include "OptionsCategory.h"

#include "Controls/Control.h"
#include <stdio.h>
#include <string.h>

OptionsCategory::OptionsCategory()
{
	name = new char[21];
	description = new char[41];
	icon = new Bitmap(24, 24);
	
	strcpy(name, "Undefined");
	strcpy(description, "No arguments");
	
	control_list_c = 0;
	
	cursor_idx = 0;
	state = SELECTING_CATEGORY;
	
	//all categories have these
	control_list[control_list_c++] = new Button("OK");
	control_list[control_list_c++] = new Button("Cancel");
}

OptionsCategory::OptionsCategory(const char* title, uint8_t* iconbuff, const char* desc)
{
	name = new char[21];
	description = new char[40];

	strcpy(name, title);
	icon = new Bitmap(24, 24, iconbuff);
	strcpy(description, desc);
	
	control_list_c = 0;
	
	cursor_idx = 0;
	state = SELECTING_CATEGORY;

	//all categories have these
	control_list[control_list_c++] = new Button("OK");
	control_list[control_list_c++] = new Button("Cancel");
}

OptionsCategory::~OptionsCategory()
{
	for (uint8_t i = 0; i < control_list_c; i++)
		delete control_list[i];

	delete name;
	delete description;
	delete icon;
}

void OptionsCategory::Draw(OLED* oled)
{
	uint8_t scr_center_x = oled->GetScreenWidth()/2;
	uint8_t scr_center_y = oled->GetScreenHeight()/2;
		
	oled->SetFont(MEDIUM);
	uint8_t fontw = oled->GetFontWidth();
	
	//title
	oled->DrawString(scr_center_x - (strlen(name)/2*fontw), 0, name);

	uint8_t y = 20;
	//controls are drawn in vertical order
	for (uint8_t i = 0; i < control_list_c-2; i++)
	{
		control_list[i]->Draw(oled, 0, y);
		
		y += (control_list[i]->GetHeight() + 5);
	}

	//ok and cancel button
	control_list[control_list_c-2]->Draw(oled, scr_center_x-40, 54);
	control_list[control_list_c-1]->Draw(oled, scr_center_y+40, 54);
}

void OptionsCategory::Up()
{
	Control* control = control_list[cursor_idx];
	
	if (state == SELECTING_CATEGORY)
	{
		if (cursor_idx > 0)
		{
			//take cursor from last control
			control->SetState(IDLE_CONTROL);
			
			cursor_idx--;

			//give it to the next
			control = control_list[cursor_idx];
			control->SetState(CURSOROVER_CONTROL);
		}
	}

	if (state == FOCUSED_CATEGORY && control->GetState() == INTERACTING_CONTROL)
		control->Up();
}

void OptionsCategory::Down()
{		
	Control* control = control_list[cursor_idx];
	
	if (state == SELECTING_CATEGORY)
	{
		if (cursor_idx < control_list_c-1)
		{
			//take cursor from last control
			control->SetState(IDLE_CONTROL);
			
			cursor_idx++;
			
			//give it to the next
			control = control_list[cursor_idx];
			control->SetState(CURSOROVER_CONTROL);
		}
	}

	if (state == FOCUSED_CATEGORY && control->GetState() == INTERACTING_CONTROL)
		control->Down();
}

void OptionsCategory::Enter()
{
	Control* control = control_list[cursor_idx];
	
	if (state == SELECTING_CATEGORY)
	{		
		control->SetState(INTERACTING_CONTROL);
		state = FOCUSED_CATEGORY;
		
		if (!strcmp(control->GetLabel(), "OK"))
		{
			cursor_idx = 0;
			state = LEAVING_CATEGORY;
		}	
		
		return;
	}

	if (state == FOCUSED_CATEGORY)
	{
		control->Enter();
		
		//went idle after interacting, leave control
		if (control->GetState() == CURSOROVER_CONTROL)
			state = SELECTING_CATEGORY;		
	}
}

void OptionsCategory::SetState(OptionsCategoryState state)
{
	this->state = state;
}

OptionsCategoryState OptionsCategory::GetState()
{
	return state;
}

const char* OptionsCategory::GetName()
{
	return name;
}

Bitmap* OptionsCategory::GetIcon()
{
	return icon;
}

const char* OptionsCategory::GetDescription()
{
	return description;
}

void OptionsCategory::AddControl(Control* control)
{
	if (control_list_c == 0)
		control->SetState(CURSOROVER_CONTROL);
	
	//push ok and cancel button to the front
	for (uint8_t i = control_list_c; i > control_list_c-2; i--)
		control_list[i] = control_list[i-1];
	
	//fill in the gap with the new control
	control_list[control_list_c-2] = control;
	control_list_c++;	
}

uint8_t OptionsCategory::GetControlCount()
{
	return control_list_c;
}

Control* OptionsCategory::GetControl(int index)
{
	if (index < 0 || index > control_list_c)
		return nullptr;
	
	return control_list[index];
}

Control* OptionsCategory::GetControl(const char* name)
{
	for (uint8_t i = 0; i < control_list_c; i++)
	{
		if (!strcmp(control_list[i]->GetLabel(), name))
			return control_list[i];
	}
	
	return nullptr;
}
