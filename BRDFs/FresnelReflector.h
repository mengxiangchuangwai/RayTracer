//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __FRESNEL_REFLECTOR__
#define __FRESNEL_REFLECTOR__


#include "../BRDFs/BRDF.h"
#include "../Utilities/Normal.h"

class FresnelReflector: public BRDF 
{
	public:
	
		FresnelReflector(void);
		
		FresnelReflector(const FresnelReflector& other);

		virtual ~FresnelReflector(void);

		virtual FresnelReflector*
		Clone(void) const;

		FresnelReflector&
		operator= (const FresnelReflector& rhs);
		
		virtual RGBColor
		Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wr) const;

		virtual RGBColor
		Sample(const Texture *tp, const ShadeContext& sr, const Vector3D& wo, Vector3D& wr) const;
		
		virtual RGBColor
		Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wr, float& pdf) const;

		virtual RGBColor
		Sample(const Texture *tp, const ShadeContext& sr, const Vector3D& wo, Vector3D& wr, float& pdf) const;

		void 
		SetRefractionIndices(const float etaIn, const float etaOut);

		void
		ComputeCoefficient(const ShadeContext& sr);


	private:

		float	m_etaIn;
		float	m_etaOut;
};


inline void 
FresnelReflector::SetRefractionIndices(const float etaIn, const float etaOut) 
{
	m_etaIn		= etaIn;
	m_etaOut	= etaOut;
}


inline RGBColor
FresnelReflector::Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wr) const 
{
	double ndotwo = sr.normal * wo;
	wr = -wo + 2.0 * sr.normal * ndotwo; 
	return (m_coeff * m_color / (sr.normal * wr));
}


inline RGBColor
FresnelReflector::Sample(const Texture *tp, const ShadeContext& sr, const Vector3D& wo, Vector3D& wr) const 
{
	double ndotwo = sr.normal * wo;
	wr = -wo + 2.0 * sr.normal * ndotwo; 
	return (m_coeff * tp->GetColor(sr) / (sr.normal * wr));
}


inline RGBColor
FresnelReflector::Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wr, float& pdf) const 
{
	double ndotwo = sr.normal * wo;
	wr = -wo + 2.0 * sr.normal * ndotwo;
	pdf = (float)(sr.normal * wr);
	return (m_coeff * m_color);  
}


inline RGBColor
FresnelReflector::Sample(const Texture *tp, const ShadeContext& sr, const Vector3D& wo, Vector3D& wr, float& pdf) const 
{
	double ndotwo = sr.normal * wo;
	wr = -wo + 2.0 * sr.normal * ndotwo; 
	pdf = (float)(sr.normal * wr);
	return (m_coeff * tp->GetColor(sr));  
}


inline void
FresnelReflector::ComputeCoefficient(const ShadeContext& sr) 
{
	double ndotd = -sr.normal * sr.ray.d;
	double eta;
	
	if( ndotd < 0.0 ) 
	{ 
		ndotd = -ndotd;
		eta = m_etaOut / m_etaIn;
	}
	else
		eta = m_etaIn / m_etaOut;

	double cosThetai 	= ndotd;
	double cosThetat 	= sqrt(1.0 - (1.0 - cosThetai * cosThetai) / (eta * eta));
	double rparallel 	= (eta * cosThetai - cosThetat) / (eta * cosThetai + cosThetat);
	double rperpend 	= (cosThetai - eta * cosThetat) / (cosThetai + eta * cosThetat);

	m_coeff = (float)(0.5 * (rparallel * rparallel + rperpend * rperpend));
}


#endif