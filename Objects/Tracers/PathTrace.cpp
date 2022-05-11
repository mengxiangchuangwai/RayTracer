//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Tracers/PathTrace.h"
#include "../Materials/Material.h"
#include "../Utilities/ShadeContext.h"
#include "../World/World.h"

PathTrace::PathTrace(void)
	: Tracer()
{}


PathTrace::PathTrace(World* wp)
	: Tracer(wp)
{}


PathTrace::~PathTrace(void) 
{}


RGBColor	
PathTrace::TraceRay(const Ray& ray, const int depth) const 
{
	if( depth > m_pWorld->GetViewPlane().GetMaxDepth() )
		return (BLACK);
	else 
	{
		ShadeContext sr(m_pWorld->TestObjects(ray));  
					
		if( sr.isHit ) 
		{
			sr.depth	= depth;
			sr.ray		= ray;
			
			return (sr.pMaterial->PathShade(sr));   
		}
		else
			return (m_pWorld->GetBackgroundColor());
	}	
}


RGBColor	
PathTrace::TraceRay(const Ray& ray, double& tmin, const int depth) const 
{
	if( depth > m_pWorld->GetViewPlane().GetMaxDepth() )
		return (BLACK);
	else 
	{
		ShadeContext sr(m_pWorld->TestObjects(ray));  
					
		if( sr.isHit ) 
		{
			sr.depth 	= depth;
			sr.ray 		= ray;
			tmin		= sr.tval;     // required for colored transparency
			return (sr.pMaterial->PathShade(sr));   
		}
		else 
		{
			tmin = kHugeValue;
			return (m_pWorld->GetBackgroundColor());
		}
	}	
}