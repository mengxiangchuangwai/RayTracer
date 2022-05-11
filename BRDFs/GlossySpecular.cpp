//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../BRDFs/GlossySpecular.h"
#include "../Samplers/MultiJittered.h"

GlossySpecular::GlossySpecular(void)
	: BRDF()
	, m_exp(0.0)
{}


GlossySpecular::GlossySpecular(const GlossySpecular& other)
    : BRDF(other)
    , m_exp(other.m_exp)
{}


GlossySpecular::~GlossySpecular(void) 
{}


GlossySpecular*
GlossySpecular::Clone (void) const 
{
	return (new GlossySpecular(*this));
}


GlossySpecular&
GlossySpecular::operator= (const GlossySpecular& rhs) 
{
	if( this == &rhs )
		return (*this);

	BRDF::operator= (rhs);
    m_exp = rhs.m_exp;
	return (*this);
}


RGBColor
GlossySpecular::S(const RGBColor& clr, const ShadeContext& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const 
{
	double ndotwo = sr.normal * wo;
	Vector3D r = -wo + 2.0 * sr.normal * ndotwo;     // direction of mirror reflection

	Vector3D w = r;
	Vector3D u = Vector3D(0.00424, 1, 0.00764) ^ w;
	u.Normalize();
	Vector3D v = u ^ w;

	Point3D sp = m_sampler->SampleHemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;				// reflected ray direction

	if( sr.normal * wi < 0.0 )						// reflected ray is below tangent plane
		wi = -sp.x * u - sp.y * v + sp.z * w;

	float phongLobe = pow(r * wi, (double)m_exp);
	pdf = phongLobe * (sr.normal * wi);

	return (m_coeff * clr * phongLobe);
}