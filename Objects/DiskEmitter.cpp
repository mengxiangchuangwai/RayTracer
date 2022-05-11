//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/DiskEmitter.h"

DiskEmitter::DiskEmitter(Material* mp)
    : Disk(mp)
    , m_pSampler(NULL)
	, m_u(1.0, 0.0, 0.0)
	, m_v(0.0, 1.0, 0.0)
	, m_w(0.0, 0.0, 1.0)
{}


DiskEmitter::DiskEmitter(const Point3D& center, const Normal& normal, const double radius, Material* mp)
    : Disk(center, normal, radius, mp)
    , m_pSampler(NULL)
{
	SetNormal(normal);
}


DiskEmitter::DiskEmitter(const DiskEmitter& other)
    : Disk(other) 
{
	m_u = other.m_u;
	m_v = other.m_v;
	m_w = other.m_w;

    if( other.m_pSampler )
		m_pSampler = other.m_pSampler->Clone();
	else  m_pSampler = NULL;
}


DiskEmitter& 
DiskEmitter::operator=(const DiskEmitter& rhs) 
{
    if( this == &rhs )
        return(*this);

    Disk::operator= (rhs);
    m_u = rhs.m_u;
	m_v = rhs.m_v;
	m_w = rhs.m_w;
	SAFE_DELETE(m_pSampler);

	if( rhs.m_pSampler )
		m_pSampler = rhs.m_pSampler->Clone();

    return(*this);
}


DiskEmitter* 
DiskEmitter::Clone(void) const 
{
    return (new DiskEmitter(*this));
}


DiskEmitter::~DiskEmitter(void) 
{
	SAFE_DELETE(m_pSampler);
}