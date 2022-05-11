//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __PATH_TRACE__
#define __PATH_TRACE__


#include "../Tracers/Tracer.h"

class PathTrace: public Tracer {
	public:
		
		PathTrace(void);
		
		PathTrace(World* wp);

		virtual 
		~PathTrace(void);
	
		virtual RGBColor	
		TraceRay(const Ray& ray, const int depth) const;
		
		virtual RGBColor	
		TraceRay(const Ray& ray, double& tmin, const int depth) const;
};


#endif
