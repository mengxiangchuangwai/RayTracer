//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/PartialCylinder.h"
#include <cmath>

PartialCylinder::PartialCylinder(Material* mp)
    : GeometricObject(mp)
    , m_y0(0)
    , m_y1(1)
    , m_radius(1)
	, m_phi1(0.0)
	, m_phi2(TWO_PI)
{}


PartialCylinder::PartialCylinder(const double y0, 
								 const double y1, 
								 const double radius, 
								 const double azimuthMin, 
								 const double azimuthMax, 
								 Material* mp)
    : GeometricObject(mp)
    , m_y0(y0)
    , m_y1(y1)
    , m_radius(radius)
	, m_phi1(azimuthMin  * PI_ON_180)
	, m_phi2(azimuthMax  * PI_ON_180)
{}


PartialCylinder::PartialCylinder(const PartialCylinder& other)
	: GeometricObject(other)
    , m_y0(other.m_y0)
    , m_y1(other.m_y1)
    , m_radius(other.m_radius)
	, m_phi1(other.m_phi1)
	, m_phi2(other.m_phi2)
{}


PartialCylinder& 
PartialCylinder::operator= (const PartialCylinder& rhs) 
{
    if( this == &rhs )
        return(*this);

    GeometricObject::operator= (rhs);

    m_y0		= rhs.m_y0;
    m_y1		= rhs.m_y1;
    m_radius	= rhs.m_radius;
	m_phi1		= rhs.m_phi1;
	m_phi2		= rhs.m_phi2;
    
	return(*this);
}


PartialCylinder* 
PartialCylinder::Clone(void) const 
{
    return (new PartialCylinder(*this));
}


void 
PartialCylinder::UpdateBoundingBox() 
{
    m_bbox.p0 = Point3D(-m_radius, m_y0, -m_radius);
    m_bbox.p1 = Point3D(+m_radius, m_y1, +m_radius);
}


bool 
PartialCylinder::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
    const Vector3D& d = ray.d;
    const Point3D&  o = ray.o;

    double a = d.x * d.x + d.z * d.z;
    double b = 2.0 * (o.x * d.x + o.z * d.z);
    double c = o.x * o.x + o.z * o.z - m_radius * m_radius;
    double disc = b * b - 4.0 * a * c;
    double tval, phi;

    if( disc >= 0 ) 
	{
		bool finish = false;
        tval = (-b - sqrt(disc)) / (2.0 * a);

loop:
        if( tval > kEpsilon ) 
		{
			Point3D hit = o + d * tval;
			phi = atan2(hit.x, hit.z);

			if( phi < 0.0 )
				phi += TWO_PI;
            
			if( hit.y >= m_y0 && hit.y <= m_y1 && phi >= m_phi1 && phi <= m_phi2 ) 
			{
                tmin = tval;
                sr.normal = Normal(hit.x / m_radius, 0.0, hit.z / m_radius);
                if( -d * sr.normal < 0.0 ) 
					sr.normal = -sr.normal;
                sr.localHitPoint = hit;
                return (true);
            }
        }


		if( !finish && 0 != disc )
		{
			finish = true;
			tval = (-b + sqrt(disc)) / (2.0 * a);
			goto loop;
		}
    }

    return (false);
}


bool 
PartialCylinder::ShadowHit(const Ray& ray, double& tmin) const 
{
    if( !m_shadowing )
		return (false);

    const Vector3D& d = ray.d;
    const Point3D&  o = ray.o;

    double a = d.x * d.x + d.z * d.z;
    double b = 2.0 * (o.x * d.x + o.z * d.z);
    double c = o.x * o.x + o.z * o.z - m_radius * m_radius;
    double disc = b * b - 4.0 * a * c;
    double tval, phi;

    if( disc >= 0 ) 
	{
		bool finish = false;
        tval = (-b - sqrt(disc)) / (2.0 * a);
       
loop:
        if( tval > kEpsilon ) 
		{
			Point3D hit = o + d * tval;
			phi = atan2(hit.x, hit.z);

			if( phi < 0.0 )
				phi += TWO_PI;
            
			if( hit.y >= m_y0 && hit.y <= m_y1 && phi >= m_phi1 && phi <= m_phi2 ) 
			{
                tmin = tval;
                return (true);
            }
        }


        if( !finish && 0 != disc )
		{
			finish = true;
			tval = (-b + sqrt(disc)) / (2.0 * a);
			goto loop;
		}
    }

    return (false);
}