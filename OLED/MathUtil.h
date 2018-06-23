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


#endif