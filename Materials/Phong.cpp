//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Materials/Phong.h"

Phong::Phong (void) 
	: Material()
{}


Phong::Phong(const Phong& other)
	: Material(other) 
{
    m_ambientBrdf    = other.m_ambientBrdf;
	m_diffuseBrdf    = other.m_diffuseBrdf;
	m_specularBrdf   = other.m_specularBrdf;
}


Phong*
Phong::Clone(void) const 
{
	return (new Phong(*this));
}


Phong&
Phong::operator= (const Phong& rhs) 
{
	if( this == &rhs )
		return (*this);

	Material::operator= (rhs);
    m_ambientBrdf    = rhs.m_ambientBrdf;
    m_diffuseBrdf    = rhs.m_diffuseBrdf;
	m_specularBrdf   = rhs.m_specularBrdf;
	return (*this);
}


Phong::~Phong(void) 
{}


RGBColor
Phong::Shade(ShadeContext& sr) 
{
	Vector3D	wo = -sr.ray.d;
    RGBColor	result = ((NULL != m_pDiffuse) ? m_ambientBrdf.Rho(m_pDiffuse, sr, wo) : m_ambientBrdf.Rho(sr, wo)) * sr.pWorld->GetAmbient()->L(sr);
    size_t		num = sr.pWorld->m_lights.size();

    for( size_t i = 0; i < num; ++i ) 
	{
        Light* pLight = sr.pWorld->m_lights[i];

		pLight->BeginSection();
		Vector3D wi = pLight->GetDirection(sr);
        double ndotwi = sr.normal * wi;

        if( ndotwi > 0.0f ) 
		{
            bool illum = true;

            if( pLight->CastsShadows() ) 
			{
                Ray shadowRay(sr.hitPoint, wi);
                illum = !pLight->InShadow(shadowRay, sr);
            }

            if( illum ) 
			{
                result += (((NULL != m_pDiffuse) ? m_diffuseBrdf.F(m_pDiffuse, sr, wo, wi) : m_diffuseBrdf.F(sr, wo, wi)) 
					+ ((NULL != m_pSpecular) ? m_specularBrdf.F(m_pSpecular, sr, wo, wi) : m_specularBrdf.F(sr, wo, wi))) * pLight->L(sr) * ndotwi;
            }
        }

		pLight->EndSection();
    }

    return (result);
}


RGBColor
Phong::AreaLightShade(ShadeContext &sr) 
{
    Vector3D	wo = -sr.ray.d;
    RGBColor	result = ((NULL != m_pDiffuse) ? m_ambientBrdf.Rho(m_pDiffuse, sr, wo) : m_ambientBrdf.Rho(sr, wo)) * sr.pWorld->GetAmbient()->L(sr);
    size_t		num = sr.pWorld->m_lights.size();

    for( size_t i = 0; i < num; ++i ) 
	{
		Light* pLight = sr.pWorld->m_lights[i];

		pLight->BeginSection();
        Vector3D wi = pLight->GetDirection(sr);
        double ndotwi = sr.normal * wi;

        if( ndotwi > 0.0 )
		{
            bool illum = true;

            if( pLight->CastsShadows() ) 
			{
                Ray shadowRay(sr.hitPoint, wi);
                illum = !pLight->InShadow(shadowRay, sr);
            }

            if( illum ) 
			{
                result += (((NULL != m_pDiffuse) ? m_diffuseBrdf.F(m_pDiffuse, sr, wo, wi) : m_diffuseBrdf.F(sr, wo, wi)) 
					+ ((NULL != m_pSpecular) ? m_specularBrdf.F(m_pSpecular, sr, wo, wi) : m_specularBrdf.F(sr, wo, wi))) * pLight->L(sr) * pLight->G(sr) * ndotwi / pLight->Pdf(sr);
            }
        }

		pLight->EndSection();
    }

    return (result);
}


RGBColor
Phong::PathShade(ShadeContext& sr) 
{
	RGBColor result(0.0);

	if( 0 == sr.depth )
		result = AreaLightShade(sr);
	
	Vector3D 	wi;
	Vector3D 	wo 		= -sr.ray.d;
	float 		pdf;
	RGBColor 	fr		= m_specularBrdf.Sample(sr, wo, wi, pdf); 
	float 		ndotwi 	= sr.normal * wi;
	Ray 		reflectedRay(sr.hitPoint, wi);
	result += fr * sr.pWorld->GetTracer()->TraceRay(reflectedRay, sr.depth + 1) * ndotwi / pdf;

	return (result);
}