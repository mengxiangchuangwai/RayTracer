//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Textures/SphericalMap.h"

SphericalMap::SphericalMap(void) 
{}


SphericalMap::SphericalMap(const SphericalMap& other) 
{}


SphericalMap&
SphericalMap::operator= (const SphericalMap& rhs) 
{
	if( this == &rhs )
		return (*this);

	return (*this);
}


SphericalMap::~SphericalMap (void) 
{}


SphericalMap*
SphericalMap::Clone(void) const 
{
	return (new SphericalMap(*this));
}


// Given a hit point on a generic sphere, and the image resolution, this function
// returns the texel coordinates in the image

void
SphericalMap::GetTexelCoords(	const 	Point3D& 	localHitPoint,
								const 	int 		xres,
								const 	int 		yres,
										int& 		row,
										int& 		column ) const 
{

	// first, compute theta and phi

	float theta = acos(localHitPoint.y);
	float phi   = atan2(localHitPoint.x, localHitPoint.z);
	if (phi < 0.0)
		phi += TWO_PI;

	// next, map theta and phi to (u, v) in [0, 1] X [0, 1]

	float u = phi * invTWO_PI;
	float v = 1.0 - theta * invPI;

	// finally, map u and v to the texel coordinates

	column 	= (int) ((xres - 1) * u);   	// column is across
	row 	= (int) ((yres - 1) * v);    	// row is up
}