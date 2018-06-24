/*
Victor Meriqui
Created 16/01/2018
*/


#ifndef OLED_H
#define OLED_H

//COMMANDS
#define OLED_I2C_ADDRESS   0x3C

#define OLED_SETCONTRAST 0x81
#define OLED_DISPLAYALLON_RESUME 0xA4
#define OLED_DISPLAYALLON 0xA5
#define OLED_NORMALDISPLAY 0xA6
#define OLED_INVERTDISPLAY 0xA7
#define OLED_DISPLAYOFF 0xAE
#define OLED_DISPLAYON 0xAF

#define OLED_SETDISPLAYOFFSET 0xD3
#define OLED_SETCOMPINS 0xDA

#define OLED_SETVCOMDETECT 0xDB

#define OLED_SETDISPLAYCLOCKDIV 0xD5
#define OLED_SETPRECHARGE 0xD9

#define OLED_SETMULTIPLEX 0xA8

#define OLED_SETLOWCOLUMN 0x00
#define OLED_SETHIGHCOLUMN 0x10

#define OLED_SETSTARTLINE 0x40

#define OLED_MEMORYMODE 0x20
#define OLED_COLUMNADDR 0x21
#define OLED_PAGEADDR   0x22

#define OLED_COMSCANINC 0xC0
#define OLED_COMSCANDEC 0xC8

#define OLED_SEGREMAP 0xA0

#define OLED_CHARGEPUMP 0x8D

#define OLED_EXTERNALVCC 0x1
#define OLED_SWITCHCAPVCC 0x2

// Scrolling #defines
#define OLED_ACTIVATE_SCROLL 0x2F
#define OLED_DEACTIVATE_SCROLL 0x2E
#define OLED_SET_VERTICAL_SCROLL_AREA 0xA3
#define OLED_RIGHT_HORIZONTAL_SCROLL 0x26
#define OLED_LEFT_HORIZONTAL_SCROLL 0x27
#define OLED_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define OLED_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

#include <Arduino.h>

#include <stdlib.h>
#include <avr/pgmspace.h>
#include <Wire.h>

#include "Bitmap.h"
#include "OLEDFont.h"

enum FontType
{
	SMALL,
	MEDIUM,
	LARGE
};

class OLED
{
	int8_t vccstate, i2caddress, resetpin;
	Bitmap* framebuffer;
	
	OLEDFont* curfont;
	
	OLEDFont* smallfont;
	OLEDFont* mediumfont;
	OLEDFont* largefont;

	public:
	
		OLED();
		~OLED();
		OLED(int8_t rst);

		void Initialize(int8_t vcc, int8_t i2caddr);
		void Reset();
		void Command(uint8_t command);
		void Data(uint8_t data);
		void Begin();
		
		void Fill();
		void Clear();
		void Display();
						
		void SetDisplayInversion(bool val);
		void SetDisplayDim(bool val);
		void SetDisplayContrast(uint8_t contrast);
		
		void DrawPixel(uint8_t x, uint8_t y);
		void ErasePixel(uint8_t x, uint8_t y);
				
		void DrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
		void DrawRectOutline(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t thickness);
		
		void DrawLine(uint8_t startx, uint8_t starty, uint8_t endx, uint8_t endy);
		void DrawCircle(uint8_t centerx, uint8_t centery, float radius, uint8_t quality);
		
		void DrawBitmap(Bitmap* map, uint8_t mapx, uint8_t mapy, uint8_t width, uint8_t height, uint8_t x, uint8_t y);
				
		void SetFont(FontType type);
		uint8_t GetFontWidth();
		uint8_t GetFontHeight();		
		
		uint8_t GetScreenWidth();
		uint8_t GetScreenHeight();
		
		void DrawChar(uint8_t x, uint8_t y, char chr);
		void DrawString(uint8_t x, uint8_t y, const char* str);
		void DrawString(uint8_t x, uint8_t y, int32_t num);
		
		void DrawStringF(uint8_t x, uint8_t y, const char* str, ...);
};

#endif