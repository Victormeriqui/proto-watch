/*
Victor Meriqui
Created 23/05/2018
*/
#ifndef IMAGES_H
#define IMAGES_H 

#include "Bitmap.h"


static uint8_t asd[] = 
{
	0x0, 0xfe, 0xff, 0x3, 0x3, 0x3, 0x3, 0xff, 0xfe, 0x0, 0x0, 0x0, 0x4, 0x6, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x83, 0x83, 0x83, 0x83, 0x83, 0xff, 0xfe, 0x0, 0x0, 0x83, 0x83, 0x83, 0x83, 0x83, 0x83, 0xff, 0xfe, 0x0, 0x0, 0xff, 0xff, 0x80, 0x80, 0x80, 0x80, 0xff, 0xff, 0x0, 0x0, 0xfe, 0xff, 0x83, 0x83, 0x83, 0x83, 0x83, 0x3, 0x0, 0x0, 0xfe, 0xff, 0x83, 0x83, 0x83, 0x83, 0x83, 0x3, 0x0, 0x3, 0x3, 0x3, 0x3, 0x3, 0x83, 0xe3, 0x7f, 0x1f, 0xf, 0x0, 0x7e, 0xff, 0x83, 0x83, 0x83, 0x83, 0xff, 0x7e, 0x0, 0x0, 0xfe, 0xff, 0x83, 0x83, 0x83, 0x83, 0xff, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x1c, 0x1c, 0x1c, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xff, 0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xff, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0x0, 0x0, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xff, 0x7f, 0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1, 0xff, 0xff, 0x0, 0x0, 0xc0, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xff, 0x7f, 0x0, 0x0, 0x7f, 0xff, 0xc1, 0xc1, 0xc1, 0xc1, 0xff, 0x7f, 0x0, 0x0, 0xc0, 0xf0, 0x3c, 0xe, 0x7, 0x1, 0x0, 0x0, 0x0, 0x0, 0x7e, 0xff, 0xc1, 0xc1, 0xc1, 0xc1, 0xff, 0x7e, 0x0, 0x0, 0xc0, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xff, 0x7f, 0x0, 0x0, 0x0, 0x0, 0x38, 0x38, 0x38, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
};

static uint8_t buff_bluetooth[] = 
{
	0x0, 0x0, 0x0, 0x0, 0x0, 0x30, 0x60, 0xC0, 0x80, 0x0, 0x0, 0xFF, 0xFF, 0x6, 0xC, 0x18, 0xB0, 0xE0, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x81, 0xC3, 0x66, 0xFF, 0xFF, 0x3C, 0x66, 0xC3, 0x81, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xC, 0x6, 0x3, 0x1, 0x0, 0x0, 0xFF, 0xFF, 0x60, 0x30, 0x18, 0xD, 0x7, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 
};
static Bitmap bmp_bluetooth = Bitmap(24, 24, buff_bluetooth);

static uint8_t buff_watch[] = 
{
	0x0, 0xC0, 0x20, 0x10, 0x8, 0x4, 0x2, 0x2, 0x2, 0x1, 0x81, 0x7, 0x7, 0x1, 0x1, 0x2, 0x82, 0x42, 0x4, 0x8, 0x10, 0x20, 0xC0, 0x0, 0x7E, 0x99, 0x18, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1E, 0x18, 0x4, 0x2, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x18, 0x99, 0x7E, 0x0, 0x3, 0x4, 0x8, 0x10, 0x20, 0x40, 0x40, 0x40, 0x80, 0x80, 0xE0, 0xE0, 0x80, 0x80, 0x40, 0x40, 0x40, 0x20, 0x10, 0x8, 0x4, 0x3, 0x0, 
};
static Bitmap bmp_watch = Bitmap(24, 24, buff_watch);

static uint8_t buff_bell[] = 
{
	0x0, 0x0, 0x0, 0x80, 0x40, 0x20, 0x10, 0x8, 0x8, 0x4, 0x4, 0x6, 0x6, 0x4, 0x4, 0x8, 0x8, 0x10, 0x20, 0x40, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xFF, 0x0, 0x0, 0x0, 0x0, 0x20, 0x30, 0x2F, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x60, 0xE0, 0xE0, 0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x2F, 0x30, 0x20, 0x0, 
};
static Bitmap bmp_bell = Bitmap(24, 24, buff_bell);

static uint8_t buff_gear[] = 
{
	0x0, 0x0, 0x10, 0xB8, 0x7C, 0x38, 0x10, 0x8, 0x8, 0x4, 0x87, 0x87, 0x87, 0x87, 0x4, 0x8, 0x8, 0x10, 0x38, 0x7C, 0xB8, 0x10, 0x0, 0x0, 0x3C, 0x3C, 0x7E, 0x81, 0x0, 0x0, 0x0, 0x3C, 0xC3, 0x81, 0x0, 0x0, 0x0, 0x0, 0x81, 0xC3, 0x3C, 0x0, 0x0, 0x0, 0x81, 0x7E, 0x3C, 0x3C, 0x0, 0x0, 0x8, 0x1D, 0x3E, 0x1C, 0x8, 0x10, 0x10, 0x20, 0xE1, 0xE1, 0xE1, 0xE1, 0x20, 0x10, 0x10, 0x8, 0x1C, 0x3E, 0x1D, 0x8, 0x0, 0x0, 
};
static Bitmap bmp_gear = Bitmap(24, 24, buff_gear);

static uint8_t buff_selectarrow[] = { 0x88, 0xD8, 0x70, 0x20 };
static Bitmap bmp_selectarrow = Bitmap(4, 8, buff_selectarrow);

static uint8_t buff_selectarrowfill[] = {0xF8, 0xF8, 0x70, 0x20};
static Bitmap bmp_selectarrowfill = Bitmap(4, 8, buff_selectarrowfill);

static uint8_t buff_uparrow[] = { 0xE0, 0x30, 0xE0};
static Bitmap bmp_uparrow = Bitmap(3, 8, buff_uparrow);

static uint8_t buff_downarrow[] = { 0x70, 0xC0, 0x70};
static Bitmap bmp_downarrow = Bitmap(3, 8, buff_downarrow);

#endif