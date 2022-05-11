//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <cmath>
#include "../Utilities/Point3D.h"

Point3D::Point3D()
	: x(0), y(0), z(0)
{}


Point3D::Point3D(const double a)
	: x(a), y(a), z(a)
{}


Point3D::Point3D(const double a, const double b, const double c)
	: x(a), y(b), z(c)
{}


Point3D::Point3D(const Point3D& p)
	: x(p.x), y(p.y), z(p.z)
{}


Point3D::~Point3D() 
{}


Point3D& 
Point3D::operator= (const Point3D& rhs) 
{	
	if( this == &rhs )
		return (*this);

	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}


// distance between two points

double
Point3D::Distance(const Point3D& p) const 
{
	return (sqrt(	(x - p.x) * (x - p.x) 
				+ 	(y - p.y) * (y - p.y)
				+	(z - p.z) * (z - p.z) ));
}


// multiplication by a matrix on the left

Point3D 						
operator* (const Matrix& mat, const Point3D& p) 
{
	return (Point3D(mat.m[0][0] * p.x + mat.m[0][1] * p.y + mat.m[0][2] * p.z + mat.m[0][3],
					mat.m[1][0] * p.x + mat.m[1][1] * p.y + mat.m[1][2] * p.z + mat.m[1][3],
					mat.m[2][0] * p.x + mat.m[2][1] * p.y + mat.m[2][2] * p.z + mat.m[2][3]));
}