//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __PERFECT_REFLECTOR__
#define __PERFECT_REFLECTOR__


#include "../Materials/Phong.h"
#include "../BRDFs/PerfectSpecular.h"

class PerfectReflector: public Phong {	
	public:
	
		PerfectReflector(void);										

		PerfectReflector(const PerfectReflector& other);						

		PerfectReflector& 
		operator= (const PerfectReflector& rhs);						

		virtual PerfectReflector*										
		Clone(void) const;				

		virtual
		~PerfectReflector(void);
		
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
		
		virtual RGBColor										
		Shade(ShadeContext& s);

		virtual RGBColor
		AreaLightShade(ShadeContext& sr);

		virtual RGBColor
		PathShade(ShadeContext& sr);

		
	private:
	
		RGBColor 
		Trace(ShadeContext& sr);

		PerfectSpecular m_reflector;		
};



inline void
PerfectReflector::SetKr(const float k) 
{
	m_reflector.SetCoeff(k);
}


inline float
PerfectReflector::GetKr(void) const
{
	return (m_reflector.GetCoeff());
}


inline void
PerfectReflector::SetCr(const RGBColor& c) 
{
	m_reflector.SetColor(c);
	
}


inline void
PerfectReflector::SetCr(const float r, const float g, const float b) 
{
	m_reflector.SetColor(r, g, b);
}


inline void
PerfectReflector::SetCr(const float c) 
{
	m_reflector.SetColor(c);
}


inline const RGBColor&
PerfectReflector::GetCr(void) const 
{
	return (m_reflector.GetColor());
}


inline RGBColor 
PerfectReflector::Trace(ShadeContext& sr) 
{
	Vector3D wo = -sr.ray.d;
	Vector3D wi;	
	RGBColor fr = m_reflector.Sample(sr, wo, wi); 
	Ray reflectedRay(sr.hitPoint, wi); 
	return (fr * sr.pWorld->GetTracer()->TraceRay(reflectedRay, sr.depth + 1) * (sr.normal * wi));
}


inline RGBColor
PerfectReflector::Shade(ShadeContext& sr) 
{
	return (Phong::Shade(sr) + Trace(sr));
}


inline RGBColor
PerfectReflector::AreaLightShade(ShadeContext& sr) 
{
	return (Phong::AreaLightShade(sr) + Trace(sr));
}


inline RGBColor
PerfectReflector::PathShade(ShadeContext& sr) 
{		
	RGBColor result(0.0);

	if( 0 == sr.depth )
		result = Phong::AreaLightShade(sr);

	Vector3D 	wo = -sr.ray.d;
	Vector3D 	wi;	
	float 		pdf;
	RGBColor 	fr = m_reflector.Sample(sr, wo, wi, pdf); 
	Ray 		reflectedRay(sr.hitPoint, wi);
	result += fr * sr.pWorld->GetTracer()->TraceRay(reflectedRay, sr.depth + 1) * (sr.normal * wi) / pdf;

	return (result);
}


#endif
