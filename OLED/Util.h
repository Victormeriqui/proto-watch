/*
Victor Meriqui
Created 16/01/2018
*/


#ifndef UTIL_HPP
#define UTIL_HPP

#include <stdlib.h>

#include <string.h>


static uint8_t curtime = 0;
static uint8_t scroll_delay = 0;

inline bool GetStringSection(char* str, uint8_t start, uint8_t width, char* out)
{
	bool ended = false;
	
	uint8_t out_c = 0;
	
	for (int i = start; i < start+width; i++)
	{
		if (str[i] == '\0')
		{
			ended = true;
			break;
		}		
		
		out[out_c++] = str[i];	
	}
	
	return ended;
}

inline void ScrollString(char* str, char* outstr, uint8_t swidth, uint8_t fontw)
{
	bool ended;
	uint8_t len = strlen(str);
	
	uint8_t start = 0;
	uint8_t width = 0;
	
	if (len < swidth/fontw)
		width = len;
	else
		width = swidth/fontw;
	
	
	if (millis() - curtime > 100)
	{
		curtime = millis();
		
		ended = GetStringSection(str, start, width, outstr);
		
		if (!ended)
		{
			strcat(outstr, "...\0");
			start++;
		}
		else
		{
			scroll_delay++;
			
			if (scroll_delay > 5)
			{
				start = 0;
			}
		}
		
		
	}
	
	
}

#endif