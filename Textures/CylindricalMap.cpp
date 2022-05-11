//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Utilities/Constants.h"
#include "../Textures/CylindricalMap.h"

CylindricalMap::CylindricalMap(void) 
{}


CylindricalMap::CylindricalMap(const CylindricalMap& other) 
{}


CylindricalMap&
CylindricalMap::operator= (const CylindricalMap& rhs) 
{
	if( this == &rhs )
		return (*this);

	return (*this);
}


CylindricalMap::~CylindricalMap (void) 
{}


CylindricalMap*
CylindricalMap::Clone(void) const 
{
	return (new CylindricalMap(*this));
}


// Given a hit point on a generic sphere, and the image resolution, this function
// returns the texel coordinates in the image

void
CylindricalMap::GetTexelCoords(	const 	Point3D& 	localHitPoint,
								const 	int 		xres,
								const 	int 		yres,
										int& 		row,
										int& 		column ) const 
{
	double phi = atan2(localHitPoint.x, localHitPoint.z);
	
	if( phi < 0.0 ) 
		phi += TWO_PI;

	float u =  phi / TWO_PI;
	float v = (localHitPoint.y + 1) / 2;

	// finally, map u and v to the texel coordinates

	column 	= (int) ((xres - 1) * u);   	// column is across
	row 	= (int) ((yres - 1) * v);    	// row is up
}