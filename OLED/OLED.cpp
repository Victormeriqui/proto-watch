/*
Victor Meriqui
Created 12/3/2016
*/

#include "OLED.h"

#include "MathUtil.h"

#include <math.h>
#include <stdarg.h>
#include <string.h>

#ifdef __AVR__
 #include <avr/pgmspace.h>
#elif defined(ESP8266)
 #include <pgmspace.h>
#endif

OLED::OLED()
{
	resetpin = 4;
	framebuffer = new Bitmap(128, 64, false);
	//font = new Bitmap(128, 64, fontarray);
	curfont = nullptr;
}

OLED::~OLED()
{
	delete framebuffer;
	
	delete smallfont;
	delete mediumfont;
	delete largefont;
}

OLED::OLED(int8_t rstpin)
{
	resetpin = rstpin;
	framebuffer = new Bitmap(128, 64, false);
	//font = new Bitmap(128, 64, fontarray);
	curfont = nullptr;
	
	smallfont = new OLEDFont(128, 24, 4, 6, smallfontbuff, 0, 6, 0, false);
	mediumfont = new OLEDFont(128, 64, 5, 8, mediumfontbuff, 0, 0, 2, false);
	largefont = new OLEDFont(150, 16, 10, 16, largefontbuff, 0, 0, 0, true);
}

void OLED::Initialize(int8_t vcc, int8_t i2caddr)
{
	vccstate = vcc;
	i2caddress = i2caddr;
}

void OLED::Reset()
{
  pinMode(resetpin, OUTPUT);
  digitalWrite(resetpin, HIGH);
 
  delay(100);
  digitalWrite(resetpin, LOW);
  delay(100);
  digitalWrite(resetpin, HIGH);
}

void OLED::Command(uint8_t command)
{
	uint8_t control = 0x00;   // Co = 0, D/C = 0
    Wire.beginTransmission(i2caddress);
    Wire.write(control);
    Wire.write(command);
    Wire.endTransmission();
}

void OLED::Data(uint8_t data)
{
	uint8_t control = 0x40;   // Co = 0, D/C = 1
    Wire.beginTransmission(i2caddress);
    Wire.write(control);
    Wire.write(data);
    Wire.endTransmission();
}

void OLED::Begin()
{
    Wire.begin();

#ifdef __SAM3X8E__
    // Force 400 KHz I2C, rawr! (Uses pins 20, 21 for SDA, SCL)
    TWI1->TWI_CWGR = 0;
    TWI1->TWI_CWGR = ((VARIANT_MCK / (2 * 400000)) - 4) * 0x101;
#endif

	Reset();
	
    Command(OLED_DISPLAYOFF);                    // 0xAE
    Command(OLED_SETDISPLAYCLOCKDIV);            // 0xD5
    Command(0x80);                                  // the suggested ratio 0x80
    Command(OLED_SETMULTIPLEX);                  // 0xA8
    Command(0x3F);
    Command(OLED_SETDISPLAYOFFSET);              // 0xD3
    Command(0x0);                                   // no offset
    Command(OLED_SETSTARTLINE | 0x0);            // line #0
    Command(OLED_CHARGEPUMP);                    // 0x8D
    if (vccstate == OLED_EXTERNALVCC) 
		Command(0x10); 
    else 
		Command(0x14);
	
    Command(OLED_MEMORYMODE);                    // 0x20
    Command(0x00);                                  // 0x0 act like ks0108
    Command(OLED_SEGREMAP | 0x1);
    Command(OLED_COMSCANDEC);
    Command(OLED_SETCOMPINS);                    // 0xDA
    Command(0x12);
    Command(OLED_SETCONTRAST);                   // 0x81
	
    if (vccstate == OLED_EXTERNALVCC) 
		Command(0x9F);
    else 
		Command(0xCF);
    Command(OLED_SETPRECHARGE);                  // 0xd9
    if (vccstate == OLED_EXTERNALVCC) 
		Command(0x22);
    else 
		Command(0xF1);
    Command(OLED_SETVCOMDETECT);                 // 0xDB
    Command(0x40);
    Command(OLED_DISPLAYALLON_RESUME);           // 0xA4
    Command(OLED_NORMALDISPLAY);                 // 0xA6
	
	Command(OLED_DISPLAYON);
}

void OLED::Display()
{
	Command(OLED_COLUMNADDR);
	Command(0);   // Column start address (0 = reset)
	Command(127); // Column end address (127 = reset)

	Command(OLED_PAGEADDR);
	Command(0); // Page start address (0 = reset)
	Command(7); // Page end address

	  // save I2C bitrate
#ifndef __SAM3X8E__
    uint8_t twbrbackup = TWBR;
    TWBR = 12; // upgrade to 400KHz!
#endif
	
	// I2C
	for (uint16_t i = 0; i < (128*8); i++) 
	{
		// send a bunch of data in one xmission
		Wire.beginTransmission(i2caddress);
		Wire.write(0x40);
		for (uint8_t x = 0; x < 16; x++) 
		{
			Wire.write(framebuffer->data[i]);
			i++;
		}
		i--;
		Wire.endTransmission();
	}
	
#ifndef __SAM3X8E__
    TWBR = twbrbackup;
#endif

}

