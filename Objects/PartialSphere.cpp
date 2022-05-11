//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <cmath>
#include "../Utilities/Constants.h"
#include "../Objects/PartialSphere.h"

PartialSphere::PartialSphere(Material* mp)
	: GeometricObject(mp)
	, m_center(0.0)
	, m_radius(1.0)
	, m_phi1(0.0)			// in radians
	, m_phi2(TWO_PI)		// in radians
	, m_theta1(0.0)			// in radians measured from top
	, m_theta2(PI)			// in radians measured from top
	, m_cosTheta1(1.0)
	, m_cosTheta2(-1.0)
{}


PartialSphere::PartialSphere(const Point3D 	center,
							 const double 	radius,
							 const double 	azimuthMin,		// in degrees
							 const double 	azimuthMax,		// in degrees
							 const double 	polarMin,		// in degrees measured from top
							 const double 	polarMax,		// in degrees measured from top
							 Material* mp)
	: GeometricObject(mp)
	, m_center(center)
	, m_radius(radius)
	, m_phi1(azimuthMin * PI_ON_180)			// in radians
	, m_phi2(azimuthMax * PI_ON_180)			// in radians
	, m_theta1(polarMin * PI_ON_180)			// in radians measured from top
	, m_theta2(polarMax * PI_ON_180)			// in radians measured from top
	, m_cosTheta1(::cos(m_theta1))
	, m_cosTheta2(::cos(m_theta2))
{}


PartialSphere::PartialSphere(const Point3D 	center, const double 	radius, Material* mp)
	: GeometricObject(mp)
	, m_center(center)
	, m_radius(radius)
	, m_phi1(0.0)
	, m_phi2(TWO_PI)
	, m_theta1(0.0)
	, m_theta2(PI)
	, m_cosTheta1(1.0)
	, m_cosTheta2(-1.0)
{}


PartialSphere*
PartialSphere::Clone(void) const 
{
	return (new PartialSphere(*this));
}


PartialSphere::PartialSphere(const PartialSphere& other)
	: 	GeometricObject(other)
	,	m_center(other.m_center)
	,	m_radius(other.m_radius)
	,	m_phi1(other.m_phi1)
	,	m_phi2(other.m_phi2)
	,	m_theta1(other.m_theta1)
	,	m_theta2(other.m_theta2)
	,	m_cosTheta1(other.m_cosTheta1)
	,	m_cosTheta2(other.m_cosTheta2)
{}


PartialSphere&
PartialSphere::operator=(const PartialSphere& rhs)
{
	if( this == &rhs )
		return (*this);

	GeometricObject::operator= (rhs);

	m_center 	= rhs.m_center;
	m_radius	= rhs.m_radius;
	m_phi1		= rhs.m_phi1;
	m_phi2		= rhs.m_phi2;
	m_theta1	= rhs.m_theta1;
	m_theta2	= rhs.m_theta2;
	m_cosTheta1	= rhs.m_cosTheta1;
	m_cosTheta2	= rhs.m_cosTheta2;

	return (*this);
}


PartialSphere::~PartialSphere(void) 
{}


void 
PartialSphere::UpdateBoundingBox(void)
{
    m_bbox.p0 = Point3D(m_center.x-m_radius, m_center.y-m_radius, m_center.z-m_radius);
    m_bbox.p1 = Point3D(m_center.x+m_radius, m_center.y+m_radius, m_center.z+m_radius);
}


bool
PartialSphere::Intersect(const Ray& ray, double& tval, ShadeContext* pContext) const 
{
	Vector3D	temp 	= ray.o - m_center;
	double 		a 		= ray.d * ray.d;
	double 		b 		= 2.0 * temp * ray.d;
	double 		c 		= temp * temp - m_radius * m_radius;
	double 		disc 	= b * b - 4.0 * a * c;

	if( disc < 0.0 )
		return (false);
	else 
	{
		double e = sqrt(disc);
		double denom = 2.0 * a;
		double t = (-b - e) / denom;    // smaller root
		bool finish = false;

loop:
		if( t > kEpsilon ) 
		{
			Vector3D hit = ray.o + t * ray.d - m_center;

			double phi = atan2(hit.x, hit.z);
			if( phi < 0.0 )
				phi += TWO_PI;

			if( hit.y <= m_radius * m_cosTheta1 && 
				hit.y >= m_radius * m_cosTheta2 && 
				phi >= m_phi1 && phi <= m_phi2 ) 
			{
				tval = t;

				if( pContext ) 
				{
					pContext->normal = (temp + tval * ray.d) / m_radius;   // points outwards
					pContext->localHitPoint = ray.o + tval * ray.d;

					 if( -ray.d * pContext->normal < 0.0 ) 
						 pContext->normal = -pContext->normal;
				}

				return (true);
			}
		}

		if( !finish && disc != 0 )
		{
			finish = true;
			t = (-b + e) / denom;    // larger root
			goto loop;
		}
	}

	return (false);
}