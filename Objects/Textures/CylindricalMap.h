//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __CYLINDRICAL_MAP__
#define __CYLINDRICAL_MAP__


#include "../Textures/Mapping.h"

class CylindricalMap: public Mapping {
	public:

		CylindricalMap(void);

		CylindricalMap(const CylindricalMap& other);

		CylindricalMap&
		operator= (const CylindricalMap& rhs);

		virtual CylindricalMap*
		Clone(void) const;

		virtual 
		~CylindricalMap(void);

		virtual void
		GetTexelCoords(	const 	Point3D& 	localHitPoint,
						const 	int 		xres,
						const 	int 		yres,
								int& 		row,
								int& 		column ) const;
};


#endif