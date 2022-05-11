//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Tracers/Tracer.h"

Tracer::Tracer(void)
	: m_pWorld(NULL)
{}


Tracer::Tracer(World* wp)
	: m_pWorld(wp)
{}


Tracer::~Tracer(void) 
{
	if( m_pWorld )
		m_pWorld = NULL;
}


RGBColor
Tracer::TraceRay(const Ray& ray) const 
{
	return (BLACK);
}


RGBColor
Tracer::TraceRay(const Ray& ray, const int depth) const 
{
	return (BLACK);
}


RGBColor
Tracer::TraceRay(const Ray& ray, double& tmin, const int depth) const 
{
	return (BLACK);
}