/*
Victor Meriqui
Created 12/06/2018
*/

#include "Controls/RadioSelect.h"
#include "OLEDFont.h"

#include <string.h>


RadioSelect::RadioSelect() : Control()
{
	values_c = 0;
	cursor_idx = 0;
	choice_idx = 0;
}

RadioSelect::~RadioSelect()
{
	for (uint8_t i = 0; i < values_c; i++)
		delete values[i];
}

RadioSelect::RadioSelect(char* name) : Control(name)
{
	values_c = 0;
	cursor_idx = 0;
	choice_idx = 0;
}

void RadioSelect::Draw(OLED* oled, uint8_t x, uint8_t y)
{
	uint8_t offset = 0;
	uint8_t valueoffset = 0;
	uint8_t vallistoffset = 0;
	
	oled->SetFont(SMALL);
	uint8_t fontw = oled->GetFontWidth();
	uint8_t fonth = oled->GetFontHeight();
		
	char namelabel[23];
	strcpy(namelabel, label);
	strcat(namelabel, ":");
	
	if (width == 0 && height == 0)
	{
		width = 1;
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

	for (uint8_t i = 0; i < values_c; i++)
	{	
		if (state == INTERACTING_CONTROL)
		{
			if (cursor_idx == i)
			{
				valueoffset = 5;
			
				oled->DrawBitmap(&bmp_selectarrow, 0, 3, 4, 5, offset + x + strlen(namelabel)*fontw+2 + vallistoffset, y);
			}
			
		}
		
		oled->DrawString(valueoffset + offset + x + strlen(namelabel)*fontw+2 + vallistoffset, y, values[i]);
				
		if (choice_idx == i)
			oled->DrawRect(valueoffset + offset + x + strlen(namelabel)*fontw+2 + vallistoffset, y+fonth, fontw*strlen(values[i]), 1);
		
		vallistoffset += strlen(values[i])*fontw+5;
	}
}

void RadioSelect::AddValue(char* value)
{
	values[values_c] = new char[10];
	strcpy(values[values_c++], value);
}
	
const char* RadioSelect::GetValue(int index)
{
	return values[index];
}

uint8_t RadioSelect::GetValuesCount()
{
	return values_c;
}

const char* RadioSelect::GetChosenValue()
{
	return values[choice_idx];
}

void RadioSelect::Up()
{
	if (cursor_idx < values_c-1)
		cursor_idx++;
}

void RadioSelect::Down()
{
	if (cursor_idx > 0)
		cursor_idx--;
}

void RadioSelect::Enter()
{
	choice_idx = cursor_idx;
	state = CURSOROVER_CONTROL;
}
