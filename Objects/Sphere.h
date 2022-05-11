//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __SPHERE__
#define __SPHERE__


#include "../Objects/GeometricObject.h"

class Sphere: public GeometricObject {

	public:

		Sphere(Material* mp = NULL);   								

		Sphere(const Point3D& cener, const double radius, Material* mp = NULL);

		Sphere(const Sphere& other); 

		virtual Sphere* 
		Clone(void) const;

		virtual
		~Sphere(void);

		Sphere&
		operator=(const Sphere& rhs);

		virtual void
		SetCenter(const Point3D& val);

		virtual void
		SetCenter(const double x, const double y, const double z);

		const Point3D&
		GetCenter(void) const;

		virtual void
		SetRadius(const double val);

		double
		GetRadius(void) const;

		virtual void
		UpdateBoundingBox(void);

		virtual bool
		Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

		virtual bool
		ShadowHit(const Ray &ray, double &tmin) const;


	protected:

		bool 
		Intersect(const Ray& ray, double& tval) const;

		Point3D 	m_center;   			// center coordinates as a point
		double 		m_radius;				// the radius
};



inline void
Sphere::SetCenter(const Point3D& val) 
{
	m_center = val;
}


inline void
Sphere::SetCenter(const double x, const double y, const double z) 
{
	m_center.x = x;
	m_center.y = y;
	m_center.z = z;
}


inline const Point3D&
Sphere::GetCenter(void) const
{
	return (m_center);
}


inline void
Sphere::SetRadius(const double val) 
{
	m_radius = val;
}


inline double 
Sphere::GetRadius(void) const
{
	return (m_radius);
}


inline bool
Sphere::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
	if( Intersect(ray, tmin) )
	{
		sr.localHitPoint = ray.o + tmin * ray.d;
		sr.normal = (sr.localHitPoint - m_center) / m_radius;

//		if( -ray.d * sr.normal < 0.0 )
		if( m_reverseNormal )
			sr.normal = -sr.normal;
		
		return (true);
	}

	return (false);
}


inline bool
Sphere::ShadowHit(const Ray& ray, double& tmin) const 
{
	if( !m_shadowing )
		return (false);

   return (Intersect(ray, tmin));
}


#endif