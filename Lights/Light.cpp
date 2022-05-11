//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Lights/Light.h"


Light::Light(void)
    : m_shadowing(false)
{}


Light::Light(const Light& other) 
	: m_shadowing(other.m_shadowing)
{}


Light&
Light::operator= (const Light& rhs) 
{
	if( this == &rhs )
		return (*this);

	m_shadowing = rhs.m_shadowing;

	return (*this);
}


Light::~Light(void) 
{}