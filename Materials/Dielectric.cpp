//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <iostream>
#include "../Materials/Dielectric.h"

Dielectric::Dielectric (void) 
	: Phong()
	, m_filterIn(1.0)
	, m_filterOut(1.0)
{}


Dielectric::Dielectric(const Dielectric& other)
	: Phong(other)
	, m_filterIn(other.m_filterIn)
	, m_filterOut(other.m_filterOut)
	, m_reflector(other.m_reflector)
	, m_transmitter(other.m_transmitter)
{}


Dielectric*
Dielectric::Clone(void) const 
{
	return (new Dielectric(*this));
}


Dielectric&
Dielectric::operator= (const Dielectric& rhs) 
{
	if( this == &rhs )
		return (*this);

	Phong::operator= (rhs);

    m_filterIn		= rhs.m_filterIn;
	m_filterOut		= rhs.m_filterOut;
	m_reflector		= rhs.m_reflector;
	m_transmitter	= rhs.m_transmitter;
	
	return (*this);
}


Dielectric::~Dielectric(void) 
{}


RGBColor 
Dielectric::Trace(ShadeContext& sr)
{
	bool tir = m_transmitter.IsTir(sr);
	m_cs.lock();

	if( !tir ) 
	{
		m_reflector.ComputeCoefficient(sr);
		m_transmitter.SetCoeff(1.0 - m_reflector.GetCoeff());
	}
	else
		m_reflector.SetCoeff(1.0);

	RGBColor result(0.0);
		
	Vector3D 	wi;
	Vector3D 	wo(-sr.ray.d);
	RGBColor 	fr = m_reflector.Sample(sr, wo, wi);		// computes wi
	Ray 		reflectedRay(sr.hitPoint, wi); 
	double 		tval = 1.0;
	RGBColor 	Lr, Lt;
	double 		ndotwi =  sr.normal * wi;
		
	if( tir ) 
	{														// total internal reflection
		m_cs.unlock();
															
		if( ndotwi < 0.0 ) 
		{  	
			// reflected ray is inside
			
			Lr = fr * sr.pWorld->GetTracer()->TraceRay(reflectedRay, tval, sr.depth + 1) * ndotwi;
			result += m_filterIn.Powc(tval) * Lr;   		// inside filter color
		}
		else 
		{				
			// reflected ray is outside
			
			Lr = fr * sr.pWorld->GetTracer()->TraceRay(reflectedRay, tval, sr.depth + 1) * ndotwi;
			result += m_filterOut.Powc(tval) * Lr;   		// outside filter color
		}
	}
	else 
	{ 														// no total internal reflection
		Vector3D wt;
		RGBColor ft = m_transmitter.Sample(sr, wo, wt);  	// computes wt
		m_cs.unlock();
	
		Ray transmittedRay(sr.hitPoint, wt);
		double ndotwt = sr.normal * wt;
							
		if( ndotwi < 0.0 ) 
		{
			// reflected ray is inside
						
			Lr = fr * sr.pWorld->GetTracer()->TraceRay(reflectedRay, tval, sr.depth + 1) * ndotwi;
			result += m_filterIn.Powc(tval) * Lr;     		// inside filter color
			
			// transmitted ray is outside
							
			Lt = ft * sr.pWorld->GetTracer()->TraceRay(transmittedRay, tval, sr.depth + 1) * ndotwt; 
			result += m_filterOut.Powc(tval) * Lt;   		// outside filter color
		}
		else 
		{				
			// reflected ray is outside

			Lr = fr * sr.pWorld->GetTracer()->TraceRay(reflectedRay, tval, sr.depth + 1) * ndotwi; 
			result += m_filterOut.Powc(tval) * Lr;			// outside filter color

			// transmitted ray is inside
			
			Lt = ft * sr.pWorld->GetTracer()->TraceRay(transmittedRay, tval, sr.depth + 1) * ndotwt; 
			result += m_filterIn.Powc(tval) * Lt; 			// inside filter color
		}		
	}	
	
	return (result);
}