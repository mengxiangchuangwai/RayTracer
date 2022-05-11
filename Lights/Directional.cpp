//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Lights/Directional.h"
#include "../World/World.h"	

Directional::Directional(void)
	: Light()
	, m_ls(1.0)
	, m_color(1.0)
	, m_dir(0, 1, 0)
{}


Directional::Directional(const Directional& other)
	: Light(other)
	, m_ls(other.m_ls)
	, m_color(other.m_color)
	, m_dir(other.m_dir)
{}


Directional*
Directional::Clone(void) const 
{
	return (new Directional(*this));
}


Directional&
Directional::operator= (const Directional& rhs)
{
	if( this == &rhs )
		return (*this);

	Light::operator= (rhs);

	m_ls	= rhs.m_ls;
	m_color = rhs.m_color;
	m_dir 	= rhs.m_dir;

	return (*this);
}


Directional::~Directional(void) 
{}


bool
Directional::InShadow(const Ray &ray, const ShadeContext &sr) const
{
    double tv;
    size_t num = sr.pWorld->m_objects.size();

    for( size_t i = 0; i < num; ++i ) 
	{
        if( sr.pWorld->m_objects[i]->ShadowHit(ray, tv) && tv > 0 )
            return true;
    }

    return false;
}