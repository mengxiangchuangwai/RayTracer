//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __ENVIRONMENT_LIGHT__
#define __ENVIRONMENT_LIGHT__


#include "../Lights/Light.h"
#include "../Samplers/Sampler.h"
#include "../Materials/Material.h"

class EnvironmentLight: public Light {
	public:

		EnvironmentLight(void);

		EnvironmentLight(const EnvironmentLight& other);

		EnvironmentLight&
		operator= (const EnvironmentLight& rhs);

		virtual EnvironmentLight*
		Clone(void) const;

		virtual
		~EnvironmentLight(void);

		void
		SetSampler(Sampler* sp);

		void
		SetMaterial(Material* mp);

		virtual Vector3D
		GetDirection(ShadeContext& sr);

		virtual RGBColor
		L(ShadeContext& sr);

		virtual bool
		InShadow(const Ray& ray, const ShadeContext& sr) const;

		virtual float
		Pdf(const ShadeContext& sr) const;

		virtual void 
		BeginSection(void);
		
		virtual void
		EndSection(void);


	private:

		Sampler*	m_pSampler;
		Material* 	m_pMaterial;
		Vector3D	m_u, m_v, m_w;
		Vector3D	m_wi;
};



inline void
EnvironmentLight::SetSampler(Sampler* sp) 
{
	SAFE_DELETE(m_pSampler);

	if( m_pSampler = sp )
        m_pSampler->SamplesToHemisphere(1);
}


inline void
EnvironmentLight::SetMaterial(Material* mp) 
{
	SAFE_DELETE(m_pMaterial);
	m_pMaterial = mp;
}


inline Vector3D
EnvironmentLight::GetDirection(ShadeContext& sr) 
{
	m_w = sr.normal;
	m_v = Vector3D(0.0034, 1, 0.0071) ^ m_w;
	m_v.Normalize();
	m_u = m_v ^ m_w;
	Point3D sp = m_pSampler->SampleHemisphere();
	m_wi = sp.x * m_u + sp.y * m_v + sp.z * m_w;
	return (m_wi);
}


inline RGBColor
EnvironmentLight::L(ShadeContext& sr) 
{
	return (m_pMaterial->GetLe(sr));
}


// The following function is not in the book.
// It uses Equation 18.6

inline float
EnvironmentLight::Pdf(const ShadeContext& sr) const 
{
	return (sr.normal * m_wi * invPI);
}


inline void 
EnvironmentLight::BeginSection(void)
{
	m_cs.lock();
}


inline void
EnvironmentLight::EndSection(void)
{
	m_cs.unlock();
}


#endif