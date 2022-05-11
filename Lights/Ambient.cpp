//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Lights/Ambient.h"

Ambient::Ambient (void)
	: Light()
	, m_ls(1.0)
	, m_color(1.0)
{}


Ambient::Ambient (const Ambient& other)
	: Light(other)
	, m_ls(other.m_ls)
	, m_color(other.m_color)
{}


Ambient*
Ambient::Clone(void) const 
{
	return (new Ambient(*this));
}


Ambient&
Ambient::operator= (const Ambient& rhs) 
{
	if( this == &rhs )
		return (*this);

	Light::operator= (rhs);

	m_ls 	= rhs.m_ls;
	m_color = rhs.m_color;

	return (*this);
}


Ambient::~Ambient (void) 
{}