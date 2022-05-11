// 	Copyright (C) Kevin Suffern 2000-2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include "../Tracers/GlobalTrace.h"
#include "../Materials/Material.h"
#include "../Utilities/ShadeRec.h"
#include "../World/World.h"

GlobalTrace::GlobalTrace(void)
	: Tracer()
{}


GlobalTrace::GlobalTrace(World* wp)
	: Tracer(wp)
{}


GlobalTrace::~GlobalTrace(void) {}


RGBColor	
GlobalTrace::trace_ray(const Ray& ray, const int depth) const {
	if (depth > world_ptr->vp.max_depth)
		return (RGBColor::black);
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));  
					
		if (sr.hit_an_object) {
			sr.depth = depth;
			sr.ray = ray;
			
			return (sr.material_ptr->global_shade(sr));   
		}
		else
			return (world_ptr->background_color);
	}	
}


RGBColor	
GlobalTrace::trace_ray(const Ray& ray, double& tmin, const int depth) const {
	if (depth > world_ptr->vp.max_depth)
		return (RGBColor::black);
	else {
		ShadeRec sr(world_ptr->hit_objects(ray));  
					
		if (sr.hit_an_object) {
			sr.depth 	= depth;
			sr.ray 		= ray;
			tmin		= sr.t;     // required for colored transparency
			return (sr.material_ptr->global_shade(sr));   
		}
		else {
			tmin = kHugeValue;
			return (world_ptr->background_color);
		}
	}	
}