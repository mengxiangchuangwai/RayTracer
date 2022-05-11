//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Textures/PlaneChecker.h"

PlaneChecker::PlaneChecker(void)
    : Checker3D()
	, m_outlineColor(BLACK)
	, m_outlineWidth(1)
{}


PlaneChecker::PlaneChecker(const PlaneChecker& other)
    : Checker3D(other)
	, m_outlineColor(other.m_outlineColor)
	, m_outlineWidth(other.m_outlineWidth)
{}


PlaneChecker&
PlaneChecker::operator= (const PlaneChecker& rhs) 
{
    if( this == &rhs )
        return (*this);

    Checker3D::operator= (rhs);
	m_outlineColor = rhs.m_outlineColor;
	m_outlineWidth = rhs.m_outlineWidth;

    return (*this);
}


PlaneChecker*
PlaneChecker::Clone(void) const 
{
    return (new PlaneChecker(*this));
}


PlaneChecker::~PlaneChecker(void) 
{}


RGBColor
PlaneChecker::GetColor(const ShadeContext& sr) const 
{
	double x = sr.localHitPoint.x;
	double z = sr.localHitPoint.z;
	int ix = (int)floor(x / m_size);
	int iz = (int)floor(z / m_size);
	double fx = x / m_size - ix;
	double fz = z / m_size - iz;
	double width = 0.5 * m_outlineWidth / m_size; 
	bool in_outline = (fx <= width || fx >= 1.0 - width) || (fz <= width || fz >= 1.0 - width);
	
	if (!in_outline)
	{
		if ((ix + iz) % 2 == 0)
			return (m_color1);
		else 
			return (m_color2);
	}
	
	return (m_outlineColor);
}