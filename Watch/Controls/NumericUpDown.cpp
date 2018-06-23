/*
Victor Meriqui
Created 11/06/2018
*/

#include "NumericUpDown.h"
#include "OLEDFont.h"
#include "MathUtil.h"
#include "Bitmap.h"
#include "../Images.h"

#include <string.h>




NumericUpDown::NumericUpDown() : Control()
{
	width = 0;
	height = 0;
}

NumericUpDown::~NumericUpDown()
{
	
}

NumericUpDown::NumericUpDown(char* name, int16_t minvalue, int16_t maxvalue) : Control(name)
{
	value = 0;
	this->minvalue = minvalue;
	this->maxvalue = maxvalue;
	
	width = 0;
	height = 0;
}

void NumericUpDown::Draw(OLED* oled, uint8_t x, uint8_t y)
{
	uint8_t fontw = oled->GetFontWidth();
	uint8_t fonth = oled->GetFontHeight();
	uint8_t offset = 0;
	
	char namelabel[23];
	strcpy(namelabel, label);
	strcat(namelabel, ":");
		
	oled->SetFont(SMALL);
	
	int8_t len = DigitCount(value)-1;
	
	if (width == 0 && height == 0)
	{
		width = fontw*strlen(namelabel) + 2 + fontw*len;
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
	
	oled->DrawString(offset + x + fontw*strlen(namelabel) + 2, y, value);
	
	if (state == INTERACTING_CONTROL)
	{
		oled->DrawBitmap(&bmp_uparrow, 0, 4, 3, 4, offset + x + strlen(namelabel)*fontw+2 + (fontw*len)/2, y-fonth);
		oled->DrawBitmap(&bmp_downarrow, 0, 4, 3, 4, offset + x + strlen(namelabel)*fontw+2 + (fontw*len)/2, y+fonth+1);
	}
	
}

int16_t NumericUpDown::GetValue()
{
	return value;
}

int16_t NumericUpDown::GetMinValue()
{
	return minvalue;
}

int16_t NumericUpDown::GetMaxValue()
{
	return maxvalue;
}

void NumericUpDown::Up()
{
	if (value < maxvalue)
		value++;
}

void NumericUpDown::Down()
{
	if (value > minvalue)
		value--;
}

void NumericUpDown::Enter()
{
	state = CURSOROVER_CONTROL;
}