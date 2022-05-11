//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __MATTE__
#define __MATTE__


#include "../Utilities/Lock.h"
#include "../Materials/Material.h"
#include "../BRDFs/Lambertian.h"

class Matte: public Material {
	public:

		Matte(void);

		Matte(const Matte& other);

		virtual Matte*
		Clone(void) const;

		Matte&
		operator= (const Matte& rhs);

		virtual 
		~Matte(void);

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
		SetCd(const RGBColor c);

		void
		SetCd(const float r, const float g, const float b);

		void
		SetCd(const float c);

		const RGBColor&
		GetCd(void) const;

		virtual RGBColor
		Shade(ShadeContext& sr);

		virtual RGBColor
		AreaLightShade(ShadeContext& sr);

		virtual RGBColor
		PathShade(ShadeContext& sr);


	private:
		
		Lambertian		m_ambientBrdf;
		Lambertian		m_diffuseBrdf;
};



inline void
Matte::SetSampler(Sampler* sp) 
{
	m_diffuseBrdf.SetSampler(sp);
}


inline void
Matte::SetupSampler(const int numSamples, const float exp, const SamplerType samplerType) 
{
	m_diffuseBrdf.SetupSampler(numSamples, exp, samplerType);	
}


inline void
Matte::SetKa(const float ka) 
{
	m_ambientBrdf.SetCoeff(ka);
}


inline float
Matte::GetKa(void) const
{
	return (m_ambientBrdf.GetCoeff());
}


inline void
Matte::SetKd (const float kd) 
{
	m_diffuseBrdf.SetCoeff(kd);
}


inline float
Matte::GetKd(void) const
{
	return (m_diffuseBrdf.GetCoeff());
}


inline void
Matte::SetCd(const RGBColor c) 
{
	m_ambientBrdf.SetColor(c);
	m_diffuseBrdf.SetColor(c);
}


inline void
Matte::SetCd(const float r, const float g, const float b) 
{
	m_ambientBrdf.SetColor(r, g, b);
	m_diffuseBrdf.SetColor(r, g, b);
}


inline void
Matte::SetCd(const float c) 
{
	m_ambientBrdf.SetColor(c);
	m_diffuseBrdf.SetColor(c);
}


inline const RGBColor&
Matte::GetCd(void) const
{
	return (m_diffuseBrdf.GetColor());
}


#endif