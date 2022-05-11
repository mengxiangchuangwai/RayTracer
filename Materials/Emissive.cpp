//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Materials/Emissive.h"

Emissive::Emissive (void)
	: Material()
	, m_ls(1.0)
	, m_ce(0.0)
{}


Emissive::Emissive(const Emissive& other)
	: Material(other)
	, m_ls(other.m_ls)
	, m_ce(other.m_ce)
{}


Emissive*
Emissive::Clone(void) const 
{
	return (new Emissive(*this));
}


Emissive&
Emissive::operator= (const Emissive& rhs) 
{
	if( this == &rhs )
		return (*this);

	Material::operator= (rhs);

	m_ls = rhs.m_ls;
    m_ce = rhs.m_ce;

	return (*this);
}


Emissive::~Emissive(void) 
{}