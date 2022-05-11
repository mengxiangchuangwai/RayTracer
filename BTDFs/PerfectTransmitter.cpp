//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../BTDFs/PerfectTransmitter.h"

PerfectTransmitter::PerfectTransmitter(void)
	: BTDF()
	, m_ior(1.0)
{}


PerfectTransmitter::PerfectTransmitter(const PerfectTransmitter& other)
	: BTDF(other)
	, m_ior(other.m_ior)
{}


PerfectTransmitter* 
PerfectTransmitter::Clone(void) 
{
	return (new PerfectTransmitter(*this));
}


PerfectTransmitter::~PerfectTransmitter(void) 
{}

	
PerfectTransmitter&							
PerfectTransmitter::operator= (const PerfectTransmitter& rhs) 
{
	if( this == &rhs )
		return (*this);
		
	m_ior = rhs.m_ior;

	return (*this);
}


// this computes the direction wt for perfect transmission
// and returns the transmission coefficient
// this is only called when there is no total internal reflection

RGBColor
PerfectTransmitter::Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wt) const 
{
	Normal norm(sr.normal);
	double cosThetai = norm * wo;
	double eta = m_ior;	
		
	if( cosThetai < 0.0 ) 
	{								// transmitted ray is outside     
		cosThetai = -cosThetai;
		norm = -norm;  				// reverse direction of normal
		eta = 1.0 / eta; 			// invert ior 
	}

	double temp = 1.0 - (1.0 - cosThetai * cosThetai) / (eta * eta);
	double cosTheta2 = sqrt(temp);
	wt = -wo / eta - (cosTheta2 - cosThetai / eta) * norm;   
	
	return (m_coeff / (eta * eta) * m_color / (sr.normal * wt));
}