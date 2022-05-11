//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Utilities/Ray.h"

Ray::Ray (void)
	: o(0.0)
	, d(0.0, 0.0, 1.0) 
{}


Ray::Ray (const Point3D& origin, const Vector3D& dir)
	: o(origin) 
	, d(dir) 
{}


Ray::Ray (const Ray& other)
	: o(other.o)
	, d(other.d) 
{}


Ray& 
Ray::operator= (const Ray& rhs) 
{	
	if( this == &rhs )
		return (*this);
		
	o = rhs.o; 
	d = rhs.d; 

	return (*this);	
}


Ray::~Ray (void) 
{}