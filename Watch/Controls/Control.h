/*
Victor Meriqui
Created 23/06/2018
*/

#ifndef CONTROL_H
#define CONTROL_H

#include <OLED.H>

enum ControlState
{
	IDLE_CONTROL, //no cursor over
	CURSOROVER_CONTROL,
	INTERACTING_CONTROL,
};

class Control
{
	protected:
	
		uint8_t width;
		uint8_t height;
		
		char* label;
		
		ControlState state;
		
	public:

		Control();
		~Control();
		
		Control(const char* name);
		
		virtual void Draw(OLED* oled, uint8_t x, uint8_t y) = 0;
		
		virtual const char* GetLabel();
		virtual uint8_t GetWidth();
		virtual uint8_t GetHeight();		
		
		virtual void SetState(ControlState state);
		virtual ControlState GetState();
		
		virtual void Up();
		virtual void Down();
		virtual void Enter();
};

#endif