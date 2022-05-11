//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __MESH_TRIANGLE__
#define __MESH_TRIANGLE__


#include "../Objects/BBox.h"
#include "../Utilities/Normal.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeContext.h"

class Mesh;
class Material;

class MeshTriangle {
public:

    MeshTriangle(const int i0 = 0, const int i1 = 0, const int i2 = 0);

    MeshTriangle(const MeshTriangle& other);

    MeshTriangle& 
	operator= (const MeshTriangle& rhs);

    virtual MeshTriangle* 
	Clone(void) const = 0;

    virtual 
	~MeshTriangle(void);

    void 
	ComputeNormal(const Mesh* pMesh, const bool reverseNormal = false);

    virtual bool 
	Hit(const Mesh* pMesh, const Ray& ray, double& tmin, ShadeContext& sr) const = 0;

	virtual bool 
	ShadowHit(const Mesh* pMesh, const Ray& ray, double& tmin) const;

	virtual Material*
	GetMaterial(void) const;

    virtual const Normal& 
	GetNormal(void) const;
	
	virtual void 
	GetBoundingBox(const Mesh* pMesh, BBox& box) const;

	void 
	GetIndices(int& i0, int& i1, int& i2) const;

	void 
	SetIndices(const int i0, const int i1, const int i2);


protected:

    int		m_index0;
    int		m_index1;
    int		m_index2;
    Normal	m_normal;

    float 
	InterpolateU(const Mesh* pMesh, const float beta, const float gamma) const;
   
	float 
	InterpolateV(const Mesh* pMesh, const float beta, const float gamma) const;

	Normal 
	InterpolateNormal(const Mesh* pMesh, const float beta, const float gamma) const;

	bool 
	Intersect(const Mesh* pMesh, const Ray& ray, double& tmin, double& beta, double& gamma ) const;
};



inline Material*
MeshTriangle::GetMaterial(void) const
{
	return (NULL);
}


inline const Normal& 
MeshTriangle::GetNormal(void) const
{
    return (m_normal);
}


inline void 
MeshTriangle::GetIndices(int& i0, int& i1, int& i2) const
{
	i0 = m_index0; i1 = m_index1; i2 = m_index2;
}


inline void 
MeshTriangle::SetIndices(const int i0, const int i1, const int i2)
{
	m_index0 = i0; m_index1 = i1; m_index2 = i2;
}


#endif // __MESHTRIANGLE__