//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


// This is the declaration of the base class Tracer
// The tracer classes have no copy constructor, assignment operator. or clone function because
// of the world pointer, which should not be assigned or copy constructed
// See comments in the World.h file.

#ifndef __TRACER__
#define __TRACER__


#include "../Utilities/Constants.h"
#include "../Utilities/Ray.h"
#include "../Utilities/RGBColor.h"

class World;

class Tracer {
	public:

		Tracer(void);

		Tracer(World* wp);

		virtual
		~Tracer(void);

		virtual RGBColor
		TraceRay(const Ray& ray) const;

		virtual RGBColor
		TraceRay(const Ray& ray, const int depth) const;

		virtual RGBColor
		TraceRay(const Ray& ray, double& tmin, const int depth) const;


	protected:

		World* m_pWorld;
};


#endif
