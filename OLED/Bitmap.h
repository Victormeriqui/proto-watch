/*
Victor Meriqui
Created 16/10/2016
*/

#ifndef BITMAP_H
#define BITMAP_H

#include <Arduino.h>

#include <stdlib.h>

class Bitmap
{

	public:
	
		uint8_t* data;
		int16_t data_c;
		
		uint8_t width;
		uint8_t height;
		
		Bitmap();
		~Bitmap();
		Bitmap(uint8_t w, uint8_t h);
		Bitmap(uint8_t w, uint8_t h, bool filled);
		Bitmap(uint8_t w, uint8_t h, uint8_t* arr);
		
		void Fill();
		void Clear();
		void DrawPixel(uint8_t x, uint8_t y);
		void ErasePixel(uint8_t x, uint8_t y);
};

#endif