//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Lights/PointLight.h"
#include "../World/World.h"

PointLight::PointLight(void)
	: Light()
	, m_ls(1.0f)
	, m_color(1.0f)
	, m_location(0.0f, 1.0f, 0.0f)
{}


PointLight::PointLight(const PointLight& other)
	: Light(other)
	, m_ls(other.m_ls)
	, m_color(other.m_color)
	, m_location(other.m_location)
{}


PointLight*
PointLight::Clone(void) const 
{
	return (new PointLight(*this));
}


PointLight&
PointLight::operator= (const PointLight& rhs)
{
	if( this == &rhs )
		return (*this);

	Light::operator= (rhs);

	m_ls		= rhs.m_ls;
	m_color 	= rhs.m_color;
	m_location 	= rhs.m_location;

	return (*this);
}


PointLight::~PointLight(void) 
{}


inline bool
PointLight::InShadow(const Ray &ray, const ShadeContext &sr) const
{
    double tv;
    size_t num = sr.pWorld->m_objects.size();
    double dist = m_location.Distance(ray.o);

    for( size_t i = 0; i < num; ++i ) 
	{
        if( sr.pWorld->m_objects[i]->ShadowHit(ray, tv) && tv < dist )
            return true;
    }

    return false;

}