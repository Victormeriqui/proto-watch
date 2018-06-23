/*
Victor Meriqui
Created 03/08/2017
*/

#include "Watch.h"

#include <Arduino.h>

#include "OptionsMenu.h"
#include "Bitmap.h"
#include "MathUtil.h"
#include "Controls/RadioSelect.h"

#include <math.h>
#include <string.h>


Watch::Watch()
{
	state = WATCHFACE_WATCH;
	
	optionsmenu = new OptionsMenu();
	notificationmanager = new NotificationManager();
}

Watch::~Watch()
{
	delete optionsmenu;
	delete notificationmanager;
}

void Watch::DrawBatteryIndicator(OLED* oled, uint8_t x, uint8_t y)
{
	uint8_t batw = 4;
	uint8_t bath = 6;
	uint8_t tipw = 2;
	uint8_t tiph = 1;
	
	uint8_t fontw = oled->GetFontWidth();
	uint8_t fonth = oled->GetFontHeight();	
			
	oled->DrawRect(x-batw, y+tiph, batw, bath);
	oled->DrawRect(x-tipw-1, y, 2, 2);
	oled->DrawString(x-batw-fontw*2, y+1, "52");
}

void Watch::DrawDigitalTime(OLED* oled, uint8_t is24h, uint8_t x, uint8_t y)
{
	char format[10] = "";
	uint8_t formatedhours = is24h ? hours : Interpolate(hours, 0, 24, 0, 12);
	uint8_t width = is24h ? 8 : 10;
	uint8_t fontw;
	uint8_t fonth;
	
	if (formatedhours < 10)
		strcpy(format, "0%d:");			
	else
		strcpy(format, "%d:");
	
	if (minutes < 10)
		strcat(format, "0%d:");
	else
		strcat(format, "%d:");
	
	if (seconds < 10)
		strcat(format, "0%d");
	else
		strcat(format, "%d");
	
	if (!is24h)
		strcat(format, (hours < 12 ? "AM" : "PM"));

	oled->SetFont(LARGE);
	
	fontw = oled->GetFontWidth();
	fonth = oled->GetFontHeight();
	
	oled->DrawStringF(x-(fontw*width/2), y-fonth/2, format, formatedhours, minutes, seconds);	
}

