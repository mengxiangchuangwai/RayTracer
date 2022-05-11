//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __RAY__
#define __RAY__


#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"

class Ray {
	public:
	
		Point3D			o;  	// origin 
		Vector3D		d; 		// direction 

	
	public:

		Ray(void);			
		
		Ray(const Point3D& origin, const Vector3D& dir);	
		
		Ray(const Ray& ray); 		
		
		Ray& operator= (const Ray& rhs);
		 								
		~Ray(void);
};


#endif
