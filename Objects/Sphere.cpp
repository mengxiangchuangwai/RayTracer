//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <cmath>
#include "../Objects/Sphere.h"
#include "../Utilities/Constants.h"

Sphere::Sphere(Material* mp)
	: GeometricObject(mp)
	, m_center(0.0)
	, m_radius(1.0)
{}


Sphere::Sphere(const Point3D& center, const double radius, Material* mp)
	: GeometricObject(mp)
	, m_center(center)
	, m_radius(radius)
{}


Sphere*
Sphere::Clone(void) const 
{
	return (new Sphere(*this));
}


Sphere::Sphere(const Sphere& other)
	: GeometricObject(other)
	, m_center(other.m_center)
	, m_radius(other.m_radius)
{}


Sphere&
Sphere::operator= (const Sphere& rhs)
{
	if( this == &rhs )
		return (*this);

	GeometricObject::operator= (rhs);
	m_center 		= rhs.m_center;
	m_radius		= rhs.m_radius;

	return (*this);
}


Sphere::~Sphere(void) 
{}


void
Sphere::UpdateBoundingBox()
{
    m_bbox.p0 = Point3D(m_center.x-m_radius, m_center.y-m_radius, m_center.z-m_radius);
    m_bbox.p1 = Point3D(m_center.x+m_radius, m_center.y+m_radius, m_center.z+m_radius);
}


bool 
Sphere::Intersect(const Ray& ray, double& tval) const 
{
	Vector3D	temp 	= ray.o - m_center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - m_radius * m_radius;
	double 		disc	= b * b - 4.0 * a * c;
    double		delta   = 0.001;

	if( disc < 0.0 )
		return (false);
	else 
	{
		double e = sqrt(disc);
		double denom = 2.0 * a;
		double t = (-b - e) / denom;    // smaller root

		if( t > delta ) 
		{
			tval = t;
			return (true);
		}

		t = (-b + e) / denom;    // larger root

		if( t > delta ) 
		{
			tval = t;
			return (true);
		}
	}

	return (false);
}