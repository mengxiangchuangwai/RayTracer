//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/Triangle.h"
#include "../Utilities/Maths.h"

Triangle::Triangle(Material* mp)
    : GeometricObject(mp)
    , m_v0(0)
    , m_v1(0)
    , m_v2(0)
    , m_normal(0)
{}


Triangle::Triangle(const Point3D& a, const Point3D& b, const Point3D& c, Material* mp)
    : GeometricObject(mp)
    , m_v0(a)
    , m_v1(b)
    , m_v2(c)
{
    m_normal = (m_v1 - m_v0) ^ (m_v2 - m_v0);
    m_normal.Normalize();
}


Triangle::Triangle(const Triangle& other)
    : GeometricObject(other)
    , m_v0(other.m_v0)
    , m_v1(other.m_v1)
    , m_v2(other.m_v2)
    , m_normal(other.m_normal)
{}


Triangle& Triangle::operator=(const Triangle& rhs) 
{
    if( this == &rhs )
        return (*this);

    GeometricObject::operator= (rhs);
    m_v0 = rhs.m_v0;
    m_v1 = rhs.m_v1;
    m_v2 = rhs.m_v2;
    m_normal = rhs.m_normal;
    return (*this);
}


Triangle* Triangle::Clone(void) const 
{
    return (new Triangle(*this));
}


bool Triangle::Intersect(const Ray& ray, double& tval) const 
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
	double tv = e3 * invDenom;

	if( tv < kEpsilon )
		return (false);

	tval = tv;
	return (true);
}


void Triangle::UpdateBoundingBox(void) 
{
    double delta = 0.0001;
    m_bbox.p0 = Point3D(min2(min2(m_v0.x, m_v1.x), m_v2.x) - delta,
						min2(min2(m_v0.y, m_v1.y), m_v2.y) - delta,
						min2(min2(m_v0.z, m_v1.z), m_v2.z) - delta);

    m_bbox.p1 = Point3D(max2(max2(m_v0.x, m_v1.x), m_v2.x) + delta,
						max2(max2(m_v0.y, m_v1.y), m_v2.y) + delta,
						max2(max2(m_v0.z, m_v1.z), m_v2.z) + delta);
}