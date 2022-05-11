//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __GLOSSY_SPECULAR__
#define __GLOSSY_SPECULAR__


#include "../BRDFs/BRDF.h"

class GlossySpecular: public BRDF {
	public:

		GlossySpecular(void);

		GlossySpecular(const GlossySpecular& other);

		virtual ~GlossySpecular(void);

		virtual GlossySpecular*
		Clone(void) const;

		GlossySpecular&
		operator= (const GlossySpecular& rhs);

		virtual void
		SetupSampler(const int numSamples, const float exp = 1.0f, const SamplerType type = ST_MultiJittered);

		virtual RGBColor
		F(const ShadeContext& sr, const Vector3D& wo, const Vector3D& wi) const;

		virtual RGBColor
		F(const Texture *tp, const ShadeContext& sr, const Vector3D& wo, const Vector3D& wi) const;

		virtual RGBColor
		Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

		virtual RGBColor
		Sample(const Texture *tp, const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

		void
		SetExponent(const float val);

		float
		GetExponent(void) const;


	private:

		RGBColor
		S(const RGBColor& clr, const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
		
		float	m_exp; 	// specular exponent
};



inline void
GlossySpecular::SetupSampler(const int numSamples, const float exp, const SamplerType type) 
{
	BRDF::SetupSampler(numSamples, exp, type);
	m_exp = exp;
}


inline void
GlossySpecular::SetExponent(const float val) 
{
	m_exp = val;
}


inline float
GlossySpecular::GetExponent(void) const
{
	return (m_exp);
}


// no sampling here: just use the Phong formula
// this is used for direct illumination only
inline RGBColor
GlossySpecular::F(const ShadeContext &sr, const Vector3D &wo, const Vector3D &wi) const 
{
	RGBColor 	L;
	double 		ndotwi = sr.normal * wi;
	Vector3D 	r(-wi + 2.0 * sr.normal * ndotwi); // mirror reflection direction
	double 		rdotwo = r * wo;

	if( rdotwo > 0.0 )
		L = m_coeff * m_color * pow(rdotwo, (double)m_exp);

	return (L);
}


inline RGBColor
GlossySpecular::F(const Texture *tp, 
				  const ShadeContext &sr, const Vector3D &wo, const Vector3D &wi) const 
{
	RGBColor 	L;
	double 		ndotwi = sr.normal * wi;
	Vector3D 	r(-wi + 2.0 * sr.normal * ndotwi); // mirror reflection direction
	double 		rdotwo = r * wo;

	if( rdotwo > 0.0 )
		L = m_coeff * tp->GetColor(sr) * pow(rdotwo, (double)m_exp);

	return (L);
}


// this is used for indirect illumination
inline RGBColor
GlossySpecular::Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const 
{
	return (S(m_color, sr, wo, wi, pdf));
}


inline RGBColor
GlossySpecular::Sample(const Texture *tp, 
						 const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const 
{
	return (S(tp->GetColor(sr), sr, wo, wi, pdf));
}


#endif
