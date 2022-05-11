//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __BRDF__
#define __BRDF__


#include "../Samplers/Sampler.h"
#include "../Textures/Texture.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/ShadeContext.h"

class BRDF {
	public:

		BRDF(void);

		BRDF(const BRDF& other);

		virtual BRDF*
		Clone(void) const = 0;

		BRDF&
		operator= (const BRDF& rhs);

		virtual
		~BRDF(void);

		virtual void
		SetSampler(Sampler* sampler, const float exp = 1.0f);

		virtual void
		SetupSampler(const int numSamples, const float exp = 1.0f, const SamplerType type = ST_MultiJittered);

		virtual RGBColor
		F(const ShadeContext& sr, const Vector3D& wo, const Vector3D& wi) const;

		virtual RGBColor
		F(const Texture* tp, const ShadeContext& sr, const Vector3D& wo, const Vector3D& wi) const;

		virtual RGBColor
		Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wi) const;

		virtual RGBColor
		Sample(const Texture* tp, const ShadeContext& sr, const Vector3D& wo, Vector3D& wi) const;

		virtual RGBColor
        Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

		virtual RGBColor
		Sample(const Texture* tp, const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

		virtual RGBColor
		Rho(const ShadeContext& sr, const Vector3D& wo) const;

		virtual RGBColor
		Rho(const Texture* tp, const ShadeContext& sr, const Vector3D& wo) const;

		virtual void
		SetColor(const RGBColor& c);

		virtual void													
		SetColor(const float r, const float g, const float b);
		
		virtual void													
		SetColor(const float c);

		virtual const RGBColor&
		GetColor(void) const;

		virtual void
		SetCoeff(const float coeff);

		virtual float
		GetCoeff(void) const;


	protected:
		
		RGBColor	m_color;
		float		m_coeff;
		Sampler*	m_sampler;		// for indirect illumination
};



inline void
BRDF::SetColor(const RGBColor& c) 
{
	m_color = c;
}


inline void
BRDF::SetColor(const float r, const float g, const float b) 
{
	m_color.Set(r, g, b);
}
		

inline void													
BRDF::SetColor(const float c) 
{
	m_color.Set(c, c, c);
}


inline const RGBColor&
BRDF::GetColor(void) const {
	return (m_color);
}


inline void
BRDF::SetCoeff(const float coeff) 
{
	m_coeff = coeff;
}


inline float
BRDF::GetCoeff(void) const 
{
	return m_coeff;
}


#endif
