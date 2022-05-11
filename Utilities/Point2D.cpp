//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Utilities/Point2D.h"

Point2D::Point2D(void)
	: x(0.0), y(0.0)
{}


Point2D::Point2D(const float val)
	: x(val), y(val)
{}


Point2D::Point2D(const float x1, const float y1)
	: x(x1), y(y1)
{}


Point2D::Point2D(const Point2D& rhs)
	: x(rhs.x), y(rhs.y)
{}


Point2D::~Point2D(void) 
{}


Point2D& 							
Point2D::operator= (const Point2D& rhs) 
{
	if( this == &rhs )
		return (*this);

	x = rhs.x;
	y = rhs.y;

	return (*this);
}