void OLED::Fill()
{
	framebuffer->Fill();
}

void OLED::Clear()
{
	framebuffer->Clear();
}

void OLED::DrawPixel(uint8_t x, uint8_t y)
{
	framebuffer->DrawPixel(x, y);
}

void OLED::ErasePixel(uint8_t x, uint8_t y)
{
	framebuffer->ErasePixel(x, y);
}

void OLED::SetDisplayInversion(bool val)
{
	if(val)
		Command(OLED_INVERTDISPLAY);
	else
		Command(OLED_NORMALDISPLAY);
}
	
void OLED::SetDisplayDim(bool val)
{
	uint8_t contrast;

	if (val) 
		contrast = 0; // Dimmed display
	else 
	{
		if (vccstate == OLED_EXTERNALVCC) 	
		  contrast = 0x9F;
		else 
		  contrast = 0xCF;
	}
	
	Command(OLED_SETCONTRAST);
	Command(contrast);
}


void OLED::SetDisplayContrast(uint8_t contrast)
{	
	Command(OLED_SETCONTRAST);
	Command(contrast);
}

void OLED::DrawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height)
{
	for (uint8_t curx = x; (curx < (x + width)) && (curx < 128); curx++)
	{

		for (uint8_t cury = y; (cury < (y + height)) && (cury < 64); cury++)
		{
			uint8_t segment = curx;
			uint8_t page = cury / 8;

			uint8_t mask = 1 << (cury % 8);
			uint16_t cellpos = segment + page*128;	

			framebuffer->data[cellpos] |= mask;
		}
		
	}
}

void OLED::DrawRectOutline(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t thickness)
{
	DrawRect(x, y, width, thickness);
	DrawRect(x, y, thickness, height);
	DrawRect(x + width, y, thickness, height+1);
	DrawRect(x, y + height, width+1, thickness);
}

void OLED::DrawLine(uint8_t startx, uint8_t starty, uint8_t endx, uint8_t endy)
{
	uint8_t deltax = abs(endx - startx);
	uint8_t deltay = abs(endy - starty);

	int8_t stepx = (startx < endx) ? 1 : -1;
	int8_t stepy = (starty < endy) ? 1 : -1;

	int8_t err = ((deltax > deltay) ? deltax : -deltay) / 2;
	int8_t err2;

	while (startx != endx || starty != endy)
	{
		DrawPixel(startx, starty);
		
		err2 = err;

		if (err2 > -deltax)
		{
			err -= deltay;
			startx += stepx;
		}
		if (err2 < deltay)
		{
			err += deltax;
			starty += stepy;
		}
	}
}

void OLED::DrawCircle(uint8_t centerx, uint8_t centery, float radius, uint8_t quality)
{
	float ang = 0;
	float step = (PI*2)/quality;
	
	uint8_t lastx = centerx + radius;
	uint8_t lasty = centery;
	
	for (ang = step; ang < PI*2+step; ang += step)
	{
		uint8_t curx = centerx + cos(ang)*radius;
		uint8_t cury = centery + sin(ang)*radius;
					
		DrawLine(lastx, lasty, curx, cury);
		
		lastx = curx;
		lasty = cury;
		
	}
}

void OLED::DrawBitmap(Bitmap* map, uint8_t mapx, uint8_t mapy, uint8_t width, uint8_t height, uint8_t x, uint8_t y)
{
	uint8_t curmapx = mapx;
	uint8_t curmapy = mapy;

	for (uint8_t tox = x; (tox < (x + width)) && (tox < 128); tox++)
	{
		for (uint8_t toy = y; (toy < (y + height)) && (toy < 64); toy++)
		{
			uint8_t tosegment = tox;
			uint8_t topage = toy / 8;

			uint8_t fromsegment = curmapx;
			uint8_t frompage = curmapy / 8;
		
			uint8_t frommask = 1 << (curmapy % 8);
			uint8_t tomask = 1 << (toy % 8);
			
			uint16_t tocellpos = tosegment + topage * 128;
			uint16_t fromcellpos = fromsegment + frompage * map->width;

			if (map->data[fromcellpos] & frommask)
				framebuffer->data[tocellpos] |= tomask;
			else
				framebuffer->data[tocellpos] &= ~tomask;
			
			curmapy++;
		}
		
		curmapx++;
		curmapy = mapy;
	}
}


void OLED::SetFont(FontType type)
{
	switch (type)
	{
		case SMALL:
		curfont = smallfont;
		break;
		
		case MEDIUM:
		curfont = mediumfont;
		break;
		
		case LARGE:
		curfont = largefont;
		break;
	}
}

uint8_t OLED::GetFontWidth()
{
	return curfont->GetGlyphWidth();
}

uint8_t OLED::GetFontHeight()
{
	return curfont->GetGlyphHeight();
}

