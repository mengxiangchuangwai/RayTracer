//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __MATHS__
#define __MATHS__


#include "../Utilities/Constants.h"

extern int
SolveQuadric(double c[3], double s[2]);


extern int
SolveCubic(double c[4], double s[3]);


extern int
SolveQuartic(double c[5], double s[4]);


template<typename T>
inline T max2(T a, T b) 
{
	return((a > b) ? a : b);
}


template<typename T>
inline T max3(T a, T b, T c)
{
	return(max2(max2(a, b), c));
}


template<typename T>
inline T min2(T a, T b) 
{
	return((a < b) ? a : b);
}


template<typename T>
inline T min3(T a, T b, T c)
{
	return (min2(min2(a, b), c));

}


template<typename T>
inline void swap2(T& a, T& b) 
{
	T temp = a;
	a = b;
	b = temp;
}


template<typename T1, typename T2>
inline T1 clamp(T1 value, T2 low, T2 high) 
{
	return (value < low ? low : (value > high ? high : value));
}


template<typename T>
inline T degreeToRadian(T degree) 
{
	return (T)(degree * PI_ON_180);
}


template<typename T>
inline T radianToDegree(T radian) 
{
	return (T)(radian * (180.0 * invPI));
}


#endif
