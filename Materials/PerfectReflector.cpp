//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <iostream>
#include "../Materials/PerfectReflector.h"

PerfectReflector::PerfectReflector (void) 
	: Phong() 
{}


PerfectReflector::PerfectReflector(const PerfectReflector& other) 
	: Phong(other)
	, m_reflector(other.m_reflector)
{}


PerfectReflector& 
PerfectReflector::operator= (const PerfectReflector& rhs) 
{
	if( this == &rhs )
		return (*this);
		
	Phong::operator= (rhs);
	m_reflector = rhs.m_reflector;

	return (*this);
}


PerfectReflector*										
PerfectReflector::Clone(void) const 
{
	return (new PerfectReflector(*this));
}	


PerfectReflector::~PerfectReflector(void) 
{}