//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Textures/LightProbe.h"

LightProbe::LightProbe(void)
	: m_mapType(LP_Default) 
{}


LightProbe::LightProbe(const LightProbe& other)
	: m_mapType(other.m_mapType) 
{}


LightProbe&
LightProbe::operator= (const LightProbe& rhs) 
{
	if( this == &rhs )
		return (*this);

	m_mapType = rhs.m_mapType;
	return (*this);
}


LightProbe::~LightProbe (void) 
{}


LightProbe*
LightProbe::Clone(void) const 
{
	return (new LightProbe(*this));
}


void
LightProbe::GetTexelCoords(	const 	Point3D& 	localHitPoint, 
							const 	int 		hres, 
							const 	int 		vres, 
							int& 	row, 
							int& 	column ) const 
{
								
	float x = localHitPoint.x; 
	float y = localHitPoint.y; 
	float z = localHitPoint.z;
	
	float d = sqrt(x * x + y * y);
	float sinBeta = y / d;
	float cosBeta = x / d;       
	float alpha;
	
	if( m_mapType == LP_Panoramic )
		alpha = acos(-z);
	else
		alpha = acos(z);
	
	float r = alpha * invPI;     		
	float u = (1.0 + r * cosBeta) * 0.5;
	float v = (1.0 + r * sinBeta) * 0.5;	
	column 	= (int) ((hres - 1) * u);	
	row 	= (int) ((vres - 1) * v);	
}