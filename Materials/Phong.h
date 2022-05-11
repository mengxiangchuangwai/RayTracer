//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __PHONG__
#define __PHONG__


#include "../Materials/Material.h"
#include "../BRDFs/Lambertian.h"
#include "../BRDFs/GlossySpecular.h"

class Phong: public Material {
	public:

		Phong(void);

		Phong(const Phong& other);

		virtual Phong *
		Clone(void) const;

		Phong&
		operator= (const Phong& rhs);

		virtual 
		~Phong(void);

		virtual void
		SetSampler(Sampler* sp);

		virtual void
		SetupSampler(const int numSamples, const float exp = 1.0f, const SamplerType samplerType = ST_MultiJittered);

		void
		SetKa(const float k);

		float
		GetKa(void) const;

		void
		SetKd(const float k);

		float
		GetKd(void) const;

		void
		SetCd(const RGBColor& c);

		void
		SetCd(const float r, const float g, const float b);

		void
		SetCd(const float c);

		const RGBColor&
		GetCd(void) const;

		void
		SetKs(const float ks);

		float
		GetKs(void) const;

		void
		SetCs(const RGBColor &c);

		void
		SetCs(const float r, const float g, const float b);

		void
		SetCs(const float c);
		
		const RGBColor&
		GetCs(void) const;

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


	protected:

		Lambertian     m_ambientBrdf;
		Lambertian     m_diffuseBrdf;
		GlossySpecular m_specularBrdf;
};



inline void
Phong::SetSampler(Sampler* sp) 
{
	if( sp )
	{
		m_diffuseBrdf.SetSampler(sp); 
		m_specularBrdf.SetSampler(sp->Clone());
	}
}


inline void
Phong::SetupSampler(const int numSamples, const float exp, const SamplerType samplerType)
{
	m_diffuseBrdf.SetupSampler(numSamples, exp, samplerType);
	m_specularBrdf.SetupSampler(numSamples, exp, samplerType);
}


inline void
Phong::SetKa(const float ka) 
{
	m_ambientBrdf.SetCoeff(ka);
}


inline float
Phong::GetKa(void) const
{
	return (m_ambientBrdf.GetCoeff());
}


inline void
Phong::SetKd (const float kd) 
{
	m_diffuseBrdf.SetCoeff(kd);
}


inline float
Phong::GetKd(void) const
{
	return (m_diffuseBrdf.GetCoeff());
}


inline void
Phong::SetCd(const RGBColor& c) 
{
	m_ambientBrdf.SetColor(c);
	m_diffuseBrdf.SetColor(c);
}


inline void
Phong::SetCd(const float r, const float g, const float b) 
{
	m_ambientBrdf.SetColor(r, g, b);
	m_diffuseBrdf.SetColor(r, g, b);
}


inline void
Phong::SetCd(const float c) 
{
	m_ambientBrdf.SetColor(c);
	m_diffuseBrdf.SetColor(c);
}


inline const RGBColor&
Phong::GetCd(void) const
{
	return (m_diffuseBrdf.GetColor());
}


inline void
Phong::SetKs(const float k) 
{
	m_specularBrdf.SetCoeff(k);
}


inline float
Phong::GetKs(void) const
{
	return (m_specularBrdf.GetCoeff());
}


inline void
Phong::SetCs(const RGBColor &c) 
{
	m_specularBrdf.SetColor(c);
}


inline void
Phong::SetCs(const float r, const float g, const float b) 
{
	m_specularBrdf.SetColor(r, g, b);
}


inline void
Phong::SetCs(const float c) 
{
	m_specularBrdf.SetColor(c);
}


inline const RGBColor&
Phong::GetCs(void) const
{
	return (m_specularBrdf.GetColor());
}


inline void
Phong::SetExponent(const float exp) 
{
	m_specularBrdf.SetExponent(exp);
}


inline float
Phong::GetExponent(void) const
{
	return (m_specularBrdf.GetExponent());
}


#endif