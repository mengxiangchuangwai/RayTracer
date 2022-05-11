//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Utilities/ShadeContext.h"

ShadeContext::ShadeContext(World* wp)
	: isHit(false)
	, pMaterial(NULL)
	, hitPoint()
	, localHitPoint()
	, normal()
	, ray()
	, depth(0)
	, color(BLACK)
	, tval(0.0)
	, tu(0.0)
	, tv(0.0)
	, pWorld(wp)
{}


ShadeContext::ShadeContext(const ShadeContext& rhs)
	: isHit(rhs.isHit)
	, pMaterial(rhs.pMaterial)
	, hitPoint(rhs.hitPoint)
	, localHitPoint(rhs.localHitPoint)
	, normal(rhs.normal)
	, ray(rhs.ray)
	, depth(rhs.depth)
	, color(rhs.color)
	, tval(rhs.tval)
	, tu(rhs.tu)
	, tv(rhs.tv)
	, pWorld(rhs.pWorld)
{}


ShadeContext* 
ShadeContext::Clone(void) const
{
	return (new ShadeContext(*this));
}

		
ShadeContext&
ShadeContext::operator= (const ShadeContext& rhs)
{
	if( this == &rhs )
		return (*this);

	isHit			= rhs.isHit;
	pMaterial		= rhs.pMaterial;
	hitPoint		= rhs.hitPoint;
	localHitPoint	= rhs.localHitPoint;
	normal			= rhs.normal;
	ray				= rhs.ray;
	depth			= rhs.depth;
	color			= rhs.color;
	tval			= rhs.tval;
	tu				= rhs.tu;
	tv				= rhs.tv;
	pWorld			= rhs.pWorld;

	return (*this);
}


ShadeContext::~ShadeContext(void) 
{}