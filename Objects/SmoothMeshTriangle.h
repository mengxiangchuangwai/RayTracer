//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __SMOOTH_MESH_TRIANGLE__
#define __SMOOTH_MESH_TRIANGLE__


#include "../Objects/MeshTriangle.h"
#include "../Objects/Mesh.h"

class SmoothMeshTriangle : public MeshTriangle {
public:

    SmoothMeshTriangle(const int i0 = 0, const int i1 = 0, const int i2 = 0);

    SmoothMeshTriangle(const SmoothMeshTriangle& other);

    SmoothMeshTriangle& 
	operator= (const SmoothMeshTriangle& rhs);

    virtual 
	SmoothMeshTriangle* Clone(void) const;

    virtual 
	~SmoothMeshTriangle(void);

    virtual bool 
	Hit(const Mesh* pMesh, const Ray& ray, double& tmin, ShadeContext& sr) const;
};



inline bool 
SmoothMeshTriangle::Hit(const Mesh* pMesh, const Ray& ray, double& tmin, ShadeContext& sr) const 
{
   double beta, gamma;

   if( Intersect(pMesh, ray, tmin, beta, gamma) )
   { 
		sr.localHitPoint = ray.o + tmin * ray.d;
		sr.normal = InterpolateNormal(pMesh, beta, gamma);
		
		if( !pMesh->tu.empty() )
		{
			sr.tu = InterpolateU(pMesh, beta, gamma);
			sr.tv = InterpolateV(pMesh, beta, gamma);
		}

		return (true);
   }

   return (false);
}


#endif