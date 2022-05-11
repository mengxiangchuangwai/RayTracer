//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/OpenCone.h"
#include <cmath>

OpenCone::OpenCone(Material* mp)
    : OpenCylinder(mp)
{}


OpenCone::OpenCone(const double y0, const double y1, const double radius, Material* mp)
    : OpenCylinder(y0, y1, radius, mp)
{}


OpenCone::OpenCone(const OpenCone& other)
	: OpenCylinder(other)
{}


OpenCone& 
OpenCone::operator= (const OpenCone& rhs) 
{
    if( this == &rhs )
        return(*this);
   
    OpenCylinder::operator= (rhs);
    return(*this);
}


OpenCone* 
OpenCone::Clone(void) const 
{
    return (new OpenCone(*this));
}


bool 
OpenCone::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
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

		if( tval < kEpsilon )
			tval  = (tval1 > tval2 ? tval1 : tval2);

        if( tval > kEpsilon ) 
		{
			Point3D hit = ray.o + ray.d * tval;
			double phi;

            if( hit.y >= m_y0 && hit.y <= m_y1 ) 
			{
                tmin = tval;
				phi = atan2(hit.x, hit.z);

				if( phi < 0.0 )
					phi += TWO_PI;
                
				sr.normal.Set(sin(phi) * cosTheta, sin(theta), cos(phi) * cosTheta);

				if( -ray.d * sr.normal < 0.0 ) 
					sr.normal = -sr.normal;
                
				sr.localHitPoint = hit;
                return (true);
            }
        }
    }

    return (false);
}


bool OpenCone::ShadowHit(const Ray& ray, double& tmin) const 
{
    if( !m_shadowing )
		return (false);

    Vector3D	down(0, -1, 0);
	Vector3D	temp = ray.o - Vector3D(0, m_y1, 0);
	double		e = ray.d * down;
	double		f = temp * down;
	double		cosTheta = cos(atan2(m_radius,  m_y1 - m_y0));
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

		if( tval < kEpsilon ) 
			tval  = (tval1 > tval2 ? tval1 :tval2);

        if( tval > kEpsilon ) 
		{
			Point3D hit = ray.o + ray.d * tval;

            if( hit.y >= m_y0 && hit.y <= m_y1 ) 
			{
                tmin = tval;
                return (true);
            }
        }
    }

    return (false);
}