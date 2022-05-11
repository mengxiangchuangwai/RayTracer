//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Utilities/Constants.h"
#include "../Utilities/Maths.h"
#include "../Objects/SmoothTriangle.h"

SmoothTriangle::SmoothTriangle(Material* mp)
	: GeometricObject(mp)
	, m_v0(0.0)
	, m_v1(0,0,1)
	, m_v2(1,0,0)
	, m_n0(0, 1, 0)
	, m_n1(0, 1, 0)
	, m_n2(0, 1, 0)
{}


SmoothTriangle::SmoothTriangle(const Point3D& a, const Point3D& b, const Point3D& c, Material* mp)
	: GeometricObject(mp)
	, m_v0(a)
	, m_v1(b)
	, m_v2(c)
	, m_n0(0, 1, 0)
	, m_n1(0, 1, 0)
	, m_n2(0, 1, 0)
{}


SmoothTriangle*
SmoothTriangle::Clone(void) const 
{
	return (new SmoothTriangle (*this));
}


SmoothTriangle::SmoothTriangle(const SmoothTriangle& other)
	: GeometricObject(other)
	, m_v0(other.m_v1)
	, m_v1(other.m_v1)
	, m_v2(other.m_v2)
	, m_n0(other.m_n0)
	, m_n1(other.m_n1)
	, m_n2(other.m_n2)
{}


SmoothTriangle&
SmoothTriangle::operator= (const SmoothTriangle& rhs) 
{
	if( this == &rhs )
		return (*this);

	m_v0 = rhs.m_v0;
	m_v1 = rhs.m_v1;
	m_v2 = rhs.m_v2;
	m_n0 = rhs.m_n0;
	m_n1 = rhs.m_n1;
	m_n2 = rhs.m_n2;

	return (*this);
}


SmoothTriangle::~SmoothTriangle(void) 
{}


Normal
SmoothTriangle::InterpolateNormal(const float beta, const float gamma) const 
{
	Normal norm((1 - beta - gamma) * m_n0 + beta * m_n1 + gamma * m_n2);
	norm.Normalize();
	return(norm);
}


void
SmoothTriangle::UpdateBoundingBox(void) 
{
    double delta = 0.0001;
    m_bbox.p0 = Point3D(min2(min2(m_v0.x, m_v1.x), m_v2.x) - delta,
						min2(min2(m_v0.y, m_v1.y), m_v2.y) - delta,
						min2(min2(m_v0.z, m_v1.z), m_v2.z) - delta);

    m_bbox.p1 = Point3D(max2(max2(m_v0.x, m_v1.x), m_v2.x) + delta,
						max2(max2(m_v0.y, m_v1.y), m_v2.y) + delta,
						max2(max2(m_v0.z, m_v1.z), m_v2.z) + delta);
}


bool 
SmoothTriangle::Intersect(const Ray& ray, double& _tval, double& _beta, double& _gamma) const 
{
	double a = m_v0.x - m_v1.x, b = m_v0.x - m_v2.x, c = ray.d.x, d = m_v0.x - ray.o.x;
	double e = m_v0.y - m_v1.y, f = m_v0.y - m_v2.y, g = ray.d.y, h = m_v0.y - ray.o.y;
	double i = m_v0.z - m_v1.z, j = m_v0.z - m_v2.z, k = ray.d.z, l = m_v0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k, s = e * j - f * i;

	double invDenom  = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * invDenom;

	if( beta < 0.0 )
	 	return (false);

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * invDenom;

	if( gamma < 0.0 )
	 	return (false);

	if( beta + gamma > 1.0 )
		return (false);

	double e3 = a * p - b * r + d * s;
	double t = e3 * invDenom;

	if( t < kEpsilon )
		return (false);

	_tval	= t;
	_beta	= beta;
	_gamma	= gamma;
	return (true);
}