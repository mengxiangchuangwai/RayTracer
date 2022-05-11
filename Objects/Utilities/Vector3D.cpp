//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <cmath>
#include "../Utilities/Vector3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Point3D.h"

Vector3D::Vector3D(void)
	: x(0.0), y(0.0), z(0.0)							
{}


Vector3D::Vector3D(double val)
	: x(val), y(val), z(val)							
{}


Vector3D::Vector3D(double x1, double y1, double z1)	 
	: x(x1), y(y1), z(z1)
{}


Vector3D::Vector3D(const Vector3D& v)
	: x(v.x), y(v.y), z(v.z)
{}


Vector3D::Vector3D(const Normal& n)	 
	: x(n.x), y(n.y), z(n.z)
{}


Vector3D::Vector3D(const Point3D& p)	 
	: x(p.x), y(p.y), z(p.z)
{}


Vector3D::~Vector3D (void) 
{}


Vector3D& 
Vector3D::operator= (const Vector3D& rhs) 
{
	if( this == &rhs )
		return (*this);

	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}


Vector3D& 
Vector3D::operator= (const Normal& rhs) 
{
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}


Vector3D& 												
Vector3D::operator= (const Point3D& rhs) 
{
	x = rhs.x; y = rhs.y; z = rhs.z;
	return (*this);
}


double													
Vector3D::Length(void) 
{
	return (sqrt(x * x + y * y + z * z));
}


void 													
Vector3D::Normalize(void) 
{	
	double len = sqrt(x * x + y * y + z * z);
	x /= len; y /= len; z /= len;
}


Vector3D& 													
Vector3D::Hat(void) 
{	
	double len = sqrt(x * x + y * y + z * z);
	x /= len; y /= len; z /= len;
	return (*this);
} 


// multiplication by a matrix on the left

Vector3D 
operator* (const Matrix& mat, const Vector3D& v) 
{
	return (Point3D(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z,
					mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z,
					mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z));
}