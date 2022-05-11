//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __AMBIENT_OCCLUDER__
#define __AMBIENT_OCCLUDER__


#include "../Lights/Light.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeContext.h"
#include "../Samplers/Sampler.h"

class AmbientOccluder: public Light {
	public:

		AmbientOccluder(void);

		AmbientOccluder(const AmbientOccluder& other);

		AmbientOccluder&
		operator= (const AmbientOccluder& rhs);

		virtual AmbientOccluder*
		Clone(void) const;

		virtual
		~AmbientOccluder(void);

		void
		SetSampler(Sampler* sp);

		virtual Vector3D
		GetDirection(ShadeContext& sr);

		virtual bool
		InShadow(const Ray& ray, const ShadeContext& sr) const;

		virtual RGBColor
		L(ShadeContext& sr);

		virtual void 
		BeginSection(void);

		virtual void
		EndSection(void);

		void
	    SetRadianceScaler(const float s);

		float
		GetRadianceScaler(void) const;

		void
		SetColor(const float c);

		void
		SetColor(const RGBColor& c);

		void
		SetColor(const float r, const float g, const float b);

		const RGBColor&
		GetColor(void) const;

	    void
	    SetMinAmount(const float m);

		float
		GetMinAmount(void) const;


	private:

		float		m_ls;
		RGBColor	m_color;
		float 		m_minAmount;
		Vector3D 	m_u, m_v, m_w;
		Sampler*	m_pSampler;
};



inline void
AmbientOccluder::SetSampler(Sampler* sp) 
{
	SAFE_DELETE(m_pSampler);

	if( m_pSampler = sp )
        m_pSampler->SamplesToHemisphere(1);
}


inline Vector3D
AmbientOccluder::GetDirection(ShadeContext& sr) 
{
	Point3D sp = m_pSampler->SampleHemisphere();
	return (sp.x * m_u + sp.y * m_v + sp.z * m_w);
}


inline void
AmbientOccluder::SetRadianceScaler(const float s) 
{
    m_ls = s;
}


inline float
AmbientOccluder::GetRadianceScaler(void) const
{
	return (m_ls);
}


inline void
AmbientOccluder::SetColor(const float c) 
{
	m_color.r = c; m_color.g = c; m_color.b = c;
}


inline void
AmbientOccluder::SetColor(const RGBColor& c) 
{
	m_color = c;
}


inline void
AmbientOccluder::SetColor(const float r, const float g, const float b) 
{
	m_color.r = r; m_color.g = g; m_color.b = b;
}


inline const RGBColor&
AmbientOccluder::GetColor(void) const
{
	return (m_color);
}


inline void
AmbientOccluder::SetMinAmount(const float m) 
{
    m_minAmount = m;
}


inline float
AmbientOccluder::GetMinAmount(void) const
{
	return (m_minAmount);
}


inline void 
AmbientOccluder::BeginSection(void)
{
	m_cs.lock();
}


inline void
AmbientOccluder::EndSection(void)
{
	m_cs.unlock();
}


#endif