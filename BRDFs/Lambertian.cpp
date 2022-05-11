//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../BRDFs/Lambertian.h"
#include "../Utilities/Constants.h"

Lambertian::Lambertian(void) 
	: BRDF() 
{ 
	m_color.Set(0.0, 0.0, 0.0);
}


Lambertian::Lambertian(const Lambertian& other) 
	: BRDF(other)
{}


Lambertian*
Lambertian::Clone(void) const 
{
	return (new Lambertian(*this));
}


Lambertian::~Lambertian(void) 
{}


Lambertian&
Lambertian::operator= (const Lambertian& other) 
{
	if( this == &other )
		return (*this);

	BRDF::operator= (other);
	return (*this);
}


RGBColor
Lambertian::S(const RGBColor& clr, const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const 
{
	Vector3D w(sr.normal);
	Vector3D v = Vector3D(0.0034, 1, 0.0071) ^ w;
	v.Normalize();
	Vector3D u = v ^ w;

	Point3D sp = m_sampler->SampleHemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	wi.Normalize();

	pdf = sr.normal * wi * invPI;
	return (m_coeff * clr * invPI);
}