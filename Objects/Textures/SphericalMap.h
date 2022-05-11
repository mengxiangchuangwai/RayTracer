//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __SPHERICAL_MAP__
#define __SPHERICAL_MAP__


// This file contains the definition of the class SphericalMap
// This class inherits from Mapping, and defines a default spherical mapping
// Here, an image with an aspect ratio of 2:1 is mapped onto a sphere so
// that it just covers the whole sphere

#include "../Utilities/Constants.h"
#include "../Textures/Mapping.h"

class SphericalMap: public Mapping {
	public:

		SphericalMap(void);

		SphericalMap(const SphericalMap& other);

		SphericalMap&
		operator= (const SphericalMap& rhs);

		virtual SphericalMap*
		Clone(void) const;

		virtual 
		~SphericalMap(void);

		virtual void
		GetTexelCoords(	const 	Point3D& 	localHitPoint,
						const 	int 		xres,
						const 	int 		yres,
								int& 		row,
								int& 		column ) const;
};


#endif