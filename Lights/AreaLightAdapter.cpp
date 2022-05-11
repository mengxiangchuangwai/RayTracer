//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <iostream>

#include "../Lights/AreaLightAdapter.h"

AreaLightAdapter::AreaLightAdapter(void)
	: Light()
	, m_pEmitter(NULL)
{}


AreaLightAdapter::AreaLightAdapter(const AreaLightAdapter& other)
	: Light(other) 
{
	if( other.m_pEmitter )
		m_pEmitter = other.m_pEmitter->Clone();
	else
		m_pEmitter = NULL;
}


AreaLightAdapter*
AreaLightAdapter::Clone(void) const 
{
	return (new AreaLightAdapter(*this));
}


AreaLightAdapter::~AreaLightAdapter(void) 
{
	SAFE_DELETE(m_pEmitter);
}


AreaLightAdapter&
AreaLightAdapter::operator= (const AreaLightAdapter& rhs) 
{
	if( this == &rhs )
		return (*this);

	Light::operator= (rhs);

	SAFE_DELETE(m_pEmitter);

	if( rhs.m_pEmitter )
		m_pEmitter = rhs.m_pEmitter->Clone();

	return (*this);
}


bool
AreaLightAdapter::InShadow(const Ray& ray, const ShadeContext& sr) const 
{
	double tv;
	size_t num = sr.pWorld->m_objects.size();
	double ts = (m_samplePoint - ray.o) * ray.d;

	for( size_t i = 0; i < num; ++i ) 
	{
		if( sr.pWorld->m_objects[i]->ShadowHit(ray, tv) && tv < ts )
			return (true);
	}

	return (false);
}