//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../BRDFs/PerfectSpecular.h"

PerfectSpecular::PerfectSpecular(void)
	: BRDF()
{}


PerfectSpecular::PerfectSpecular(const PerfectSpecular& other)
	: BRDF(other)
{}


PerfectSpecular::~PerfectSpecular(void) 
{}


PerfectSpecular* 
PerfectSpecular::Clone(void) const 
{
	return (new PerfectSpecular(*this));
}	


PerfectSpecular&
PerfectSpecular::operator= (const PerfectSpecular& rhs) 
{
	if( this == &rhs )
		return (*this);

	return (*this);
}