//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __MESH_OBJECT__
#define __MESH_OBJECT__


#include "../Objects/GeometricObject.h"
#include "../Objects/Mesh.h"

typedef enum {
	TT_Flat,
	TT_Smooth
} TriangleType;

class MeshObject: public GeometricObject {
public:

    MeshObject(Material* mp = NULL);

    MeshObject(const MeshObject& other);

    MeshObject& 
	operator= (const MeshObject& rhs);

    MeshObject* 
	Clone(void) const;

    virtual 
	~MeshObject(void);

	void 
	Clear(void);

    virtual void 
	UpdateBoundingBox(void);

    virtual bool 
	Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

	virtual bool 
	ShadowHit(const Ray& ray, double& tmin) const;

	void 
	ReadFlatTriangles(const char* pFileName);

    void 
	ReadFlatTexTriangles(const char* pFileName);

    void 
	ReadSmoothTriangles(const char* pFileName);

    void 
	ReadSmoothTexTriangles(const char* pFileName);

	void ReverseNormals(bool val);


protected:

    Mesh*	m_pMesh;
    bool	m_reverseNormal;
	
    void 
	ReadPlyFile(const char* pFileName, const int triangleType);

    void 
	ReadTexPlyFile(const char* pFileName, const int triangleType);
   
	void 
	ComputeVertexNormals(void);
};



inline void 
MeshObject::Clear(void) 
{
	m_pMesh->Clear();
}


inline void 
MeshObject::ReadFlatTriangles(const char* pFileName) 
{
  	ReadPlyFile(pFileName, TT_Flat);
}


inline void 
MeshObject::ReadSmoothTriangles(const char* pFileName) 
{
  	ReadPlyFile(pFileName, TT_Smooth);
  	ComputeVertexNormals();
}


inline void
MeshObject::ReadFlatTexTriangles(const char* pFileName) 
{
  	ReadTexPlyFile(pFileName, TT_Flat);
}


inline void
MeshObject::ReadSmoothTexTriangles(const char* pFileName) 
{
  	ReadTexPlyFile(pFileName, TT_Smooth);
  	ComputeVertexNormals();
}


inline void 
MeshObject::ReverseNormals(bool val)
{
	m_reverseNormal = val;
}


#endif // __MESH_OBJECT__
