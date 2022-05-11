//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Utilities/RGBColor.h"

RGBColor::RGBColor(void)
	: r(0.0), g(0.0), b(0.0) 							
{}


RGBColor::RGBColor(float c)
	: r(c), g(c), b(c) 							
{}


RGBColor::RGBColor(float r1, float g1, float b1)	
	: r(r1), g(g1), b(b1)
{}


RGBColor::RGBColor(const RGBColor& c)
	: r(c.r), g(c.g), b(c.b)
{} 				 


RGBColor::~RGBColor(void)		
{}


RGBColor& 											
RGBColor::operator= (const RGBColor& rhs) 
{
	if( this == &rhs )
		return (*this);

	r = rhs.r; g = rhs.g; b = rhs.b;

	return (*this);
}


const RGBColor RGBColor::Black = RGBColor(0.0f);
const RGBColor RGBColor::White = RGBColor(1.0f);
const RGBColor RGBColor::Red = RGBColor(1.0f, 0.0f, 0.0f);
const RGBColor RGBColor::Yellow = RGBColor(1.0f, 1.0f, 0.0f);
const RGBColor RGBColor::DarkYellow = RGBColor(0.61f, 0.61f, 0.0f);
const RGBColor RGBColor::Brown = RGBColor(0.71f, 0.4f, 0.16f);
const RGBColor RGBColor::Orange = RGBColor(1.0f, 0.75, 0.0f);
const RGBColor RGBColor::Green = RGBColor(0.0f, 0.6f, 0.3f);
const RGBColor RGBColor::LightGreen = RGBColor(0.65f, 1.0f, 0.3f);
const RGBColor RGBColor::DarkGreen = RGBColor(0.0f, 0.41f, 0.0f);
const RGBColor RGBColor::LightPurple = RGBColor(0.65f, 0.3f, 1.0f);
const RGBColor RGBColor::DarkPurple = RGBColor(0.5f, 0.0f, 1.0f);
const RGBColor RGBColor::Grey = RGBColor(0.25f);