//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __MESH_GRID__
#define __MESH_GRID__


#include <vector>
#include <list>
#include "../Objects/MeshObject.h"

class MeshGrid : public MeshObject
{
public:
	MeshGrid(Material* mp = NULL);

    MeshGrid(const int nx, const int ny, const int nz, Material* mp = NULL);

    MeshGrid(const MeshGrid& other);

    MeshGrid& operator= (const MeshGrid& rhs);

    MeshGrid* Clone(void) const;

    virtual ~MeshGrid(void);

    void 
	SetDimensions(const int nx, const int ny, const int nz);

	void
	GetDimensions(int& nx, int& ny, int& nz) const;

    void 
	MakeCells(void);

    virtual bool 
	Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

	virtual bool 
	ShadowHit(const Ray& ray, double& tmin) const;


protected:

    std::vector<std::list<MeshTriangle*>> m_cells;
	int m_dims[3];

	bool 
	Intersect(const Ray& ray, double& tval, ShadeContext& sr, bool shadowHit = false) const;

    bool 
	ListHit(const std::list<MeshTriangle*>& ls, const Ray& ray, double& tval, ShadeContext& sr) const;

	bool 
	ListShadowHit(const std::list<MeshTriangle*>& ls, const Ray& ray, double& tval) const;

};



inline void 
MeshGrid::SetDimensions(const int nx, const int ny, const int nz)
{
    m_dims[0] = nx;
    m_dims[1] = ny;
    m_dims[2] = nz;
}


inline void
MeshGrid::GetDimensions(int& nx, int& ny, int& nz) const
{
	nx = m_dims[0];
	ny = m_dims[1];
	nz = m_dims[2];
}


inline bool 
MeshGrid::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{	
	return (Intersect(ray, tmin, sr));
}


inline bool 
MeshGrid::ShadowHit(const Ray& ray, double& tmin) const 
{
	if( !m_shadowing )
		return false;

	ShadeContext sr;
	return (Intersect(ray, tmin, sr, true));
}


#endif // __MESH_GRID__