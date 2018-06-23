#include "OptionsMenu.h"

#include "Controls/Control.cpp"
#include "Controls/Checkbox.cpp"
#include "Controls/NumericUpDown.cpp"
#include "Controls/PassCode.cpp"
#include "Controls/Button.cpp"
#include "Controls/RadioSelect.cpp"
#include "OLEDFont.h"
#include "Images.h"

#include <string.h>


OptionsMenu::OptionsMenu()
{
	category_list_c = 0;
	cursor_idx = 0;
	state = SELECTING_OPTIONS;
	PopulateCategories();
}

OptionsMenu::~OptionsMenu()
{
	for (uint8_t i = 0; i < category_list_c; i++)
		delete category_list[i];
}

void OptionsMenu::PopulateCategories()
{
	//Watch
	OptionsCategory* watchcat = new OptionsCategory("Watch", buff_watch, "Watch face settings");
	
	RadioSelect* timeformat = new RadioSelect("Time Format");
	timeformat->AddValue("12h");
	timeformat->AddValue("24h");	
	Checkbox* showsecs = new Checkbox("Show Seconds");
	watchcat->AddControl(timeformat);
	watchcat->AddControl(showsecs);
	
	category_list[category_list_c++] = watchcat;
	
	//Options	
	OptionsCategory* settingscat = new OptionsCategory("Options", buff_gear, "General settings");
	
	Checkbox* vibrateinput = new Checkbox("Input Vibration");
	settingscat->AddControl(vibrateinput);
	NumericUpDown* vibratetime = new NumericUpDown("Vibration time(ms)", 5, 50);
	settingscat->AddControl(vibratetime);
	
	category_list[category_list_c++] = settingscat;
	
	//Notifications
	OptionsCategory* notifycat = new OptionsCategory("Notifications", buff_bell, "Notification settings");
	
	Checkbox* vibratenotify = new Checkbox("Notification Vibration");
	notifycat->AddControl(vibratenotify);
	
	category_list[category_list_c++] = notifycat;
	
	//Bluetooth
	OptionsCategory* bluetoothcat = new OptionsCategory("Bluetooth", buff_bluetooth, "Bluetooth connection settings");
	
	Checkbox* blucheck = new Checkbox("Module On");
	PassCode* blupin = new PassCode("Password", 6);

	bluetoothcat->AddControl(blucheck);
	bluetoothcat->AddControl(blupin);

	category_list[category_list_c++] = bluetoothcat;
}


void OptionsMenu::Draw(OLED* oled)
{
	OptionsCategory* curcategory = category_list[cursor_idx];
	
	if (state == INSIDE_OPTIONS)
	{
		curcategory->Draw(oled);
		return;
	}
	
	const char* name = curcategory->GetName();
	Bitmap* icon = curcategory->GetIcon();
	const char* desc = curcategory->GetDescription();
	
	uint8_t scr_center_x = oled->GetScreenWidth()/2;
	uint8_t scr_center_y = oled->GetScreenHeight()/2; 
	
	uint8_t fontw = oled->GetFontWidth();
	uint8_t fonth = oled->GetFontHeight();	

	oled->SetFont(MEDIUM);
	
	oled->DrawString(scr_center_x - (strlen(name)*fontw/2), 0, name);
	oled->DrawBitmap(icon, 0, 0, 24, 24, scr_center_x-12, scr_center_y-12);
	
	oled->SetFont(SMALL);
	fontw = oled->GetFontWidth();
	fonth = oled->GetFontHeight();	
	
	oled->DrawString(scr_center_x - (strlen(desc)*fontw/2), oled->GetScreenHeight()-fonth, desc);
}

void OptionsMenu::SetState(OptionsMenuState state)
{
	this->state = state;
}

OptionsMenuState OptionsMenu::GetState()
{
	return state;
}

void OptionsMenu::Up()
{
	OptionsCategory* curcategory = category_list[cursor_idx];
	
	if (state == SELECTING_OPTIONS)
	{
		if (cursor_idx > 0)
			cursor_idx--;
	}

	if (state == INSIDE_OPTIONS && curcategory->GetState() != LEAVING_CATEGORY)
		curcategory->Up();
}

void OptionsMenu::Down()
{
	OptionsCategory* curcategory = category_list[cursor_idx];
	
	if (state == SELECTING_OPTIONS)
	{
		if (cursor_idx < category_list_c-1)
			cursor_idx++;
	}

	if (state == INSIDE_OPTIONS && curcategory->GetState() != LEAVING_CATEGORY)
		curcategory->Down();
}

void OptionsMenu::Enter()
{
	OptionsCategory* curcategory = category_list[cursor_idx];
	
	if (state == SELECTING_OPTIONS)
	{		
		state = INSIDE_OPTIONS;
		curcategory->SetState(SELECTING_CATEGORY);

		return;
	}

	if (state == INSIDE_OPTIONS)
	{
		curcategory->Enter();
		
		//changed state to leaving after interaction, leaving category
		//preserve cursor
		if (curcategory->GetState() == LEAVING_CATEGORY)
			state = SELECTING_OPTIONS;		
	}
	
}

void OptionsMenu::Home()
{
	OptionsCategory* curcategory = category_list[cursor_idx];
	
	if (state == INSIDE_OPTIONS)
	{
		curcategory->SetState(LEAVING_CATEGORY);
		state = SELECTING_OPTIONS;
		
		return;
	}		
	
	if (state == SELECTING_OPTIONS)
	{
		cursor_idx = 0;
		state = LEAVING_OPTIONS;
	}
}

OptionsCategory* OptionsMenu::GetCategory(char* str)
{
	for (uint8_t i = 0; i < category_list_c; i++)
	{
		if (!strcmp(category_list[i]->GetName(), str))
			return category_list[i];
	}
	
	return nullptr;
}
