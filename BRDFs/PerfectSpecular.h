//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __PERFECT_SPECULAR__
#define __PERFECT_SPECULAR__


// this implements perfect specular reflection for indirect illumination
// with reflective materials 

#include "../BRDFs/BRDF.h"
#include "../Utilities/Normal.h"

class PerfectSpecular: public BRDF 
{
	public:
	
		PerfectSpecular(void);
		
		PerfectSpecular(const PerfectSpecular& other);

		virtual 
		~PerfectSpecular(void);

		virtual PerfectSpecular*
		Clone(void) const;

		PerfectSpecular&
		operator= (const PerfectSpecular& rhs);
		
		virtual RGBColor
		Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wi) const;

		virtual RGBColor
		Sample(const Texture *tp, const ShadeContext& sr, const Vector3D& wo, Vector3D& wi) const;
		
		virtual RGBColor
		Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

		virtual RGBColor
		Sample(const Texture *tp, const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
};



// this computes wi: the direction of perfect mirror reflection
// it's called from the functions PerfectReflector::shade and Transparent::shade.
// the fabs in the last statement is for transparency

inline RGBColor
PerfectSpecular::Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wi) const 
{
	double ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo; 
	return (m_coeff * m_color / (sr.normal * wi));
}


inline RGBColor
PerfectSpecular::Sample(const Texture *tp, 
						  const ShadeContext& sr, const Vector3D& wo, Vector3D& wi) const 
{
	double ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo; 
	return (m_coeff * tp->GetColor(sr) / (sr.normal * wi));
}


// this version of sample_f is used with path tracing
// it returns ndotwi in the pdf

inline RGBColor
PerfectSpecular::Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const 
{
	double ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo; 
	pdf = sr.normal * wi;
	return (m_coeff * m_color);  
}


inline RGBColor
PerfectSpecular::Sample(const Texture *tp, 
						  const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const 
{
	double ndotwo = sr.normal * wo;
	wi = -wo + 2.0 * sr.normal * ndotwo;
	pdf = sr.normal * wi;
	return (m_coeff * tp->GetColor(sr));  
}


#endif

