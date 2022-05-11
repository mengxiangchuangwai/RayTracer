//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __PERFECT_TRANSMITTER__
#define __PERFECT_TRANSMITTER__

// this implements perfect specular transmission for transparent materials

#include "../BTDFs/BTDF.h"

class PerfectTransmitter: public BTDF {
	public:
	
		PerfectTransmitter(void);
		
		PerfectTransmitter(const PerfectTransmitter& other);
		
		virtual PerfectTransmitter*
		Clone(void);
		
		~PerfectTransmitter(void);
		
		PerfectTransmitter&							
		operator= (const PerfectTransmitter& rhs);
	
		void
		SetIor(const float eta);

		float
		GetIor(void) const;

		bool													
		IsTir(const ShadeContext& sr) const;
		
		virtual RGBColor
		Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wt) const;

				
	private:

		float		m_ior;		// index of refraction
};



inline void
PerfectTransmitter::SetIor(const float eta) 
{
	m_ior = eta;
}


inline float
PerfectTransmitter::GetIor(void) const
{
	return (m_ior);
}


inline bool													
PerfectTransmitter::IsTir(const ShadeContext& sr) const 
{
	Vector3D wo(-sr.ray.d); 
	double cosThetai = sr.normal * wo;  
	double eta = m_ior;
	
	if( cosThetai < 0.0 ) 
		eta = 1.0 / eta; 
		
	return (1.0 - (1.0 - cosThetai * cosThetai) / (eta * eta) < 0.0);
}	


#endif
