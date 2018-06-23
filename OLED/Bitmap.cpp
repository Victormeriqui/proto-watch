#include "Bitmap.h"

Bitmap::Bitmap()
{
	width = 128;
	height = 64;
	data_c = width * (height/8);
	
	data = (uint8_t*)malloc(sizeof(uint8_t) * data_c);
}

Bitmap::~Bitmap()
{
	free(data);
}

Bitmap::Bitmap(uint8_t w, uint8_t h)
{
	width = w;
	height = h;
	data_c = width * (height/8);
	
	data = (uint8_t*)malloc(sizeof(uint8_t) * data_c);
}

Bitmap::Bitmap(uint8_t w, uint8_t h, bool filled)
{
	width = w;
	height = h;
	data_c = width * (height/8);
	
	data = (uint8_t*)malloc(sizeof(uint8_t) * data_c);
	
	if (filled)
		Fill();
}

Bitmap::Bitmap(uint8_t w, uint8_t h, uint8_t* arr)
{
	width = w;
	height = h;
	data_c = width * (height/8);
	
	data = (uint8_t*)malloc(sizeof(uint8_t) * data_c);
	
	for (int i = 0; i < data_c; i++)
		data[i] = arr[i];
	//memcpy(data, arr, data_c);
}

void Bitmap::Fill()
{
	memset(data, 0xFF, data_c);
}

void Bitmap::Clear()
{
	memset(data, 0x00, data_c);
}

void Bitmap::DrawPixel(uint8_t x, uint8_t y)
{
	uint8_t segment = x;
	uint8_t page = y / 8;

	uint8_t mask = 1 << (y % 8);
	uint16_t cellpos = segment + page*width;

	data[cellpos] |= mask;
}

void Bitmap::ErasePixel(uint8_t x, uint8_t y)
{
	uint8_t segment = x;
	uint8_t page = y / 8;

	uint8_t mask = 0xFF - (1 << (y % 8));
	uint16_t cellpos = segment + page * width;

	data[cellpos] &= mask;
}