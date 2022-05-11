//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Utilities/Maths.h"	// for SolveQuartic
#include "../Objects/Torus.h"

Torus::Torus (Material* mp)
    : GeometricObject(mp)
	, m_or(2.0)
	, m_ir(0.5)
{
	UpdateBoundingBox();
}


Torus::Torus (const double a, const double b, Material* mp)
	: GeometricObject(mp)
	, m_or(a)
	, m_ir(b)
{
	UpdateBoundingBox();
}


Torus*
Torus::Clone(void) const 
{
	return (new Torus(*this));
}


Torus::Torus (const Torus& other)
	: GeometricObject(other)
	, m_or(other.m_or)
	, m_ir(other.m_ir)
{}


Torus&
Torus::operator = (const Torus& rhs) 
{
	if( this == &rhs )
		return (*this);

	GeometricObject::operator= (rhs);
	m_or = rhs.m_or;
	m_ir = rhs.m_ir;

	return (*this);
}


Torus::~Torus(void) 
{}


// Find the normal vector at the specified position
// This works because the torus is defined by a single implicit equation

Normal
Torus::ComputeNormal(const Point3D& p) const 
{
	Normal normal;
	double a = m_or * m_or + m_ir * m_ir;

	double x = p.x;
	double y = p.y;
	double z = p.z;
	double b = x * x + y * y + z * z;

	normal.x = 4.0 * x * (b - a);
	normal.y = 4.0 * y * (b - a + 2.0 * m_or * m_or);
	normal.z = 4.0 * z * (b - a);
	normal.Normalize();

	return (normal);
}


bool Torus::Intersect(const Ray& ray, double& tval) const 
{	
	if( !m_bbox.Hit(ray) )
		return (false);

	double x1 = ray.o.x; double y1 = ray.o.y; double z1 = ray.o.z;
	double d1 = ray.d.x; double d2 = ray.d.y; double d3 = ray.d.z;

	double coeffs[5];	// coefficient array for the quartic equation
	double roots[4];	// solution array for the quartic equation

	// define the coefficients of the quartic equation

	double sdd 	= d1 * d1 + d2 * d2 + d3 * d3;
	double e	= x1 * x1 + y1 * y1 + z1 * z1 - m_or * m_or - m_ir * m_ir;
	double f	= x1 * d1 + y1 * d2 + z1 * d3;
	double foo	= 4.0 * m_or * m_or;

	coeffs[0] = e * e - foo * (m_ir * m_ir - y1 * y1); 	// constant term
	coeffs[1] = 4.0 * f * e + 2.0 * foo * y1 * d2;
	coeffs[2] = 2.0 * sdd * e + 4.0 * f * f + foo * d2 * d2;
	coeffs[3] = 4.0 * sdd * f;
	coeffs[4] = sdd * sdd;  // coefficient of t^4

	// find roots of the quartic equation

	int	num = SolveQuartic(coeffs, roots);
	double tv = kHugeValue;
	bool intersected = false;

	if( 0 == num )	// ray misses the torus
		return (false);

	// find the smallest root greater than kEpsilon, if any
	// the roots array is not sorted

	for( int i = 0; i < num; ++i )
		if( roots[i] > kEpsilon ) 
		{
			intersected = true;

			if( roots[i] < tv ) 
				tv = roots[i];
		}

	if( !intersected ) 
		return (false);

	tval = tv;
	return (true);
}