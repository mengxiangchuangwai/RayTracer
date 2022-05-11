//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../BTDFs/BTDF.h"

BTDF::BTDF(void)
	: m_color(1.0)
	, m_coeff(0.0)
{}


BTDF::BTDF(const BTDF& other)
	: m_color(other.m_color)
	, m_coeff(other.m_coeff)
{}


BTDF::~BTDF(void) 
{}


BTDF&														
BTDF::operator= (const BTDF& rhs) 
{
	if( this == &rhs )
		return (*this);

	m_color = rhs.m_color;
	m_coeff = rhs.m_coeff;

	return (*this);
}


RGBColor
BTDF::Rho(const ShadeContext& sr, const Vector3D& wo) const 
{
	return (BLACK);
}


RGBColor
BTDF::Rho(const Texture* tp, const ShadeContext& sr, const Vector3D& wo) const 
{
	return (BLACK);
}


RGBColor
BTDF::Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wt) const 
{
	return (BLACK);
}


RGBColor
BTDF::Sample(const Texture* tp, const ShadeContext& sr, const Vector3D& wo, Vector3D& wt) const 
{
	return (BLACK);
}