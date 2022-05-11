//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Utilities/Maths.h"
#include "../Textures/SphereChecker.h"

SphereChecker::SphereChecker(void)
	: Texture()
	, m_horizCheckers(20)
	, m_vertCheckers(10)
	, m_horizLineWidth(0.0)
	, m_vertLineWidth(0.0)
	, m_color1(WHITE)
	, m_color2(0.5)
	, m_lineColor(BLACK)
{}


SphereChecker::SphereChecker(const SphereChecker& other)
	: Texture(other)
	, m_horizCheckers(other.m_horizCheckers)
	, m_vertCheckers(other.m_vertCheckers)
	, m_horizLineWidth(other.m_horizLineWidth)
	, m_vertLineWidth(other.m_vertLineWidth)
	, m_color1(other.m_color1)
	, m_color2(other.m_color2)
	, m_lineColor(other.m_lineColor)
{}


SphereChecker& 
SphereChecker::operator= (const SphereChecker& rhs) 	
{
	if( this == &rhs )
		return (*this);
	
	Texture::operator= (rhs);
	
	m_horizCheckers		= rhs.m_horizCheckers;
	m_vertCheckers 		= rhs.m_vertCheckers;
	m_horizLineWidth 	= rhs.m_horizLineWidth;
	m_vertLineWidth 	= rhs.m_vertLineWidth;
	m_color1			= rhs.m_color1;
	m_color2 			= rhs.m_color2;
	m_lineColor 		= rhs.m_lineColor;

	return (*this);
}


SphereChecker*										
SphereChecker::Clone(void) const 
{
	return (new SphereChecker(*this));
}	


SphereChecker::~SphereChecker(void) 
{}


RGBColor																				
SphereChecker::GetColor(const ShadeContext& sr) const 
{
	double x = sr.localHitPoint.x;
	double y = sr.localHitPoint.y;
	double z = sr.localHitPoint.z;
		
	double theta = acos(y);
	double phi   = atan2(x, z);
	if( phi < 0.0 )
		phi += 2.0 * PI;
	
	double phiSize = 2 * PI / m_horizCheckers;   	// in radians - azimuth angle
	double thetaSize =   PI / m_vertCheckers;   	// in radians - polar angle
	
	int iphi = floor(phi / phiSize);
	int itheta = floor(theta / thetaSize);
	
	double fphi = phi / phiSize - iphi;
	double ftheta = theta / thetaSize - itheta;
	
	double phiLineWidth = 0.5 * m_vertLineWidth;
	double thetaLineWidth = 0.5 * m_horizLineWidth;
	
	bool inOutline = (fphi <= phiLineWidth || fphi >= 1.0 - phiLineWidth) || 
						(ftheta <= thetaLineWidth || ftheta >= 1.0 - thetaLineWidth);	

	if( !inOutline ) 
	{
		if( (iphi + itheta) % 2 == 0 )
			return (m_color1);
		else
			return (m_color2);
	}
	
	return (m_lineColor);
}