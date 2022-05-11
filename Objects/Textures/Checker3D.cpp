//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <cmath>
#include "../Textures/Checker3D.h"
#include "../Utilities/Constants.h"
#include "../Utilities/RGBColor.h"

Checker3D::Checker3D(void)
    : Texture()
	, m_size(1.0)
	, m_color1(WHITE)
	, m_color2(0.5)
{}


Checker3D::Checker3D(const Checker3D& other)
    : Texture(other)
	, m_size(other.m_size)
	, m_color1(other.m_color1)
	, m_color2(other.m_color2)
{}


Checker3D&
Checker3D::operator= (const Checker3D& rhs) 
{
    if( this == &rhs )
        return (*this);

    Texture::operator= (rhs);
    m_size		= rhs.m_size;
    m_color1	= rhs.m_color1;
    m_color2	= rhs.m_color2;

    return (*this);
}


Checker3D*
Checker3D::Clone(void) const 
{
    return (new Checker3D(*this));
}


Checker3D::~Checker3D(void) 
{}


RGBColor
Checker3D::GetColor(const ShadeContext& sr) const 
{
    double eps = -0.000187453738;	// small random number
	int ix = (int)floor((sr.localHitPoint.x + eps) / m_size);
	int iy = (int)floor((sr.localHitPoint.y + eps) / m_size);
	int iz = (int)floor((sr.localHitPoint.z + eps) / m_size);

    if( 0 == (ix + iy + iz) % 2 )
        return (m_color1);
    else
        return (m_color2);
}