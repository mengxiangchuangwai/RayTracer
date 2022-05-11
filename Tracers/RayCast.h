//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __RAY_CAST__
#define __RAY_CAST__


#include "../Tracers/Tracer.h"

class RayCast: public Tracer {
	public:

		RayCast(void);

		RayCast(World* wp);

		virtual 
		~RayCast(void);

		virtual RGBColor
		TraceRay(const Ray& ray) const;

		virtual RGBColor
		TraceRay(const Ray& ray, const int depth) const;

		virtual RGBColor	
		TraceRay(const Ray& ray, double& tmin, const int depth) const;
};


#endif
