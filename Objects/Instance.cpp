//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <cmath>
#include "../Utilities/Constants.h"
#include "../Objects/Instance.h"

Instance::Instance(Material* mp)
	: GeometricObject(mp)
	, m_pObject(NULL)
	, m_pLocalMaterial(NULL)
	, m_inverseMatrix()
	, m_forwardMatrix()
	, m_transformTexture(true)
{}


Instance::Instance(GeometricObject* pObject)
	: GeometricObject()
	, m_pObject(pObject)
	, m_pLocalMaterial(NULL)
	, m_inverseMatrix()
	, m_forwardMatrix()
	, m_transformTexture(true)
{}


Instance::Instance (const Instance& other)
	: GeometricObject(other)
	, m_pLocalMaterial(NULL)
	, m_inverseMatrix(other.m_inverseMatrix)
	, m_forwardMatrix(other.m_forwardMatrix)
	, m_transformTexture(other.m_transformTexture)
{
	if( other.m_pObject )
		m_pObject = other.m_pObject->Clone();
	else  m_pObject = NULL;
}


Instance*
Instance::Clone(void) const 
{
	return (new Instance(*this));
}


Instance::~Instance(void) 
{
	SAFE_DELETE(m_pObject);
}


Instance&
Instance::operator= (const Instance& rhs) 
{
	if( this == &rhs )
		return (*this);

	GeometricObject::operator= (rhs);

	SAFE_DELETE(m_pObject);

	if( rhs.m_pObject )
		m_pObject = rhs.m_pObject->Clone();

	m_pLocalMaterial	= NULL;
	m_inverseMatrix		= rhs.m_inverseMatrix;
	m_forwardMatrix		= rhs.m_forwardMatrix;
	m_transformTexture 	= rhs.m_transformTexture;

	return (*this);
}


void
Instance::SetObject(GeometricObject* pObject) 
{
	SAFE_DELETE(m_pObject);
	m_pObject = pObject;
}


void
Instance::UpdateBoundingBox(void) 
{

	// First get the object's untransformed BBox

	BBox obb;
	m_pObject->UpdateBoundingBox();
    m_pObject->GetBoundingBox(obb);


	// Now apply the affine transformations to the box.
	// We must apply the transformations to all 8 vertices of the orginal box
	// and then work out the new minimum and maximum values

	// Construct the eight vertices as 3D points:

	Point3D  pa[8];
	Point3D& p0 = obb.p0;
	Point3D& p1 = obb.p1;

	pa[0].x = pa[3].x = pa[4].x = pa[7].x = p0.x;
	pa[1].x = pa[2].x = pa[5].x = pa[6].x = p1.x;

	pa[0].y = pa[1].y = pa[4].y = pa[5].y = p0.y;
	pa[2].y = pa[3].y = pa[6].y = pa[7].y = p1.y;

	pa[0].z = pa[1].z = pa[2].z = pa[3].z = p0.z;
	pa[4].z = pa[5].z = pa[6].z = pa[7].z = p1.z;


	// Transform these using the forward matrix

	for( int i = 0; i < 8; ++i )
		pa[i] = m_forwardMatrix * pa[i];

	// Compute the minimum values

	double x0 = kHugeValue;
	double y0 = kHugeValue;
	double z0 = kHugeValue;

	for( int i = 0; i < 8; ++i )  
	{
		if( pa[i].x < x0 )
			x0 = pa[i].x;
	
		if( pa[i].y < y0 )
			y0 = pa[i].y;
	
		if( pa[i].z < z0 )
			z0 = pa[i].z;
	}

	// Compute the manimum values

	double x1 = -kHugeValue;
	double y1 = -kHugeValue;
	double z1 = -kHugeValue;

	for( int i = 0; i < 8; ++i ) 
	{
		if( pa[i].x > x1 )
			x1 = pa[i].x;

		if( pa[i].y > y1 )
			y1 = pa[i].y;
	
		if( pa[i].z > z1 )
			z1 = pa[i].z;
	}

	// Assign values to the bounding box

	m_bbox.p0.Set(x0, y0, z0);
	m_bbox.p1.Set(x1, y1, z1);
}


bool
Instance::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
	Ray invRay(ray);
	invRay.o = m_inverseMatrix * invRay.o;
	invRay.d = m_inverseMatrix * invRay.d;
	
	if( m_pObject->Hit(invRay, tmin, sr) ) 
	{
		sr.normal = m_inverseMatrix * sr.normal;
		sr.normal.Normalize();
		m_pLocalMaterial = (NULL == sr.pMaterial ? m_pObject->GetMaterial() : sr.pMaterial);

		if( !m_transformTexture )
			sr.localHitPoint = ray.o + tmin * ray.d;

		return (true);
	}

	return (false);
}


bool
Instance::ShadowHit(const Ray& ray, double& tmin) const 
{
	if( !m_shadowing )
		return false;

	Ray invRay(ray);
	invRay.o = m_inverseMatrix * invRay.o;
	invRay.d = m_inverseMatrix * invRay.d;
	return (m_pObject->ShadowHit(invRay, tmin));
}


