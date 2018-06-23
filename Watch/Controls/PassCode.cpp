/*
Victor Meriqui
Created 12/06/2018
*/

#include "PassCode.h"
#include "OLEDFont.h"

#include <math.h>
#include <string.h>


PassCode::PassCode() : Control()
{
	for (uint8_t i = 0; i < 10; i++)
		values[i] = 0;
	
	values_c = 3;

	cursor_idx = 0;
	focused = false;
}

PassCode::~PassCode()
{
	
}

PassCode::PassCode(char* name, uint8_t digit_count) : Control(name)
{
	for (uint8_t i = 0; i < 10; i++)
		values[i] = '0'+i;
	
	values_c = digit_count;
	
	cursor_idx = 0;
	focused = false;
}

void PassCode::Draw(OLED* oled, uint8_t x, uint8_t y)
{
	uint8_t offset = 0;
	uint8_t valueoffset = 0;
	
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
		
		oled->DrawString(offset + x + strlen(namelabel)*fontw+2 + (values_c+2)*fontw*2+5, y, "ok");
	}	
	
	oled->DrawString(offset + x, y, namelabel);
	
	for (uint8_t i = 0; i < values_c; i++)
	{	
		if (state == INTERACTING_CONTROL)
		{
			if(cursor_idx == values_c)
				oled->DrawBitmap(&bmp_selectarrow, 0, 3, 4, 5, offset + x + strlen(namelabel)*fontw+2 + (values_c+2)*fontw*2, y);
			
			if (cursor_idx == i)
			{
				valueoffset = 5;
				
				if (focused)
				{
					oled->DrawBitmap(&bmp_selectarrowfill, 0, 3, 4, 5, offset + x + strlen(namelabel)*fontw+2 + i*fontw*2, y);
					valueoffset = 7;
					
					oled->DrawBitmap(&bmp_uparrow, 0, 4, 3, 4, valueoffset + offset + x + strlen(namelabel)*fontw+2 + i*fontw*2, y-fonth);
					oled->DrawBitmap(&bmp_downarrow, 0, 4, 3, 4, valueoffset + offset + x + strlen(namelabel)*fontw+2 + i*fontw*2, y+fonth+1);					
				}
				else
					oled->DrawBitmap(&bmp_selectarrow, 0, 3, 4, 5, offset + x + strlen(namelabel)*fontw+2 + i*fontw*2, y);
			}
			
		}
		
		oled->DrawChar(valueoffset + offset + x + strlen(namelabel)*fontw+2 + i*fontw*2, y, values[i]);
		
		//if (focused)
			//oled->DrawRect(valueoffset + offset + x + strlen(namelabel)*fontw+2 + i*fontw*2, y+fonth, fontw, 1);
	}
}

uint8_t PassCode::GetValue(int index)
{
	return values[index];
}

uint8_t PassCode::GetValuesCount()
{
	return values_c;
}

uint32_t PassCode::GetFullValue()
{
	uint32_t res = 0;
	uint8_t pos = 0;
	
	for (uint8_t i = values_c-1; i >= 0; i--)
	{
		res += values[i] * (uint32_t)pow(10, pos);
		pos++;
	}
	
	return res;
}

void PassCode::Up()
{
	if (focused)
	{
		if (values[cursor_idx] < '9')
			values[cursor_idx]++;
	}
	else
	{
		if (cursor_idx < values_c)
			cursor_idx++;
	}		
}

void PassCode::Down()
{
	if (focused)
	{
		if (values[cursor_idx] > '0')
			values[cursor_idx]--;
	}
	else
	{
		if (cursor_idx > 0)
			cursor_idx--;
	}		
}


void PassCode::Enter()
{
	if (cursor_idx == values_c)
	{
		state = CURSOROVER_CONTROL;
		return;
	}	
	
	focused = !focused;
}