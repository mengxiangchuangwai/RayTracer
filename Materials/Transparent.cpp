///  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Materials/Transparent.h"

Transparent::Transparent (void) 
	: Phong()
{}


Transparent::Transparent(const Transparent& other)
	: Phong(other)
	, m_reflector(other.m_reflector)
	, m_transmitter(other.m_transmitter)
{}


Transparent*
Transparent::Clone(void) const 
{
	return (new Transparent(*this));
}


Transparent&
Transparent::operator= (const Transparent& rhs) 
{
	if( this == &rhs )
		return (*this);

	Phong::operator= (rhs);
    m_reflector = rhs.m_reflector;
	m_transmitter = rhs.m_transmitter;
	return (*this);
}


Transparent::~Transparent(void) 
{
}


RGBColor 
Transparent::Trace(ShadeContext& sr)
{
	bool  tir = m_transmitter.IsTir(sr);
	float kr;

	if( tir ) 
	{
		m_cs.lock();
		kr = m_reflector.GetCoeff();
		m_reflector.SetCoeff(1.0);
	}

	RGBColor L(0.0);
	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	RGBColor fr = m_reflector.Sample(sr, wo, wi);			// computes wi
	Ray reflectedRay(sr.hitPoint, wi);
	
	if( tir ) 
	{
		m_reflector.SetCoeff(kr);
		m_cs.unlock();
		L = fr * sr.pWorld->GetTracer()->TraceRay(reflectedRay, sr.depth + 1) * (sr.normal * wi);;
	// kr = 1.0
	}
	else {
		Vector3D wt;
		RGBColor ft = m_transmitter.Sample(sr, wo, wt);		// computes wt
		Ray transmittedRay(sr.hitPoint, wt);
		
		L  = fr * sr.pWorld->GetTracer()->TraceRay(reflectedRay, sr.depth + 1) * (sr.normal * wi);
		L += ft * sr.pWorld->GetTracer()->TraceRay(transmittedRay, sr.depth + 1) * (sr.normal * wt);
	}
	
	return (L);
}