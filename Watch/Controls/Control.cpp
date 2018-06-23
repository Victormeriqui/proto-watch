/*
Victor Meriqui
Created 24/07/2017
*/

#include "Control.h"

#include <string.h>

Control::Control()
{
	label = new char[21];
	
	strcpy(label, "Undefined");
	
	width = 0;
	height = 0;
	state = IDLE_CONTROL;
}

Control::~Control()
{
	delete label;
}

Control::Control(const char* name)
{
	label = new char[21];
	
	strcpy(label, name);
	width = 0;
	height = 0;
	state = IDLE_CONTROL;
}

const char* Control::GetLabel()
{
	return label;
}

uint8_t Control::GetWidth()
{
	return width;
}

uint8_t Control::GetHeight()
{
	return height;
}

void Control::Up()
{
	
}

void Control::Down()
{
	
}

void Control::Enter()
{
	
}

ControlState Control::GetState()
{
	return state;
}

void Control::SetState(ControlState state)
{
	this->state = state;
}