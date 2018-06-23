/*
Victor Meriqui
Created 05/06/2018
*/

#include "Button.h"
#include "OLEDFont.h"
#include "Images.h"

#include <string.h>


Button::Button() : Control()
{
}

Button::~Button()
{	
}

Button::Button(char* text) : Control(text)
{
	width = 30;
	height = 10;
}

void Button::Draw(OLED* oled, uint8_t x, uint8_t y)
{
	oled->SetFont(SMALL);
	uint8_t fontw = oled->GetFontWidth();
	uint8_t fonth = oled->GetFontHeight();
		
	if (state != IDLE_CONTROL)
		oled->DrawBitmap(&bmp_selectarrow, 0, 3, 4, 5, x-6, y);
	
	oled->DrawString(x + width/2 - (strlen(label)*fontw/2), y, label);

	oled->DrawRectOutline(x-2, y-2, width, height, 1);
	
}