uint8_t OLED::GetScreenWidth()
{
	return 128;
}

uint8_t OLED::GetScreenHeight()
{
	return 64;
}

void OLED::DrawChar(uint8_t x, uint8_t y, char chr)
{
	uint8_t glyphw = curfont->GetGlyphWidth();
	uint8_t glyphh = curfont->GetGlyphHeight();
	
	uint8_t glyphoffset = curfont->GetGlyphOffset();
	
	uint8_t charsperrow = curfont->GetMapWidth()/glyphw + (glyphoffset > 0 ? 1 : 0);
	
	uint8_t glyphy = ((chr-32) / charsperrow) * glyphh;
	uint8_t xoffset = glyphy/glyphh*glyphoffset;
	uint8_t glyphx = (((chr-32) % charsperrow) * glyphw) + xoffset;
	
	
	if (curfont->IsLinear())
	{
		switch (chr)
		{
		case 'A' :
			DrawBitmap(curfont->GetMap(), curfont->GetMapStartX()+(11*glyphw), curfont->GetMapStartY(), glyphw, glyphh, x, y);
			break;
		case 'M' :
			DrawBitmap(curfont->GetMap(), curfont->GetMapStartX()+(12*glyphw), curfont->GetMapStartY(), glyphw, glyphh, x, y);
			break;
		case 'P' :
			DrawBitmap(curfont->GetMap(), curfont->GetMapStartX()+(13*glyphw), curfont->GetMapStartY(), glyphw, glyphh, x, y);
			break;
		case ' ' :
			DrawBitmap(curfont->GetMap(), curfont->GetMapStartX()+(14*glyphw), curfont->GetMapStartY(), glyphw, glyphh, x, y);
			break;
		default :
			DrawBitmap(curfont->GetMap(), curfont->GetMapStartX()+ ((chr-'0')*glyphw), curfont->GetMapStartY(), glyphw, glyphh, x, y);
		}		
	}
	else
		DrawBitmap(curfont->GetMap(), curfont->GetMapStartX() + glyphx, curfont->GetMapStartY() + glyphy, curfont->GetGlyphWidth(), curfont->GetGlyphHeight(), x, y);
	//DrawBitmap(curfont->GetMap(), 20, 0, 10, 16, 0, 0);
}

void OLED::DrawString(uint8_t x, uint8_t y, const char* str)
{
	uint8_t rx = x;
	uint8_t ry = y;

	for (uint16_t i = 0; str[i] != '\0'; i++)
	{
		DrawChar(rx, ry, str[i]);
		
		rx += curfont->GetGlyphWidth();
		
		if(rx > 124)
		{
			ry += curfont->GetGlyphHeight();
			rx = x;
		}	
	}
}

void OLED::DrawString(uint8_t x, uint8_t y, int32_t num)
{
	int8_t dig_c = DigitCount(num);
	uint8_t rx = x;
	uint8_t ry = y;
	int16_t div = (int16_t)pow(10, dig_c-1);
	
	while(dig_c > 0)
	{
		uint8_t dig = (num/div) % 10;
		
		DrawChar(rx, ry, '0'+dig);
		
		rx += curfont->GetGlyphWidth();
		
		if(rx > 124)
		{
			ry += curfont->GetGlyphHeight();
			rx = x;
		}	
		
		div /= 10;
		dig_c--;
	}
}

void OLED::DrawStringF(uint8_t x, uint8_t y, const char* str, ...)
{
	uint8_t rx = x;
	uint8_t ry = y;
	
	char tempstr[100];
	
	va_list arglist;
		
	va_start(arglist, str);
	
	for (uint16_t i = 0; str[i] != '\0'; i++)
	{
		if(str[i] != '%' && str[i] != '\n')
		{
			DrawChar(rx, ry, str[i]);
			rx += curfont->GetGlyphWidth();
		}
		
		if(str[i] == '%')
		{
			switch(str[i+1])
			{
				case 'c':
				DrawChar(rx, ry, va_arg(arglist, int));
				rx += curfont->GetGlyphWidth();
				break;
				
				case 'd':
				case 'i':
				itoa(va_arg(arglist, int), tempstr, 10);
				DrawString(rx, ry, tempstr);
				rx += curfont->GetGlyphWidth()*strlen(tempstr);
				break;
				
				case 'x':
				itoa(va_arg(arglist, int), tempstr, 16);
				DrawString(rx, ry, tempstr);
				rx += curfont->GetGlyphWidth()*strlen(tempstr);
				break;

				case 's':
				strcpy(tempstr, va_arg(arglist, char*));
				DrawString(rx, ry, tempstr);
				rx += curfont->GetGlyphWidth()*strlen(tempstr);
				break;
				
				case '%':
				DrawChar(rx, ry, '%');
				rx += curfont->GetGlyphWidth();
				break;			
			}
			i++;
		}
		
		if(rx > 124 || str[i] == '\n')
		{
			ry += curfont->GetGlyphHeight();
			rx = x;
		}	
	}
}
