/*
Victor Meriqui
Created 16/01/2018
*/


#include "OLEDFont.h"

OLEDFont::OLEDFont()
{
	mapwidth = 0;
	mapheight = 0;
	glyphwidth = 0;
	glyphheight = 0;
	mapstartx = 0;
	mapstarty = 0;
	map = new Bitmap();
}

OLEDFont::~OLEDFont()
{
	delete map;
}

OLEDFont::OLEDFont(uint8_t fontwidth, uint8_t fontheight, uint8_t charwidth, uint8_t charheight, uint8_t* font, uint8_t startx, uint8_t starty, uint8_t offset, bool linear)
{
	mapwidth = fontwidth;
	mapheight = fontheight;
	glyphwidth = charwidth;
	glyphheight = charheight;

	mapstartx = startx;
	mapstarty = starty;
	
	glyphoffset = offset;
	islinear = linear;
	
	map = new Bitmap(mapwidth, mapheight, font);
}


uint8_t OLEDFont::GetGlyphWidth()
{
	return glyphwidth;
}

uint8_t OLEDFont::GetGlyphHeight()
{
	return glyphheight;
}	

uint8_t OLEDFont::GetMapStartX()
{
	return mapstartx;
}

uint8_t OLEDFont::GetMapStartY()
{
	return mapstarty;
}

uint8_t OLEDFont::GetMapWidth()
{
	return mapwidth;
}

uint8_t OLEDFont::GetMapHeight()
{
	return mapheight;
}

uint8_t OLEDFont::GetGlyphOffset()
{
	return glyphoffset;
}

bool OLEDFont::IsLinear()
{
	return islinear;
}

Bitmap* OLEDFont::GetMap()
{
	return map;
}