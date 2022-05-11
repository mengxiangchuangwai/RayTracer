//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __FLAT_MESH_TRIANGLE__
#define __FLAT_MESH_TRIANGLE__


#include "../Objects/MeshTriangle.h"

class FlatMeshTriangle : public MeshTriangle {
public:

    FlatMeshTriangle(const int i0 = 0, const int i1 = 0, const int i2 = 0);

    FlatMeshTriangle(const FlatMeshTriangle& other);

    FlatMeshTriangle& 
	operator= (const FlatMeshTriangle& rhs);

    virtual FlatMeshTriangle* 
	Clone(void) const;

    virtual 
	~FlatMeshTriangle(void);

    virtual bool 
	Hit(const Mesh* pMesh, const Ray& ray, double& tmin, ShadeContext& sr) const;
};


#endif