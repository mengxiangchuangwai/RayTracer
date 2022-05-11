//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __LAMBERTIAN__
#define __LAMBERTIAN__


#include "../BRDFs/BRDF.h"

class Lambertian: public BRDF {
	public:

		Lambertian(void);

		Lambertian(const Lambertian& other);

		virtual Lambertian*
		Clone(void) const;

		Lambertian&
		operator= (const Lambertian& rhs);

		virtual 
		~Lambertian(void);

		virtual RGBColor
		F(const ShadeContext& sr, const Vector3D& wo, const Vector3D& wi) const;

		virtual RGBColor
		F(const Texture *tp, const ShadeContext& sr, const Vector3D& wo, const Vector3D& wi) const;

		virtual RGBColor
		Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

		virtual RGBColor
		Sample(const Texture *tp, const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

		virtual RGBColor
		Rho(const ShadeContext& sr, const Vector3D& wo) const;

		virtual RGBColor
		Rho(const Texture *tp, const ShadeContext& sr, const Vector3D& wo) const;


	private:

		RGBColor
		S(const RGBColor& clr, const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
};



inline RGBColor
Lambertian::F(const ShadeContext& sr, const Vector3D& wo, const Vector3D& wi) const 
{
	return (m_coeff * m_color * invPI);
}


inline RGBColor
Lambertian::F(const Texture *tp, 
			  const ShadeContext& sr, const Vector3D& wo, const Vector3D& wi) const 
{
	return (m_coeff * tp->GetColor(sr) * invPI);
}


// this generates a direction by sampling the hemisphere with a cosine distribution
// this is called in path_shade for any material with a diffuse shading component
// the samples have to be stored with a cosine distribution

inline RGBColor
Lambertian::Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const 
{
	return (S(m_color, sr, wo, wi, pdf));
}


inline RGBColor
Lambertian::Sample(const Texture *tp, 
					 const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const 
{
	return (S(tp->GetColor(sr), sr, wo, wi, pdf));
}


inline RGBColor
Lambertian::Rho(const ShadeContext& sr, const Vector3D& wo) const 
{
	return (m_coeff * m_color);
}


inline RGBColor
Lambertian::Rho(const Texture *tp, 
				const ShadeContext& sr, const Vector3D& wo) const 
{
	return (m_coeff * tp->GetColor(sr));
}


#endif
