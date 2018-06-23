/*
Victor Meriqui
Created 05/06/2018
*/

#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <Arduino.h>

#include "OLED.h"

typedef struct Notification
{
	char appname[31];
	char title[41];
	char content[101];
} Notification;

enum NotificationState
{
	SELECTING_NOTIFICATION,
	READING_NOTIFICATION
};

class NotificationManager
{
	Notification notification_list[10];
	uint8_t notification_list_c;
	
	NotificationState state;
	
	uint8_t cursor_idx;
	
	
	public:
	
		NotificationManager();
		~NotificationManager();
			
		void Draw(OLED* oled);
		
		void AddNotification(Notification notification);
		
		Notification GetLastNotification();
		
		uint8_t GetNotificationCount();
		
		void Up();
		void Down();
		void Enter();
		void Home();
		
};

#endif