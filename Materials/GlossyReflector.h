//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __GLOSSY_REFLECTOR__
#define __GLOSSY_REFLECTOR__


#include "../Materials/Phong.h"

class GlossyReflector: public Phong {	
	public:
	
		GlossyReflector(void);

		GlossyReflector(const GlossyReflector& other);

		virtual GlossyReflector*
		Clone(void) const;

		GlossyReflector&
		operator= (const GlossyReflector& rhs);

		virtual
		~GlossyReflector(void);
	
		virtual void
		SetSampler(Sampler* sp);

		virtual void
		SetupSampler(const int numSamples, const float exp = 1.0f, const SamplerType samplerType = ST_MultiJittered);
	
		void
		SetKr(const float k);

		float
		GetKr(void) const;
	
		void													
		SetCr(const RGBColor& c);
		
		void
		SetCr(const float r, const float g, const float b);
		
		void
		SetCr(const float c);

		const RGBColor&
		GetCr(void) const;

		void													
		SetExponent(const float exp);

		float
		GetExponent(void) const;

		virtual RGBColor
		Shade(ShadeContext& sr);
	
		virtual RGBColor
		AreaLightShade(ShadeContext& sr);

		virtual RGBColor
		PathShade(ShadeContext& sr);

	
	private:
	
		RGBColor 
		Trace(ShadeContext& sr);

		GlossySpecular m_reflector;
};



inline void
GlossyReflector::SetSampler(Sampler* sp) 
{
	if( sp )
	{
		Phong::SetSampler(sp);
		m_reflector.SetSampler(sp->Clone());
	}
}


inline void
GlossyReflector::SetupSampler(const int numSamples, const float exp, const SamplerType samplerType) 
{
	Phong::SetupSampler(numSamples, exp, samplerType);
	m_reflector.SetupSampler(numSamples, exp, samplerType);	
}


inline void
GlossyReflector::SetKr(const float k) 
{
	m_reflector.SetCoeff(k);
}


inline float
GlossyReflector::GetKr(void) const
{
	return (m_reflector.GetCoeff());
}


inline void
GlossyReflector::SetCr(const RGBColor& c) 
{
	m_reflector.SetColor(c);
}


inline void
GlossyReflector::SetCr(const float r, const float g, const float b) 
{
	m_reflector.SetColor(r, g, b);
}


inline void
GlossyReflector::SetCr(const float c) 
{
	m_reflector.SetColor(c);
}


inline const RGBColor&
GlossyReflector::GetCr(void) const 
{
	return (m_reflector.GetColor());
}


inline void
GlossyReflector::SetExponent(const float exp) 
{
	m_reflector.SetExponent(exp);
}


inline float
GlossyReflector::GetExponent(void) const 
{
	return (m_reflector.GetExponent());
}


inline RGBColor 
GlossyReflector::Trace(ShadeContext& sr) 
{
	Vector3D 	wo(-sr.ray.d);
	Vector3D 	wi;
	float		pdf;	
	RGBColor 	fr(m_reflector.Sample(sr, wo, wi, pdf)); 
	Ray 		reflectedRay(sr.hitPoint, wi);
	return (fr * sr.pWorld->GetTracer()->TraceRay(reflectedRay, sr.depth + 1) * (sr.normal * wi) / pdf);
}


inline RGBColor
GlossyReflector::Shade(ShadeContext& sr) 
{
	return (Phong::Shade(sr) + Trace(sr));
}


inline RGBColor
GlossyReflector::AreaLightShade(ShadeContext& sr) 
{
	return (Phong::AreaLightShade(sr) + Trace(sr));
}


inline RGBColor
GlossyReflector::PathShade(ShadeContext& sr) 
{
	RGBColor result(0.0);

	if( 0 == sr.depth )
		result = Phong::AreaLightShade(sr);
	
	result += Trace(sr);
	return (result);
}


#endif // __GLOSSY_REFLECTOR__