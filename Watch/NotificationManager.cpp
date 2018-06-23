/*
Victor Meriqui
Created 05/06/2018
*/

#include "NotificationManager.h"
#include "MathUtil.h"

#include "Images.h"
#include <string.h>

NotificationManager::NotificationManager()
{
	notification_list_c = 0;
	
	state = SELECTING_NOTIFICATION;
	cursor_idx = 0;
}

NotificationManager::~NotificationManager()
{
	
}

void NotificationManager::Draw(OLED* oled)
{
	uint8_t scr_center_x = oled->GetScreenWidth()/2;
	uint8_t scr_center_y = oled->GetScreenHeight()/2; 

	oled->SetFont(SMALL);
	
	uint8_t fontw = oled->GetFontWidth();
	uint8_t fonth = oled->GetFontHeight();	
	
	uint8_t strsize = DigitCount(notification_list_c) + strlen(" Notifications");
	oled->DrawStringF(scr_center_x - (strsize*fontw/2), 0, "%d Notifications", notification_list_c);

	if (state == SELECTING_NOTIFICATION)
	{
		uint8_t y = 7;	
		uint8_t offset = 0;
		for (uint8_t i = 0; i < notification_list_c; i++)
		{
			if (i == cursor_idx)
			{
				offset = 7;
				oled->DrawBitmap(&bmp_selectarrow, 0, 3, 4, 5, 0, y);		
			}
			
			oled->DrawString(offset, y, notification_list[i].appname);
			//oled->DrawString(0, y+fonth, notification_list[i].title);
			//oled->DrawString(0, y+fonth*2, notification_list[i].content);
			
			y += fonth*2;
		}
	}	
	else
	{
		oled->DrawString(scr_center_x-strlen(notification_list[cursor_idx].appname)*fontw/2, 2*fonth, notification_list[cursor_idx].appname);
		oled->DrawString(scr_center_x-strlen(notification_list[cursor_idx].title)*fontw/2, 4*fonth, notification_list[cursor_idx].title);
		oled->DrawString(0, 6*fonth, notification_list[cursor_idx].content);
		
	}
	
}

void NotificationManager::AddNotification(Notification notification)
{
	notification_list[notification_list_c++] = notification;
}

Notification NotificationManager::GetLastNotification()
{

	return notification_list[notification_list_c-1];
}

uint8_t NotificationManager::GetNotificationCount()
{
	return notification_list_c;
}

void NotificationManager::Up()
{	
	if (state == SELECTING_NOTIFICATION && cursor_idx < notification_list_c-1)
		cursor_idx++;
}

void NotificationManager::Down()
{
	if (state == SELECTING_NOTIFICATION && cursor_idx > 0)
		cursor_idx--;
}

void NotificationManager::Enter()
{	
	if (state == SELECTING_NOTIFICATION)
	{
		state = READING_NOTIFICATION;
		return;
	}
	
	if (state == READING_NOTIFICATION)
	{
		state = SELECTING_NOTIFICATION;
		return;
	}	
}

void NotificationManager::Home()
{

}
