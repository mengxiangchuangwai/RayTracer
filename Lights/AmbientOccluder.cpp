//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Lights/AmbientOccluder.h"
#include "../World/World.h"

AmbientOccluder::AmbientOccluder(void)
	: Light()
    , m_ls(1.0)
    , m_color(1.0)
    , m_minAmount(0.0)
    , m_u(1.0, 0.0, 0.0)
    , m_v(0.0, 1.0, 0.0)
    , m_w(0.0, 0.0, 1.0)
    , m_pSampler(NULL)
{}


AmbientOccluder::AmbientOccluder(const AmbientOccluder& other)
	: Light(other)
	, m_ls(other.m_ls)
	, m_color(other.m_color)
	, m_minAmount(other.m_minAmount)
	, m_u(other.m_u)
	, m_v(other.m_v)
	, m_w(other.m_w)
{
	if (other.m_pSampler)
		m_pSampler = other.m_pSampler->Clone();
	else
		m_pSampler = NULL;
}


AmbientOccluder*
AmbientOccluder::Clone(void) const 
{
	return (new AmbientOccluder(*this));
}


AmbientOccluder&
AmbientOccluder::operator= (const AmbientOccluder& rhs)
{
	if( this == &rhs )
		return *this;

	Light::operator= (rhs);

	m_ls		= rhs.m_ls;
	m_color 	= rhs.m_color;
	m_minAmount	= rhs.m_minAmount;
	m_u 		= rhs.m_u;
	m_v 		= rhs.m_v;
	m_w 		= rhs.m_w;

	SAFE_DELETE(m_pSampler);

	if( rhs.m_pSampler )
		m_pSampler = rhs.m_pSampler->Clone();

	return *this;
}


AmbientOccluder::~AmbientOccluder(void) 
{
	SAFE_DELETE(m_pSampler);
}


bool
AmbientOccluder::InShadow(const Ray& ray, const ShadeContext& sr) const 
{
	double tv;
	size_t num = sr.pWorld->m_objects.size();

	for( size_t i = 0; i < num; ++i ) 
	{
		if( sr.pWorld->m_objects[i]->ShadowHit(ray, tv) )
			return true;
	}

	return false;
}


RGBColor
AmbientOccluder::L(ShadeContext& sr) 
{
	BeginSection();
	
	m_w = sr.normal;
	m_v = m_w ^ Vector3D(0.0072, 1.0, 0.0034); // jitter the up vector in case normal is vertical
	m_v.Normalize();
	m_u = m_v ^ m_w;

	Ray shadowRay;
	shadowRay.o = sr.hitPoint;
	shadowRay.d = GetDirection(sr);
	
	EndSection();

	if( InShadow(shadowRay, sr) )
		return (m_minAmount * m_ls * m_color);
	else
		return (m_ls * m_color);
}