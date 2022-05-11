//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Lights/EnvironmentLight.h"
#include "../World/World.h"

EnvironmentLight::EnvironmentLight()
    : Light()
    , m_pSampler(NULL)
    , m_pMaterial(NULL)
{
}


EnvironmentLight::EnvironmentLight(const EnvironmentLight& other)
    : Light(other)
{
    if( other.m_pSampler )
        m_pSampler = other.m_pSampler->Clone();
    else
        m_pSampler = NULL;

    if( other.m_pMaterial )
        m_pMaterial = other.m_pMaterial->Clone();
    else
        m_pMaterial = NULL;
}


EnvironmentLight*
EnvironmentLight::Clone(void) const
{
    return (new EnvironmentLight(*this));
}


EnvironmentLight::~EnvironmentLight(void)
{
	SAFE_DELETE(m_pSampler);
	SAFE_DELETE(m_pMaterial);
}


EnvironmentLight&
EnvironmentLight::operator= (const EnvironmentLight& rhs)
{
    if( this == &rhs )
		return (*this);

	Light::operator= (rhs);

	SAFE_DELETE(m_pSampler);

	if( rhs.m_pSampler )
		m_pSampler = rhs.m_pSampler->Clone();

	SAFE_DELETE(m_pMaterial);

	if( rhs.m_pMaterial )
        m_pMaterial = rhs.m_pMaterial->Clone();

	return (*this);
}


bool
EnvironmentLight::InShadow(const Ray& ray, const ShadeContext& sr) const 
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