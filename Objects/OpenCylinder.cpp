//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/OpenCylinder.h"
#include <cmath>

OpenCylinder::OpenCylinder(Material* mp)
    : GeometricObject(mp)
    , m_y0(-1)
    , m_y1(1)
    , m_radius(1)
{}


OpenCylinder::OpenCylinder(const double y0, const double y1, const double radius, Material* mp)
    : GeometricObject(mp)
    , m_y0(y0)
    , m_y1(y1)
    , m_radius(radius)
{}


OpenCylinder::OpenCylinder(const OpenCylinder& other)
	: GeometricObject(other)
    , m_y0(other.m_y0)
    , m_y1(other.m_y1)
    , m_radius(other.m_radius)
{}


OpenCylinder& 
OpenCylinder::operator= (const OpenCylinder& rhs) 
{
    if( this == &rhs )
        return(*this);
   
    GeometricObject::operator= (rhs);
    m_y0 = rhs.m_y0;
    m_y1 = rhs.m_y1;
    m_radius = rhs.m_radius;
    return(*this);
}


OpenCylinder* 
OpenCylinder::Clone(void) const 
{
    return (new OpenCylinder(*this));
}


void 
OpenCylinder::UpdateBoundingBox() 
{
    m_bbox.p0 = Point3D(-m_radius, m_y0, -m_radius);
    m_bbox.p1 = Point3D(+m_radius, m_y1, +m_radius);
}


bool 
OpenCylinder::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
    const Vector3D& d = ray.d;
    const Point3D&  o = ray.o;

    double a = d.x * d.x + d.z * d.z;
    double b = 2.0 * (o.x * d.x + o.z * d.z);
    double c = o.x * o.x + o.z * o.z - m_radius * m_radius;
    double disc = b * b - 4.0 * a * c;

    if( disc >= 0 )
	{
		bool finish = false;
        double tval = (-b - sqrt(disc)) / (2.0 * a);
       
loop:
        if( tval > kEpsilon ) 
		{
			Point3D hit = o + d * tval;
            
			if( hit.y >= m_y0 && hit.y <= m_y1 ) 
			{
                tmin = tval;
                sr.normal = Normal(hit.x / m_radius, 0.0, hit.z / m_radius);
                if( -d * sr.normal < 0.0 ) sr.normal = -sr.normal;
                sr.localHitPoint = hit;
                return (true);
            }
        }
       
		if( !finish && disc != 0)
		{
			finish = true;
			tval = (-b + sqrt(disc)) / (2.0 * a);
			goto loop;
		}
    }

    return (false);
}


bool OpenCylinder::ShadowHit(const Ray& ray, double& tmin) const 
{
    if( !m_shadowing )
		return (false);

    const Vector3D& d = ray.d;
    const Point3D&  o = ray.o;

    double a = d.x * d.x + d.z * d.z;
    double b = 2.0 * (o.x * d.x + o.z * d.z);
    double c = o.x * o.x + o.z * o.z - m_radius * m_radius;
    double disc = b * b - 4.0 * a * c;

    if( disc >= 0 ) 
	{
		bool finish = false;
		double tval = (-b - sqrt(disc)) / (2.0 * a);
  
loop:
        if( tval > kEpsilon ) 
		{
			 Point3D hit = o + d * tval;

            if( hit.y >= m_y0 && hit.y <= m_y1 ) 
			{
                tmin = tval;
                return (true);
            }
        }

		if( !finish && disc != 0 )
		{
			finish = true;
			tval = (-b + sqrt(disc)) / (2.0 * a);
			goto loop;
		}
    }

    return (false);
}