//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __COMPOUND__
#define __COMPOUND__


#include "../Objects/GeometricObject.h"
#include "../Materials/Material.h"

class Compound: public GeometricObject {
public:

    Compound(Material* mp = NULL);

    Compound(const Compound& other);

    Compound& 
	operator= (const Compound& rhs);

    Compound* 
	Clone(void) const;

    virtual ~Compound(void);

    virtual Material* 
	GetMaterial(void) const;

    virtual void 
	SetMaterial(Material* mp);

    virtual void 
	UpdateBoundingBox(void);

    virtual bool 
	Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

    virtual bool 
	ShadowHit(const Ray& ray, double& tmin) const;

	virtual void 
	Clear(void);

	void 
	AddObject(GeometricObject* op);

    void 
	DeleteObjects(void);


protected:

    mutable Material* m_pLocalMaterial;
    std::vector<GeometricObject*> m_objects;
};



inline void
Compound::Clear(void) 
{
	DeleteObjects();
}


inline Material*
Compound::GetMaterial(void) const 
{
	return (NULL == m_pLocalMaterial ? m_pMaterial : m_pLocalMaterial);
}


inline void Compound::SetMaterial(Material* mp) 
{
	GeometricObject::SetMaterial(mp);
}


#endif