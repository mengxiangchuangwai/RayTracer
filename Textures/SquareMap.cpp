//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Textures/SquareMap.h"

SquareMap::SquareMap(void) 
{}


SquareMap::SquareMap(const SquareMap& other) 
{}


SquareMap&
SquareMap::operator= (const SquareMap& rhs) 
{
	if( this == &rhs )
		return (*this);

	return (*this);
}


SquareMap::~SquareMap (void) 
{}


SquareMap*
SquareMap::Clone(void) const 
{
	return (new SquareMap(*this));
}


// Given a hit point on a generic sphere, and the image resolution, this function
// returns the texel coordinates in the image

void
SquareMap::GetTexelCoords(	const 	Point3D& 	localHitPoint,
							const 	int 		xres,
							const 	int 		yres,
									int& 		row,
									int& 		column ) const 
{
	float u = (localHitPoint.z + 1) / 2;
	float v = (localHitPoint.x + 1) / 2;

	// finally, map u and v to the texel coordinates

	column 	= (int) ((xres - 1) * u);   	// column is across
	row 	= (int) ((yres - 1) * v);    	// row is up
}