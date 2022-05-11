//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __SHADE_CONTEXT__
#define __SHADE_CONTEXT__


class Material;
class World;

#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"

class ShadeContext {
	public:

		bool			isHit;			// did the ray hit an object?
		Material* 		pMaterial;		// temperary pointer to the nearest object's material
		Point3D 		hitPoint;		// world coordinates of intersection
		Point3D			localHitPoint;	// world coordinates of hit point on untransformed object (used for texture transformations)
		Normal			normal;			// normal at hit point
		Ray				ray;			// required for specular highlights and area lights
		int				depth;			// recursion depth
		RGBColor		color;			// used in the Chapter 3 only
		double			tval;			// ray parameter
		float			tu;				// texture coordinate
		float			tv;				// texture coordinate
		World*			pWorld;			// pointer of the world


	public:

        ShadeContext(World* wp = NULL);			// default constructor
		
		ShadeContext(const ShadeContext& rhs);	// copy constructor

		virtual ShadeContext* 					// virtual copy constructor
		Clone(void) const;

		ShadeContext& 							// assignment operator
		operator= (const ShadeContext& rhs);
		
		virtual 
		~ShadeContext(void);					// destructor
};


#endif