void
Instance::Scale(const Vector3D& s) 
{
	Matrix temp;

	temp.m[0][0] = 1.0 / s.x;
	temp.m[1][1] = 1.0 / s.y;
	temp.m[2][2] = 1.0 / s.z;

	m_inverseMatrix = m_inverseMatrix * temp;

	temp.m[0][0] = s.x;
	temp.m[1][1] = s.y;
	temp.m[2][2] = s.z;

	m_forwardMatrix = temp * m_forwardMatrix;
}


void
Instance::Scale(const double a, const double b, const double c) 
{
	Matrix temp;

	temp.m[0][0] = 1.0 / a;
	temp.m[1][1] = 1.0 / b;
	temp.m[2][2] = 1.0 / c;

	m_inverseMatrix = m_inverseMatrix * temp;

	temp.m[0][0] = a;
	temp.m[1][1] = b;
	temp.m[2][2] = c;

	m_forwardMatrix = temp * m_forwardMatrix;
}


void
Instance::Translate(const Vector3D& t) 
{
	Matrix temp;

	temp.m[0][3] = -t.x;
	temp.m[1][3] = -t.y;
	temp.m[2][3] = -t.z;

	m_inverseMatrix = m_inverseMatrix * temp;

	temp.m[0][3] = t.x;
	temp.m[1][3] = t.y;
	temp.m[2][3] = t.z;

	m_forwardMatrix = temp * m_forwardMatrix;
}


void
Instance::Translate(const double dx, const double dy, const double dz) 
{
	Matrix temp;

	temp.m[0][3] = -dx;
	temp.m[1][3] = -dy;
	temp.m[2][3] = -dz;

	m_inverseMatrix = m_inverseMatrix * temp;

	temp.m[0][3] = dx;
	temp.m[1][3] = dy;
	temp.m[2][3] = dz;

	m_forwardMatrix = temp * m_forwardMatrix;
}


void
Instance::RotateX(const double theta) 
{
	double sinTheta = sin(theta * PI_ON_180);
	double cosTheta = cos(theta * PI_ON_180);

	Matrix temp;

	temp.m[1][1] = cosTheta;
	temp.m[1][2] = sinTheta;
	temp.m[2][1] = -sinTheta;
	temp.m[2][2] = cosTheta;

	m_inverseMatrix = m_inverseMatrix * temp;

	temp.m[1][1] = cosTheta;
	temp.m[1][2] = -sinTheta;
	temp.m[2][1] = sinTheta;
	temp.m[2][2] = cosTheta;

	m_forwardMatrix = temp * m_forwardMatrix;
}


void
Instance::RotateY(const double theta) 
{

	double sinTheta = sin(theta * PI_ON_180);
	double cosTheta = cos(theta * PI_ON_180);

	Matrix temp;

	temp.m[0][0] = cosTheta;
	temp.m[0][2] = -sinTheta;
	temp.m[2][0] = sinTheta;
	temp.m[2][2] = cosTheta;

	m_inverseMatrix = m_inverseMatrix * temp;

	temp.m[0][0] = cosTheta;
	temp.m[0][2] = sinTheta;
	temp.m[2][0] = -sinTheta;
	temp.m[2][2] = cosTheta;

	m_forwardMatrix = temp * m_forwardMatrix;
}


void
Instance::RotateZ(const double theta) 
{
	double sinTheta = sin(theta * PI_ON_180);
	double cosTheta = cos(theta * PI_ON_180);

	Matrix temp;

	temp.m[0][0] = cosTheta;
	temp.m[0][1] = sinTheta;
	temp.m[1][0] = -sinTheta;
	temp.m[1][1] = cosTheta;

	m_inverseMatrix = m_inverseMatrix * temp;

	temp.m[0][0] = cosTheta;
	temp.m[0][1] = -sinTheta;
	temp.m[1][0] = sinTheta;
	temp.m[1][1] = cosTheta;

	m_forwardMatrix = temp * m_forwardMatrix;
}


void
Instance::Shear(const Matrix& s) 
{
	Matrix temp;

	// discriminant

	double d = 1.0 	- s.m[1][0] * s.m[0][1] - s.m[2][0] * s.m[0][2]  - s.m[2][1] * s.m[1][2]
					+ s.m[1][0] * s.m[2][1] * s.m[0][2] + s.m[2][0] * s.m[0][1] * s.m[2][1];

	// diagonals

	temp.m[0][0] = 1.0 - s.m[2][1] * s.m[1][2];
	temp.m[1][1] = 1.0 - s.m[2][0] * s.m[0][2];
	temp.m[2][2] = 1.0 - s.m[1][0] * s.m[0][1];
	temp.m[3][3] = d;

	// first row

	temp.m[0][1] = -s.m[1][0] + s.m[2][0] * s.m[1][2];
	temp.m[0][2] = -s.m[2][0] + s.m[1][0] * s.m[2][1];

	// second row

	temp.m[1][0] = -s.m[0][1] + s.m[2][1] * s.m[0][2];
	temp.m[1][2] = -s.m[2][1] + s.m[2][0] * s.m[0][1];

	// third row

	temp.m[2][0] = -s.m[0][2] + s.m[0][1] * s.m[1][2];
	temp.m[2][1] = -s.m[1][2] + s.m[1][0] * s.m[0][2] ;

	// divide by discriminant

	temp = temp / d;
	m_inverseMatrix = m_inverseMatrix * temp;

	m_forwardMatrix = s * m_forwardMatrix;
}