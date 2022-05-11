//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/Rectangle.h"
#include "../Samplers/Sampler.h"

RectangleX::RectangleX(Material* mp)
	: GeometricObject(mp)
	, m_p0(-1, 0, -1)
	, m_a(0, 0, 2) 
	, m_b(2, 0, 0)
	, m_alenSq(4.0)
	, m_blenSq(4.0)
	, m_normal(0, 1, 0)
	, m_area(4.0)
	, m_invArea(0.25)
	, m_pSampler(NULL)
{}


RectangleX::RectangleX(const Point3D& p0, const Vector3D& a, const Vector3D& b, Material* mp)
	: GeometricObject(mp)
	, m_p0(p0)
	, m_a(a)
	, m_b(b)
	, m_alenSq(m_a.LengthSq())
	, m_blenSq(m_b.LengthSq())
	, m_area(m_a.Length() * m_b.Length())
	, m_invArea(1.0 / m_area)
	, m_pSampler(NULL)
{
	m_normal = m_a ^ m_b;
	m_normal.Normalize();
}


RectangleX::RectangleX(const Point3D& p0, const Vector3D& a, const Vector3D& b, const Normal& normal, Material* mp)
	: GeometricObject(mp)
	, m_p0(p0)
	, m_a(a)
	, m_b(b)
	, m_alenSq(m_a.LengthSq())
	, m_blenSq(m_b.LengthSq())
	, m_area(m_a.Length() * m_b.Length())
	, m_invArea(1.0 / m_area)
	, m_normal(normal)
	, m_pSampler(NULL)
{
	m_normal.Normalize();
}


RectangleX*
RectangleX::Clone(void) const 
{
	return (new RectangleX(*this));
}


RectangleX::RectangleX(const RectangleX& other)
	:	GeometricObject(other)
	,	m_p0(other.m_p0)
	,	m_a(other.m_a)
	,	m_b(other.m_b)
	,	m_alenSq(other.m_alenSq)
	,	m_blenSq(other.m_blenSq)
	,	m_normal(other.m_normal)
	,	m_area(other.m_area)
	,	m_invArea(other.m_invArea)
{
	if( other.m_pSampler )
		m_pSampler	= other.m_pSampler->Clone();
	else  m_pSampler = NULL;
}


RectangleX&
RectangleX::operator=(const RectangleX& rhs) 
{
	if( this == &rhs )
		return (*this);

	GeometricObject::operator= (rhs);

	m_p0		= rhs.m_p0;
	m_a			= rhs.m_a;
	m_b			= rhs.m_b;
	m_alenSq	= rhs.m_alenSq;
	m_blenSq	= rhs.m_blenSq;
	m_area		= rhs.m_area;
	m_invArea	= rhs.m_invArea;
	m_normal	= rhs.m_normal;

	SAFE_DELETE(m_pSampler);

	if( rhs.m_pSampler )
		m_pSampler= rhs.m_pSampler->Clone();

	return (*this);
}


RectangleX::~RectangleX (void) 
{
	SAFE_DELETE(m_pSampler);
}


void RectangleX::UpdateBoundingBox(void) 
{
 	double delta = 0.0001;
    m_bbox.p0 = Point3D(min2(m_p0.x, m_p0.x + m_a.x + m_b.x) - delta,
						min2(m_p0.y, m_p0.y + m_a.y + m_b.y) - delta,
						min2(m_p0.z, m_p0.z + m_a.z + m_b.z) - delta);
    m_bbox.p1 = Point3D(max2(m_p0.x, m_p0.x + m_a.x + m_b.x) + delta,
						max2(m_p0.y, m_p0.y + m_a.y + m_b.y) + delta,
						max2(m_p0.z, m_p0.z + m_a.z + m_b.z) + delta);
}


bool
RectangleX::Intersect(const Ray& ray, double& tmin, ShadeContext* pContext) const
{
	double tval  = (m_p0 - ray.o) * m_normal / (ray.d * m_normal);
    double delta = 0.001;

	if( tval <= delta )
		return (false);

	Point3D p = ray.o + tval * ray.d;
	Vector3D d = p - m_p0;

	double ddota = d * m_a;

	if( ddota < 0.0 || ddota > m_alenSq )
		return (false);

	double ddotb = d * m_b;

	if( ddotb < 0.0 || ddotb > m_blenSq )
		return (false);

	tmin = tval;

	if( pContext )
	{
		pContext->normal = m_normal;
		pContext->localHitPoint = p;
	}

	return (true);
}


void
RectangleX::SetSampler(Sampler* sampler) 
{
	SAFE_DELETE(m_pSampler);
	m_pSampler = sampler;
}


Point3D
RectangleX::Sample(void) 
{
	Point2D sp = m_pSampler->SampleUnitSquare();
	return (m_p0 + sp.x * m_a + sp.y * m_b);
}