//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Materials/Material.h"

Material::Material(void)
	: m_pDiffuse(NULL)
	, m_pSpecular(NULL)
	, m_pEmissive(NULL)
	, m_shadowing(true)
{}


Material::Material(const Material& other) 
	: 	m_shadowing(other.m_shadowing)
{
	if( other.m_pDiffuse )
		m_pDiffuse = other.m_pDiffuse->Clone();
	else
		m_pDiffuse = NULL;

	if( other.m_pSpecular )
		m_pSpecular = other.m_pSpecular->Clone();
	else
		m_pSpecular = NULL;

	if( other.m_pEmissive )
		m_pEmissive = other.m_pEmissive->Clone();
	else
		m_pEmissive = NULL;
}


Material&
Material::operator= (const Material& rhs) 
{
	if( this == &rhs )
		return (*this);

	SAFE_DELETE(m_pDiffuse);

	if( rhs.m_pDiffuse )
		m_pDiffuse = rhs.m_pDiffuse->Clone();

	SAFE_DELETE(m_pSpecular);

	if( rhs.m_pSpecular )
		m_pSpecular = rhs.m_pSpecular->Clone();

	SAFE_DELETE(m_pEmissive);

	if( rhs.m_pEmissive )
		m_pEmissive = rhs.m_pEmissive->Clone();
	
	m_shadowing = rhs.m_shadowing;

	return (*this);
}


Material::~Material(void) 
{
	SAFE_DELETE(m_pDiffuse);
	SAFE_DELETE(m_pSpecular);
	SAFE_DELETE(m_pEmissive);
}


RGBColor
Material::Shade(ShadeContext& sr) 
{
	return (BLACK);
}


RGBColor
Material::AreaLightShade(ShadeContext &sr) 
{
    return (BLACK);
}


RGBColor
Material::PathShade(ShadeContext& sr) 
{
	return (BLACK);
}


RGBColor
Material::GetLe(ShadeContext &sr) const 
{
    return BLACK;
}


void Material::SetDiffuseTexture(Texture* tp) 
{
	SAFE_DELETE(m_pDiffuse);
	m_pDiffuse = tp;
}


Texture* Material::GetDiffuseTexture(void) const 
{
	return m_pDiffuse;
}


void Material::SetSpecularTexture(Texture* tp) 
{
	SAFE_DELETE(m_pSpecular);
	m_pSpecular = tp;
}


Texture* Material::GetSpecularTexture(void) const 
{
	return m_pSpecular;
}


void Material::SetEmissiveTexture(Texture* tp) 
{
	SAFE_DELETE(m_pEmissive);
	m_pEmissive = tp;
}


Texture* Material::GetEmissiveTexture(void) const 
{
	return m_pEmissive;
}