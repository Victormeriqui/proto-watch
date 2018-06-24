/*
Victor Meriqui
Created 16/01/2018
*/


#ifndef MATHUTIL_HPP
#define MATHUTIL_HPP

#include <math.h>

inline int8_t DigitCount(int16_t val)
{
	return ((int8_t)log10(val))+1;
}

inline double Interpolate(double val, double fmin, double fmax, double tmin, double tmax)
{
	double fdist = fmax - fmin;
	double tdist = tmax - tmin;

	double scaled = (val - fmin) / fdist;

	return tmin + (scaled * tdist);
}

inline double Logb(double val, int8_t base)
{
	return log10(val) / log10(base);
}

inline int8_t GetMinValue(int8_t arr[], uint8_t arr_c)
{
	int8_t min = 0;
	for (uint8_t i = 0; i < arr_c; i++)
	{
		if (arr[i] < arr[min])
			min = i;
	}

	return arr[min];
}

inline int8_t GetMaxValue(int8_t arr[], int arr_c)
{
	int8_t max = 0;
	for (uint8_t i = 0; i < arr_c; i++)
	{
		if (arr[i] > arr[max])
			max = i;
	}

	return arr[max];
}

#endif