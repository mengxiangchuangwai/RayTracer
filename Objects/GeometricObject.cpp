//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Utilities/Constants.h"
#include "../Materials/Material.h"
#include "../Objects/GeometricObject.h"

static const Normal g_normal;

GeometricObject::GeometricObject (Material* mp)
	: m_pMaterial(mp)
	, m_shadowing(true)
	, m_reverseNormal(false)
{}


GeometricObject::GeometricObject (const GeometricObject& other) 
	: m_color(other.m_color)
	, m_bbox(other.m_bbox)
	, m_shadowing(other.m_shadowing)
	, m_reverseNormal(other.m_reverseNormal)
{
	if( other.m_pMaterial )
		m_pMaterial = other.m_pMaterial->Clone();
	else
		m_pMaterial = NULL;
}


GeometricObject&
GeometricObject::operator= (const GeometricObject& rhs) 
{
	if( this == &rhs )
		return (*this);

	SAFE_DELETE(m_pMaterial);

	if( rhs.m_pMaterial )
		m_pMaterial = rhs.m_pMaterial->Clone();
   
    m_color			= rhs.m_color;
	m_bbox			= rhs.m_bbox;
	m_shadowing		= rhs.m_shadowing;
	m_reverseNormal	= rhs.m_reverseNormal;
	return (*this);
}


GeometricObject::~GeometricObject (void) 
{
	SAFE_DELETE(m_pMaterial);
}


bool
GeometricObject::ShadowHit(const Ray &ray, double &tmin) const 
{
    return (false);
}


void
GeometricObject::SetMaterial(Material* mp) 
{
    SAFE_DELETE(m_pMaterial);
	m_pMaterial = mp;
}


void
GeometricObject::SetSampler(Sampler* sp) 
{}


Normal
GeometricObject::GetNormal(const Point3D& p) const 
{
	return g_normal;
}


const Normal&
GeometricObject::GetNormal(void) const 
{
    return g_normal;
}