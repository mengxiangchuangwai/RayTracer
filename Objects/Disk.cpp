//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/Disk.h"

Disk::Disk(Material* mp)
    : GeometricObject(mp)
    , m_center(0)
    , m_normal(0)
    , m_radius(0)
{}


Disk::Disk(const Point3D& center, const Normal& normal, const double radius, Material* mp)
    : GeometricObject(mp)
    , m_center(center)
    , m_normal(normal)
    , m_radius(radius) 
{
    m_normal.Normalize();
}


Disk::Disk(const Disk& other)
    : GeometricObject(other)
    , m_center(other.m_center)
    , m_normal(other.m_normal)
    , m_radius(other.m_radius) 
{
    m_normal.Normalize();
}


Disk& 
Disk::operator= (const Disk& rhs)
{
    if( this == &rhs )
        return(*this);

    GeometricObject::operator= (rhs);
    m_center = rhs.m_center;
    m_normal = rhs.m_normal;
    m_radius = rhs.m_radius;
    m_normal.Normalize();
    return (*this);
}


Disk* 
Disk::Clone(void) const 
{
    return (new Disk(*this));
}


Disk::~Disk(void) 
{}


bool 
Disk::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
    double tv = (m_center - ray.o) * m_normal / (ray.d * m_normal);
    if( tv <= kEpsilon )
        return (false);

    Point3D pt = ray.o + tv * ray.d;
    if( m_center.DistanceSq(pt) < (m_radius * m_radius) ) 
	{
        tmin = tv;
        sr.normal = m_normal;
        sr.localHitPoint = pt;
        return (true);
    }

    return (false);
}


bool 
Disk::ShadowHit(const Ray& ray, double& tmin) const
{
	if( !m_shadowing )
		return (false);

    double tv = (m_center - ray.o) * m_normal / (ray.d * m_normal);
    if( tv <= kEpsilon )
        return (false);

    Point3D pt = ray.o + tv * ray.d;
    if( m_center.DistanceSq(pt) < (m_radius * m_radius) ) 
	{
        tmin = tv;
        return (true);
    }

    return (false);
}