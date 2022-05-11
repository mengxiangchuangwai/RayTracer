//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../BRDFs/FresnelReflector.h"

FresnelReflector::FresnelReflector(void)
	: BRDF()
	, m_etaIn(1.5)
	, m_etaOut(1.0)
{}


FresnelReflector::FresnelReflector(const FresnelReflector& other)
	: BRDF(other)
	, m_etaIn(other.m_etaIn)
	, m_etaOut(other.m_etaOut)
{}


FresnelReflector::~FresnelReflector(void) 
{}


FresnelReflector* 
FresnelReflector::Clone(void) const 
{
	return (new FresnelReflector(*this));
}	


FresnelReflector&
FresnelReflector::operator= (const FresnelReflector& rhs) 
{
	if( this == &rhs )
		return (*this);

	m_etaIn		= rhs.m_etaIn;
	m_etaOut	= rhs.m_etaOut;
	return (*this);
}