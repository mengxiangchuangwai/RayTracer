//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/PartialCone.h"
#include <iostream>
#include <cmath>

PartialCone::PartialCone(Material* mp)
    : PartialCylinder(mp)
{}


PartialCone::PartialCone(const double y0, 
						 const double y1, 
						 const double radius, 
						 const double azimuthMin, 
						 const double azimuthMax, 
						 Material* mp)
    : PartialCylinder(y0, y1, radius, azimuthMin, azimuthMax, mp)
{}


PartialCone::PartialCone(const PartialCone& other)
	: PartialCylinder(other)
{}


PartialCone& 
PartialCone::operator= (const PartialCone& rhs) 
{
    if( this == &rhs )
        return(*this);

    PartialCylinder::operator= (rhs);
	return(*this);
}


PartialCone* 
PartialCone::Clone(void) const 
{
    return (new PartialCone(*this));
}


bool 
PartialCone::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
	Vector3D	down(0, -1, 0);
	Vector3D	temp = ray.o - Point3D(0, m_y1, 0);
	double		e = ray.d * down;
	double		f = temp * down;
	double		theta = atan2(m_radius, m_y1 - m_y0 );
	double		cosTheta = cos(theta);
	double		cosThetaSq = cosTheta * cosTheta;

	double		a = e * e - cosThetaSq;
	double		b = 2 * (e * f - ray.d * temp * cosThetaSq);
	double		c = f * f - temp * temp * cosThetaSq;
    double		disc = b * b - 4.0 * a * c;
    double		tval, tval1, tval2;

    if( disc >= 0 )
	{
        tval1 = (-b - sqrt(disc)) / (2.0 * a);
		tval2 = (-b + sqrt(disc)) / (2.0 * a);
		tval  = (tval1 > tval2 ? tval2 : tval1);
		bool finish = false;

loop:
        if( tval > kEpsilon ) 
		{
			Point3D hit = ray.o + ray.d * tval;

            if( hit.y >= m_y0 && hit.y <= m_y1 ) 
			{
				double phi = atan2(hit.x, hit.z);

				if( phi < 0.0 )
					phi += TWO_PI;
                
				if( phi >= m_phi1 && phi <= m_phi2 )
				{
					tmin = tval;
					sr.normal.Set(sin(phi) * cosTheta, sin(theta), cos(phi) * cosTheta);
					if( -ray.d * sr.normal < 0.0 ) 
						sr.normal = -sr.normal;

					sr.localHitPoint = hit;
					return (true);
				}
            }
        }

		if( !finish && disc != 0 )
		{
			finish = true;
			tval  = (tval1 > tval2 ? tval1 : tval2);
			goto loop;
		}
    }

    return (false);
}


bool 
PartialCone::ShadowHit(const Ray& ray, double& tmin) const 
{
    if( !m_shadowing )
		return (false);

	Vector3D	down(0, -1, 0);
	Vector3D	temp = ray.o - Point3D(0, m_y1, 0);
	double		e = ray.d * down;
	double		f = temp * down;
	double		theta = atan2(m_radius, m_y1 - m_y0 );
	double		cosTheta = cos(theta);
	double		cosThetaSq = cosTheta * cosTheta;

	double		a = e * e - cosThetaSq;
	double		b = 2 * (e * f - ray.d * temp * cosThetaSq);
	double		c = f * f - temp * temp * cosThetaSq;
    double		disc = b * b - 4.0 * a * c;
    double		tval, tval1, tval2;

    if( disc >= 0 )
	{
        tval1 = (-b - sqrt(disc)) / (2.0 * a);
		tval2 = (-b + sqrt(disc)) / (2.0 * a);
		tval  = (tval1 > tval2 ? tval2 :tval1);
		bool finish = false;

loop:
        if( tval > kEpsilon && tval < -kEpsilon ) 
		{
			Point3D hit = ray.o + ray.d * tval;

            if( hit.y >= m_y0 && hit.y <= m_y1 ) 
			{
				double phi = atan2(hit.x, hit.z);

				if( phi < 0.0 )
					phi += TWO_PI;
                
				if( phi >= m_phi1 && phi <= m_phi2 )
				{
					tmin = tval;
					return (true);
				}
            }
        }

		if( !finish && disc != 0 )
		{
			finish = true;
			tval  = (tval1 > tval2 ? tval1 :tval2);
			goto loop;
		}
    }

    return (false);
}