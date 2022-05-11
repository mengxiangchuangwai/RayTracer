//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __GRID__
#define __GRID__


#include "../Objects/Compound.h"

class Grid : public Compound {
public:

    Grid(Material* mp = NULL);

    Grid(const int nx, const int ny, const int nz, Material* mp = NULL);

    Grid(const Grid& other);

    Grid& 
	operator= (const Grid& rhs);

    Grid* 
	Clone(void) const;

    virtual 
	~Grid(void);

	virtual void 
	Clear(void);

    virtual bool 
	Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

	virtual bool 
	ShadowHit(const Ray& ray, double& tmin) const;

	void 
	SetDimensions(const int nx, const int ny, const int nz);

    void 
	MakeCells(void);


protected:

    std::vector<std::list<GeometricObject*>> m_cells;
	int m_dims[3];

	bool 
	Intersect(const Ray& ray, double& tval, ShadeContext& sr, bool shadowHit = false) const;

    bool 
	ListHit(const std::list<GeometricObject*>& ls, const Ray& ray, double& tval, ShadeContext& sr) const;

	bool 
	ListShadowHit(const std::list<GeometricObject*>& ls, const Ray& ray, double& tval) const;

};



inline void 
Grid::SetDimensions(const int nx, const int ny, const int nz)
{
    m_dims[0] = nx;
    m_dims[1] = ny;
    m_dims[2] = nz;
}


inline void
Grid::Clear(void) 
{
	m_dims[0] = m_dims[1] = m_dims[2] = 0;
	Compound::Clear();
}


inline bool 
Grid::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
	return (Intersect(ray, tmin, sr));
}


inline bool 
Grid::ShadowHit(const Ray& ray, double& tmin) const 
{
	if( !m_shadowing )
		return false;

	ShadeContext sr;
	return (Intersect(ray, tmin, sr, true));
}


#endif // __GRID__