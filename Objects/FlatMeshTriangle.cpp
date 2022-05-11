//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/FlatMeshTriangle.h"
#include "../Objects/Mesh.h"

FlatMeshTriangle::FlatMeshTriangle(const int i0, const int i1, const int i2)
    : MeshTriangle(i0, i1, i2)
{}


FlatMeshTriangle::FlatMeshTriangle(const FlatMeshTriangle& other)
    : MeshTriangle(other)
{}


FlatMeshTriangle& 
FlatMeshTriangle::operator=(const FlatMeshTriangle& rhs) 
{
    if( this == &rhs )
        return (*this);

    MeshTriangle::operator= (rhs);
    return (*this);
}


FlatMeshTriangle* 
FlatMeshTriangle::Clone(void) const 
{
    return (new FlatMeshTriangle(*this));
}


FlatMeshTriangle::~FlatMeshTriangle(void) 
{}


bool 
FlatMeshTriangle::Hit(const Mesh* pMesh, const Ray& ray, double& tmin, ShadeContext& sr) const 
{
    double beta, gamma;

	if( Intersect(pMesh, ray, tmin, beta, gamma) )
	{
		sr.normal = m_normal;
		sr.localHitPoint = ray.o + tmin * ray.d;
		
		if( !pMesh->tu.empty() )
		{
			sr.tu = InterpolateU(pMesh, beta, gamma);
			sr.tv = InterpolateV(pMesh, beta, gamma);
		}
		return (true);
	}
	
	return (false);
}