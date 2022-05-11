//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/Plane.h"

Plane::Plane(Material* mp)
	: GeometricObject(mp)
	, m_point(0.0)
	, m_normal(0, 1, 0)
{}


Plane::Plane(const Point3D& point, const Normal& normal)
	: GeometricObject()
	, m_point(point)
	, m_normal(normal)
{
		m_normal.Normalize();
}


Plane::Plane(const Plane& other)
	: GeometricObject(other)
	, m_point(other.m_point)
	, m_normal(other.m_normal)
{}


Plane*
Plane::Clone(void) const 
{
	return (new Plane(*this));
}


Plane&
Plane::operator=(const Plane& rhs) 
{
	if( this == &rhs )
		return (*this);

	GeometricObject::operator= (rhs);
	m_point = rhs.m_point;
	m_normal = rhs.m_normal;

	return (*this);
}


Plane::~Plane(void)
{}


bool
Plane::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
	double tv = (m_point - ray.o) * m_normal / (ray.d * m_normal);
    double delta = 0.001;

	if( tv > delta ) 
	{
		tmin = tv;
		sr.normal = m_normal;
		sr.localHitPoint = ray.o + tv * ray.d;

		return (true);
	}

	return (false);
}


bool
Plane::ShadowHit(const Ray& ray, double& tmin) const 
{
	if( !m_shadowing )
		return (false);

	double tv = (m_point - ray.o) * m_normal / (ray.d * m_normal);
    double delta = 0.001;

	if( tv > delta ) 
	{
		tmin = tv;
		return (true);
	}

	return (false);
}