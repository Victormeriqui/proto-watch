/*
Victor Meriqui
Created 23/06/2018
*/

#ifndef WATCH_H
#define WATCH_H

#include "OptionsMenu.h"
#include "NotificationManager.h"

enum WatchState
{
	WATCHFACE_WATCH,
	OPTIONS_WATCH,
	NOTIFICATIONS_WATCH
};

class Watch
{
	WatchState state;
	uint8_t curinfo;
	
	NotificationManager* notificationmanager;
	OptionsMenu* optionsmenu;

	void SetMenuMenuSelector();
	
	void GetStringSection(char* src, uint8_t start, uint8_t width, char* ret, bool* ended);
	
	unsigned long prevmillis = 0;
	unsigned long prevtime = 0;
		
	uint8_t scroll = 0;
	uint16_t delay = 50;
	
	uint8_t seconds = 0;
	uint8_t minutes = 55;
	uint8_t hours = 19;

	private:
		void DrawBatteryIndicator(OLED* oled, uint8_t x, uint8_t y);
		void DrawDigitalTime(OLED* oled, uint8_t is24h, uint8_t x, uint8_t y);
	
	public:
	
		Watch();
		~Watch();
			
		void Draw(OLED* oled);
				
		void AddNotification(Notification notification);
			
		void Up();
		void Down();
		void Enter();
		void Home();
		
		WatchState GetState();
		
};

#endif