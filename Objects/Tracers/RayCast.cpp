//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Tracers/RayCast.h"
#include "../World/World.h"
#include "../Utilities/ShadeContext.h"
#include "../Materials/Material.h"

RayCast::RayCast(void)
	: Tracer()
{}


RayCast::RayCast(World* wp)
	: Tracer(wp)
{}


RayCast::~RayCast(void) 
{}


RGBColor
RayCast::TraceRay(const Ray& ray) const 
{
	ShadeContext sr(m_pWorld->TestObjects(ray));

	if( sr.isHit ) 
	{
		sr.ray = ray;			// used for specular shading
		return (sr.pMaterial->Shade(sr));
	}
	else
		return (m_pWorld->GetBackgroundColor());
}


RGBColor
RayCast::TraceRay(const Ray& ray, const int depth) const 
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
			return (sr.pMaterial->Shade(sr));
		}
		else
			return (m_pWorld->GetBackgroundColor());
	}
}


RGBColor	
RayCast::TraceRay(const Ray& ray, double& tmin, const int depth) const 
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
			return (sr.pMaterial->Shade(sr));   
		}
		else 
		{
			tmin = kHugeValue;
			return (m_pWorld->GetBackgroundColor());
		}
	}																																			
}