//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __SQUARE_MAP__
#define __SQUARE_MAP__


#include "../Textures/Mapping.h"

class SquareMap: public Mapping {
	public:

		SquareMap(void);

		SquareMap(const SquareMap& other);

		SquareMap&
		operator= (const SquareMap& rhs);

		virtual SquareMap*
		Clone(void) const;

		virtual 
		~SquareMap(void);

		virtual void
		GetTexelCoords(	const 	Point3D& 	localHitPoint,
						const 	int 		xres,
						const 	int 		yres,
								int& 		row,
								int& 		column ) const;
};


#endif