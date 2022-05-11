//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <cmath>
#include "../Objects/PartialTorus.h"

PartialTorus::PartialTorus(Material* mp)
    : Torus(mp)
	, m_phi1(0.0)
	, m_phi2(TWO_PI)
	, m_theta1(0.0)
	, m_theta2(TWO_PI)
{}


PartialTorus::PartialTorus(const double	a,
						   const double	b,
						   const double azimuthMin,		// in degrees
						   const double azimuthMax,		// in degrees
						   const double polarMin,		// in degrees measured counter clockwise from the (x, z) plane
						   const double polarMax,		// in degrees measured counter clockwise from the (x, z) plane
						   Material* mp)
	: Torus(a, b, mp)
	, m_phi1(azimuthMin * PI_ON_180)
	, m_phi2(azimuthMax * PI_ON_180)
	, m_theta1(polarMin * PI_ON_180)
	, m_theta2(polarMax * PI_ON_180)
{}


PartialTorus*
PartialTorus::Clone(void) const 
{
	return (new PartialTorus(*this));
}


PartialTorus::PartialTorus(const PartialTorus& other)
	: Torus(other)
	, m_phi1(other.m_phi1)
	, m_phi2(other.m_phi2)
	, m_theta1(other.m_theta1)
	, m_theta2(other.m_theta2)
{}


PartialTorus&
PartialTorus::operator = (const PartialTorus& rhs) 
{
	if( this == &rhs )
		return (*this);

	Torus::operator= (rhs);

	m_phi1		= rhs.m_phi1;
	m_phi2		= rhs.m_phi2;
	m_theta1	= rhs.m_theta1;
	m_theta2	= rhs.m_theta2;

	return (*this);
}


PartialTorus::~PartialTorus(void) 
{}


bool
PartialTorus::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{	
	if( Intersect(ray, tmin) ) 
	{
		sr.localHitPoint 	= ray.o + tmin * ray.d;

		const Point3D& hit = sr.localHitPoint;
		double phi = atan2(hit.x, hit.z);
		if (phi < 0.0)
			phi += TWO_PI;

		if( phi >= m_phi1 && phi <= m_phi2 ) 
		{
			double theta = atan2(hit.y, sqrt(hit.x * hit.x + hit.z * hit.z));
			if( theta < 0.0 )
				theta += TWO_PI;

			if( theta >= m_theta1 && theta <= m_theta2 ) 
			{
				sr.normal = ComputeNormal(sr.localHitPoint);

				if( -ray.d * sr.normal < 0.0 )
                    sr.normal = -sr.normal;

				return (true);
			}
		}
	}

	return (false);
}


bool 
PartialTorus::ShadowHit(const Ray& ray, double& tmin) const 
{    
	if( !m_shadowing )
		return (false);

	if( Intersect(ray, tmin) ) 
	{
		Point3D hit(ray.o + tmin * ray.d);
		double phi = atan2(hit.x, hit.z);
		if( phi < 0.0 )
			phi += TWO_PI;

		if( phi >= m_phi1 && phi <= m_phi2 ) 
		{
			double theta = atan2(hit.y, sqrt(hit.x * hit.x + hit.z * hit.z));
			if( theta < 0.0 )
				theta += TWO_PI;

			if( theta >= m_theta1 && theta <= m_theta2 )
				return (true);
		}
	}

	return (false);
}