void Watch::Draw(OLED* oled)
{
	uint8_t fontw = 0;
	uint8_t fonth = 0;
	uint8_t scrw = 128;
	uint8_t scrh = 64;
	
	if (state == WATCHFACE_WATCH)
	{
		RadioSelect* styler = (RadioSelect*)(optionsmenu->GetCategory("Watch")->GetControl("Style"));
		RadioSelect* formatr = (RadioSelect*)(optionsmenu->GetCategory("Watch")->GetControl("Time Format"));
		
		const char* watchstyle = styler->GetChosenValue();
		const char* watchformat = formatr->GetChosenValue();
		uint8_t is24h = (strcmp(watchformat, "24h") == 0);
		
		if (millis() - prevtime > 100)
		{
			prevtime = millis();
			seconds++;
			
			if (seconds >= 60)
			{
				minutes++;
				seconds = 0;
				
				if (minutes >= 60)
				{
					hours++;
					minutes = 0;
					
					if (hours >= 24)
						hours = 0;									
				}	
			}
		}			
			
	/*	if (strcmp(watchstyle, "Round") == 0)
		{
			float radius = 32;
			oled->DrawCircle(scrw/2, scrh/2, radius, 20);
		
			double secondsrot = Interpolate(seconds, 0, 60, 0, PI*2);
			double minutesrot = Interpolate(minutes, 0, 60, 0, PI*2);
			double hoursrot = Interpolate(hours, 0, is24h ? 24 : 12, 0, PI*2);
			float startclock = 3*(PI/2);
		
			oled->DrawLine(scrw/2, scrh/2, scrw/2+cos(startclock+secondsrot)*radius, scrh/2+sin(startclock+secondsrot)*radius);
			oled->DrawLine(scrw/2, scrh/2, scrw/2+cos(startclock+minutesrot)*radius/1.5, scrh/2+sin(startclock+minutesrot)*radius/1.5);
			oled->DrawLine(scrw/2, scrh/2, scrw/2+cos(startclock+hoursrot)*radius/2, scrh/2+sin(startclock+hoursrot)*radius/2);
			
			oled->SetFont(SMALL);
			fontw = oled->GetFontWidth();
			fonth = oled->GetFontHeight();
			
			float part = PI/6;
			
			if (is24h)
				part = PI/12;
			
			uint8_t part_c = 1;
			for (float ang = 0; ang < PI*2+part; ang += 0.03)
			{		
		
				if (ang >= part*part_c)
				{	
					int8_t rcos = (int8_t)(cos(startclock+(float)ang)*(radius-6));
					int8_t rsin = (int8_t)(sin(startclock+(float)ang)*(radius-6));
			
					if (!is24h || part_c % 2 == 0)
					{
						uint8_t digitoff = (part_c > 9) ? fontw/2 : 0;
						oled->DrawString(scrw/2+rcos-digitoff, scrh/2-2+rsin, part_c);
					}
					part_c++;
				}
			}
		}*/
	//	else if (strcmp(watchstyle, "Digital") == 0)
		{

			uint8_t bigfonth = 0;
			
			char msg[40];
			bool ended;
				
			oled->SetFont(SMALL);
			fontw = oled->GetFontWidth();
			fonth = oled->GetFontHeight();	
	
			DrawBatteryIndicator(oled, scrw-5, 0);
			oled->DrawString(0, 0, "Wed, Sept 23");
			oled->DrawStringF(40, 0, "%d Notifications", notificationmanager->GetNotificationCount());
			oled->SetFont(LARGE);
			bigfonth = oled->GetFontHeight();
			
			DrawDigitalTime(oled, is24h, scrw/2, scrh/2);
			
			oled->SetFont(SMALL);
			fontw = oled->GetFontWidth();
			fonth = oled->GetFontHeight();

			
			Notification lastnot = notificationmanager->GetLastNotification();
			GetStringSection(lastnot.content, scroll, 29, msg, &ended);
			
			if (ended)
			{
				if (millis() - prevmillis > 2000)
				{
					scroll = 0;
					delay = 2000;
					prevmillis = millis();
				}
			}
			else
			{
				if (millis() - prevmillis > delay)
				{
					prevmillis = millis();
					scroll++;
					delay = 100	;
				}
			}
			char title[400];
			strcpy(title, lastnot.appname);
			strcat(title, " - ");
			strcat(title, lastnot.title);
			strcat(title, ":");
			title[strlen(title)] = '\0';
			
			oled->DrawStringF(0, scrh/2+bigfonth/2+3+fonth, "%s", title);
			oled->DrawStringF(0, scrh/2+bigfonth/2+3+fonth*2, msg);
		}
		
	
		
	
		
		/*float part = PI/6;
		uint8_t part_c = 1;
		for (float ang = 0; ang < PI*2+part; ang += 0.03)
		{			
			if (ang >= part*part_c)
			{
				float testradius = 15;
				
				while (1)
				{
					testradius += 0.5;
					
					int8_t testcos = (int8_t)(cos(startclock+(float)ang)*testradius);
					int8_t testsin = (int8_t)(sin(startclock+(float)ang)*testradius);
					uint8_t testx = scrw/2 + testcos;
					uint8_t testy = scrh/2 + testsin;
					
					if (testx <= 0 || testx >= scrw)
						break;
					
					if (testy <= 0 || testy >= scrh)
						break;
				}
				
				//if (part_c % 2 == 0)
				{
					int8_t rcos = (int8_t)(cos(startclock+(float)ang)*(testradius-5));
					int8_t rsin = (int8_t)(sin(startclock+(float)ang)*(testradius-5));
					
					uint8_t digitoff = (part_c > 9) ? fontw/2 : 0;
					oled->DrawString(scrw/2+rcos-digitoff, scrh/2+rsin, part_c);
					
					oled->DrawLine(scrw/2+cos(startclock+ang)*(testradius), scrh/2+sin(startclock+ang)*(testradius), scrw/2+cos(startclock+ang)*(testradius-5), scrh/2+sin(startclock+ang)*(testradius-5));
				}
				part_c++;
				}
			
		}*/		

	}
	
	if (state == OPTIONS_WATCH)
		optionsmenu->Draw(oled);
	
	if (state == NOTIFICATIONS_WATCH)
		notificationmanager->Draw(oled);
}

void Watch::GetStringSection(char* src, uint8_t start, uint8_t width, char* ret, bool* ended)
{
	uint8_t i;
	uint8_t ret_c = 0;

	for (i = start; i < start+width; i++)
	{
		ret[ret_c++] = src[i];
		
		if (!(*ended) && src[i+1] == '\0')
			(*ended) = true;
	}	
	
	if (!(*ended))
	{
		ret[ret_c++] = '.';
		ret[ret_c++] = '.';
		ret[ret_c++] = '.';
	}
	
	ret[ret_c] = '\0';
}

void Watch::AddNotification(Notification notification)
{
	notificationmanager->AddNotification(notification);
}

void Watch::Up()
{	
	if (state == NOTIFICATIONS_WATCH)
		notificationmanager->Up();

	if (state == OPTIONS_WATCH)
		optionsmenu->Up();
	
	if (state == WATCHFACE_WATCH)
	{
		state = OPTIONS_WATCH;
		optionsmenu->SetState(SELECTING_OPTIONS);
	}
}

void Watch::Down()
{
	if (state == NOTIFICATIONS_WATCH)
		notificationmanager->Down();
	
	if (state == OPTIONS_WATCH)
		optionsmenu->Down();
	
	if (state == WATCHFACE_WATCH)
	{
		state = OPTIONS_WATCH;
		optionsmenu->SetState(SELECTING_OPTIONS);
	}
}

void Watch::Enter()
{	
	if (state == NOTIFICATIONS_WATCH)
		notificationmanager->Enter();
	
	if (state == OPTIONS_WATCH)
		optionsmenu->Enter();
	
	if (state == WATCHFACE_WATCH)
	{
		state = OPTIONS_WATCH;
		optionsmenu->SetState(SELECTING_OPTIONS);
	}
}

void Watch::Home()
{
	switch (state)
	{
		case NOTIFICATIONS_WATCH:
		state = WATCHFACE_WATCH;
		break;
		
		case WATCHFACE_WATCH:
		state = NOTIFICATIONS_WATCH;
		break;
		
		case OPTIONS_WATCH:
		state = WATCHFACE_WATCH;
		break;
	}
}

WatchState Watch::GetState()
{
	return state;
}
