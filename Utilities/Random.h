//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <cstdlib>


inline void
SetRandSeed(const int seed) 
{
	srand(seed);
}

inline int
RandInt(void) 
{
	return (rand());
}

inline float
RandFloat(void) 
{
	return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
}

inline float 
RandFloat(float low, float high) 
{
	return (RandFloat() * (high - low) + low);
}

inline int
RandInt(int low, int high) 
{
	return ((int)(RandFloat(0, (float)high - (float)low + 1.0f) + (float)low));
}