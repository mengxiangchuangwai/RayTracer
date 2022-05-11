//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../BRDFs/BRDF.h"
#include "../Samplers/Hammersley.h"
#include "../Samplers/Jittered.h"
#include "../Samplers/MultiJittered.h"
#include "../Samplers/NRooks.h"
#include "../Samplers/PureRandom.h"
#include "../Samplers/Regular.h"
#include "../Utilities/RGBColor.h"

BRDF::BRDF(void)
	: m_color(1.0)
	, m_coeff(0.0)
    , m_sampler(NULL)
{}


BRDF::BRDF (const BRDF& other) 
	: m_color(other.m_color)
	, m_coeff(other.m_coeff)
{
	if( other.m_sampler )
		m_sampler = other.m_sampler->Clone();
	else  
		m_sampler = NULL;

}


BRDF&
BRDF::operator= (const BRDF& rhs) 
{
	if( this == &rhs )
		return (*this);

	m_color = rhs.m_color;
	m_coeff = rhs.m_coeff;

	SAFE_DELETE(m_sampler);

	if( rhs.m_sampler )
		m_sampler = rhs.m_sampler->Clone();

	return (*this);
}


BRDF::~BRDF(void) 
{
	SAFE_DELETE(m_sampler);
}


void
BRDF::SetSampler(Sampler* sp, const float exp) 
{
	SAFE_DELETE(m_sampler);

	if( m_sampler = sp )
		m_sampler->SamplesToHemisphere(exp);
}


void
BRDF::SetupSampler(const int numSamples, const float exp, const SamplerType type) 
{
    SAFE_DELETE(m_sampler);

	switch( type ) 
	{
		case ST_Hammersley:
			m_sampler = new Hammersley(numSamples);
			break;
		case ST_Jittered:
			m_sampler = new Jittered(numSamples);
			break;
		case ST_MultiJittered:
		default:
			m_sampler = new MultiJittered(numSamples);
			break;
		case ST_NRooks:
			m_sampler = new NRooks(numSamples);
			break;
		case ST_PureRandom:
			m_sampler = new PureRandom(numSamples);
			break;
		case ST_Regular:
			m_sampler = new Regular(numSamples);
			break;
	}

	if( m_sampler )
        m_sampler->SamplesToHemisphere(exp);
}


RGBColor
BRDF::F(const ShadeContext& sr, const Vector3D& wo, const Vector3D& wi) const 
{
	return (BLACK);
}


RGBColor
BRDF::F(const Texture *tp, 
		const ShadeContext& sr, const Vector3D& wo, const Vector3D& wi) const 
{
	return (BLACK);
}


RGBColor
BRDF::Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wi) const 
{
	return (BLACK);
}


RGBColor
BRDF::Sample(const Texture *tp, 
			   const ShadeContext& sr, const Vector3D& wo, Vector3D& wi) const 
{
	return (BLACK);
}


RGBColor
BRDF::Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const 
{
	return (BLACK);
}


RGBColor
BRDF::Sample(const Texture *tp, 
			   const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const 
{
	return (BLACK);
}


RGBColor
BRDF::Rho(const ShadeContext& sr, const Vector3D& wo) const 
{
	return (BLACK);
}


RGBColor
BRDF::Rho(const Texture *tp, 
		  const ShadeContext& sr, const Vector3D& wo) const 
{
	return (BLACK);
}