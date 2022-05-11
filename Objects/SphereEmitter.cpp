//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <cmath>

#include "../Objects/SphereEmitter.h"
#include "../Utilities/Constants.h"

SphereEmitter::SphereEmitter(Material* mp)
	: Sphere(mp)
	, m_pSampler(NULL)
	, m_invArea(1.0 / (4 * PI))
{}


SphereEmitter::SphereEmitter(const Point3D& center, const double radius, Material* mp)
	: Sphere(center, radius, mp)
	, m_pSampler(NULL)
	, m_invArea(1.0 / (4 * PI * m_radius * m_radius))
{}


SphereEmitter*
SphereEmitter::Clone(void) const 
{
	return (new SphereEmitter(*this));
}


SphereEmitter::SphereEmitter (const SphereEmitter& other)
	: Sphere(other)
{
	m_invArea = other.m_invArea;

	if( other.m_pSampler )
		m_pSampler	= other.m_pSampler->Clone();
	else  m_pSampler = NULL;
}


SphereEmitter&
SphereEmitter::operator= (const SphereEmitter& rhs)
{
	if( this == &rhs )
		return (*this);

	Sphere::operator= (rhs);
	m_invArea = rhs.m_invArea;

	SAFE_DELETE(m_pSampler);

	if( rhs.m_pSampler )
		m_pSampler= rhs.m_pSampler->Clone();

	return (*this);
}


SphereEmitter::~SphereEmitter(void) 
{
	SAFE_DELETE(m_pSampler);
}


void
SphereEmitter::SetSampler(Sampler* sampler) 
{
	SAFE_DELETE(m_pSampler);

	if( m_pSampler = sampler )
		m_pSampler->SamplesToSphere();
}