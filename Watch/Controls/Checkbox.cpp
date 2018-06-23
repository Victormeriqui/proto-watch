/*
Victor Meriqui
Created 07/06/2018
*/

#include "Checkbox.h"
#include "OLEDFont.h"
#include "Images.h"

#include <string.h>


Checkbox::Checkbox() : Control()
{
	checked = true;
}

Checkbox::~Checkbox()
{
	
}

Checkbox::Checkbox(char* name) : Control(name)
{
	checked = true;
}

void Checkbox::Draw(OLED* oled, uint8_t x, uint8_t y)
{

	oled->SetFont(SMALL);
	uint8_t fontw = oled->GetFontWidth();
	uint8_t fonth = oled->GetFontHeight();
	
	uint8_t offset = 0;
	
	char namelabel[23];
	strcpy(namelabel, label);
	strcat(namelabel, ":");
	
	
	
	if (width == 0 && height == 0)
	{
		width = fontw*strlen(namelabel) + 7;
		height = fonth;
	}
		
	if (state == CURSOROVER_CONTROL)
	{
		offset = 7;
		oled->DrawBitmap(&bmp_selectarrow, 0, 3, 4, 5, x, y);
	}
	
	if (state == INTERACTING_CONTROL)
	{
		offset = 10;
		oled->DrawBitmap(&bmp_selectarrowfill, 0, 3, 4, 5, x, y);
	}	
	
	oled->DrawString(offset + x, y, namelabel);
	
	oled->DrawRectOutline(offset + x + width-6, y-1, 6, 6, 1);
	
	if (checked)
		oled->DrawRect(offset + x + width - 4, y+1, 3, 3);	
	
	//oled->DrawChar(offset + x + strlen(namelabel)*fontw+7, y, 'x');
	
	
	
}

bool Checkbox::IsChecked()
{
	return checked;
}

void Checkbox::Up()
{
	checked = true;
}

void Checkbox::Down()
{
	checked = false;
}

void Checkbox::Enter()
{
	state = CURSOROVER_CONTROL;
}
