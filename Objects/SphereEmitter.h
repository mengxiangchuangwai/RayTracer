//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __SPHERE_EMITTER__
#define __SPHERE_EMITTER__


#include "../Samplers/Sampler.h"
#include "../Objects/Sphere.h"

class SphereEmitter: public Sphere {

	public:

		SphereEmitter(Material* mp = NULL); 

		SphereEmitter(const Point3D& center, const double radius, Material* mp = NULL);

		SphereEmitter(const SphereEmitter& other);

		virtual SphereEmitter* 
		Clone(void) const;

		virtual
		~SphereEmitter(void);

		SphereEmitter&
		operator= (const SphereEmitter& rhs);

		virtual void
		SetSampler(Sampler* pSampler);

		virtual Point3D
		Sample(void);

		virtual Normal
		GetNormal(const Point3D& p) const;

		virtual float
		Pdf(const ShadeContext& sr, const Vector3D& wi);

		virtual void
		SetRadius(const double val);


	protected:

		double		m_invArea;
		Sampler*	m_pSampler;					// for sphere lights
};



inline Point3D
SphereEmitter::Sample(void) 
{
	Point3D sp = m_pSampler->SampleSphere();
	return (m_center + sp * m_radius);
}


inline Normal 
SphereEmitter::GetNormal(const Point3D& p) const 
{
   return (p - m_center) / m_radius;
}


inline float
SphereEmitter::Pdf(const ShadeContext& sr, const Vector3D& wi) 
{
	return (float)(m_invArea);
}


inline void
SphereEmitter::SetRadius(const double val) 
{
	m_radius	= val;
	m_invArea	= 1.0 / (4 * PI * m_radius * m_radius);
}


#endif