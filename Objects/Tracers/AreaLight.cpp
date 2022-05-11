//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Tracers/AreaLight.h"
#include "../Utilities/ShadeContext.h"
#include "../Materials/Material.h"
#include "../World/World.h"

AreaLight::AreaLight(void)
	: Tracer()
{}


AreaLight::AreaLight(World* wp)
	: Tracer(wp)
{}


AreaLight::~AreaLight(void) 
{}


RGBColor AreaLight::TraceRay(const Ray& ray) const
{
    ShadeContext sr(m_pWorld->TestObjects(ray));

    if( sr.isHit )
	{
        sr.ray = ray;
        return (sr.pMaterial->AreaLightShade(sr));
    }
    else
        return (m_pWorld->GetBackgroundColor());
}


// The statement sr.ray = ray; is required for specular shading, computing the reflected and
// transmitted ray directions, and for rendering single sided emissive materials with area lights

RGBColor
AreaLight::TraceRay(const Ray& ray, const int depth) const 
{
	if( depth > m_pWorld->GetViewPlane().GetMaxDepth() )
		return (BLACK);
	else {
		ShadeContext sr(m_pWorld->TestObjects(ray));

		if( sr.isHit ) 
		{
			sr.depth	= depth;
			sr.ray		= ray;

			return (sr.pMaterial->AreaLightShade(sr));
		}
		else
			return (m_pWorld->GetBackgroundColor());
	}
}


RGBColor	
AreaLight::TraceRay(const Ray& ray, double& tmin, const int depth) const 
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
			
			return (sr.pMaterial->AreaLightShade(sr));   
		}
		else 
		{
			tmin = kHugeValue;
			return (m_pWorld->GetBackgroundColor());
		}
	}																																			
}