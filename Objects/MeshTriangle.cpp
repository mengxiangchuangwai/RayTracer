//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/MeshTriangle.h"
#include "../Objects/Mesh.h"
#include "../Utilities/Maths.h"

MeshTriangle::MeshTriangle(const int i0, const int i1, const int i2)
    : m_index0(i0)
    , m_index1(i1)
    , m_index2(i2)
    , m_normal(0)
{}


MeshTriangle::MeshTriangle(const MeshTriangle& other)
    : m_index0(other.m_index0)
    , m_index1(other.m_index1)
    , m_index2(other.m_index2)
    , m_normal(other.m_normal)
{}


MeshTriangle& MeshTriangle::operator= (const MeshTriangle& rhs) 
{
    if( this == &rhs )
        return (*this);

    m_index0	= rhs.m_index0;
    m_index1	= rhs.m_index1;
    m_index2	= rhs.m_index2;
    m_normal	= rhs.m_normal;

    return (*this);
}


MeshTriangle::~MeshTriangle(void)
{}


void 
MeshTriangle::ComputeNormal(const Mesh* pMesh, const bool reverseNormal) 
{
    m_normal = (pMesh->vertices[m_index1] - pMesh->vertices[m_index0])
			 ^ (pMesh->vertices[m_index2] - pMesh->vertices[m_index0]);
    m_normal.Normalize();

    if( reverseNormal ) 
		m_normal = -m_normal;
}


void 
MeshTriangle::GetBoundingBox(const Mesh* pMesh, BBox& box) const 
{
    Point3D v1(pMesh->vertices[m_index0]);
    Point3D v2(pMesh->vertices[m_index1]);
    Point3D v3(pMesh->vertices[m_index2]);
    double delta = 0.0001;

    box.p0 = Point3D(	min2(min2(v1.x, v2.x), v3.x) - delta,
						min2(min2(v1.y, v2.y), v3.y) - delta,
						min2(min2(v1.z, v2.z), v3.z) - delta	);
    box.p1 = Point3D(	max2(max2(v1.x, v2.x), v3.x) + delta,
						max2(max2(v1.y, v2.y), v3.y) + delta,
						max2(max2(v1.z, v2.z), v3.z) + delta	);
}


bool 
MeshTriangle::Intersect(const Mesh* pMesh, const Ray& ray, double& tmin1, double& beta1, double& gamma1 ) const 
{
	const Point3D& v0 = pMesh->vertices[m_index0];
    const Point3D& v1 = pMesh->vertices[m_index1];
    const Point3D& v2 = pMesh->vertices[m_index2];

	double pa[18];
    pa[0] = v0.x - v1.x;
    pa[1] = v0.x - v2.x;
    pa[2] = ray.d.x;
    pa[3] = v0.x - ray.o.x;

    pa[4] = v0.y - v1.y;
    pa[5] = v0.y - v2.y;
    pa[6] = ray.d.y;
    pa[7] = v0.y - ray.o.y;

    pa[8] = v0.z - v1.z;
    pa[9] = v0.z - v2.z;
    pa[10] = ray.d.z;
    pa[11] = v0.z - ray.o.z;

    pa[12] = pa[5] * pa[10] - pa[6] * pa[9];
    pa[13] = pa[7] * pa[10] - pa[6] * pa[11];
    pa[14] = pa[5] * pa[11] - pa[7] * pa[9];
    pa[15] = pa[6] * pa[8]  - pa[4] * pa[10];
    pa[16] = pa[4] * pa[11] - pa[7] * pa[8];
    pa[17] = pa[4] * pa[9]  - pa[5] * pa[8];

    double invDenom = 1.0 / (pa[0] * pa[12] + pa[1] * pa[15] + pa[2] * pa[17]);
    double e1 = pa[3] * pa[12] - pa[1] * pa[13] - pa[2] * pa[14];
    double beta = e1 * invDenom;

    if( beta < 0.0 /*|| beta > 1.0*/ )
        return (false);

    double e2 = pa[0] * pa[13] + pa[3] * pa[15] + pa[2] * pa[16];
    double gamma = e2 * invDenom;

    if( gamma < 0.0 /*|| gamma > 1.0*/ )
        return (false);

    if( beta + gamma > 1.0 )
        return false;

    double e3 = pa[0] * pa[14] - pa[1] * pa[16] + pa[3] * pa[17];
    double tv = e3 * invDenom;

    if( tv < kEpsilon )
        return (false);

    tmin1	= tv;
	beta1	= beta;
	gamma1	= gamma;
	return (true);
}


float 
MeshTriangle::InterpolateU(const Mesh* pMesh, const float beta, const float gamma) const 
{
	return ((1 - beta - gamma) * pMesh->tu[m_index0] + beta * pMesh->tu[m_index1] + gamma * pMesh->tu[m_index2]);
}


float 
MeshTriangle::InterpolateV(const Mesh* pMesh, const float beta, const float gamma) const 
{
	return ((1 - beta - gamma) * pMesh->tv[m_index0] + beta * pMesh->tv[m_index1] + gamma * pMesh->tv[m_index2]);
}


Normal 
MeshTriangle::InterpolateNormal(const Mesh* pMesh, const float beta, const float gamma) const 
{
    Normal out((1 - beta - gamma) * pMesh->normals[m_index0] + beta * pMesh->normals[m_index1] + gamma * pMesh->normals[m_index2]);
    out.Normalize();
    return (out);
}


bool 
MeshTriangle::ShadowHit(const Mesh* pMesh, const Ray& ray, double& tmin) const 
{
	double beta, gamma;
	return (Intersect(pMesh, ray, tmin, beta, gamma));
}
