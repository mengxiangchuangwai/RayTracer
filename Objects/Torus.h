//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __TORUS__
#define __TORUS__


#include "../Objects/GeometricObject.h"

class Torus: public GeometricObject {
	public:

		Torus(Material* mp = NULL);

		Torus(const double outerRadius, const double innerRadius, Material* mp = NULL);

		virtual Torus*
		Clone(void) const;

		Torus(const Torus& other);

		virtual 
		~Torus(void);

		Torus&
		operator= (const Torus& rhs);

		Normal
		ComputeNormal(const Point3D& p) const;

		virtual void
		UpdateBoundingBox(void);

		virtual bool
		Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

		virtual bool 
		ShadowHit(const Ray& ray, double& tmin) const;

		void 
		SetOuterRadius(const double r);

		double 
		GetOuterRadius(void) const;

		void
		SetInnerRadius(const double r);

		double
		GetInnerRadius(void) const;


	protected:

		bool 
		Intersect(const Ray& ray, double& tmin) const;

		double 	m_or;	 // swept radius
		double	m_ir;	 // tube radius
};



inline bool
Torus::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
	if( Intersect(ray, tmin) )
	{
		sr.localHitPoint = ray.o + tmin * ray.d;
		sr.normal = ComputeNormal(sr.localHitPoint);

	//	if( -ray.d * sr.normal < 0.0 ) 
		if( m_reverseNormal )
			sr.normal = -sr.normal;

		return (true);
	}

	return (false);
}


inline bool 
Torus::ShadowHit(const Ray& ray, double& tmin) const 
{    
	if( !m_shadowing )
		return (false);

	return (Intersect(ray, tmin));
}


inline void 
Torus::SetOuterRadius(const double r)
{
	m_or = r;
}


inline double 
Torus::GetOuterRadius(void) const
{
	return (m_or);
}


inline void
Torus::SetInnerRadius(const double r)
{
	m_ir = r;
}


inline double
Torus::GetInnerRadius(void) const
{
	return (m_ir);
}


inline void
Torus::UpdateBoundingBox(void)
{
	m_bbox = BBox(-m_or - m_ir, m_or + m_ir, -m_ir, m_ir, -m_or - m_ir, m_or + m_ir);
}


#endif