//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __CYLINDER__
#define __CYLINDER__


#include "../Objects/Compound.h"
#include "../Objects/OpenCylinder.h"
#include "../Objects/Disk.h"

class Cylinder : public Compound {
public:

    Cylinder(Material* mp = NULL);

    Cylinder(const double y0, const double y1, const double radius, Material* mp = NULL);

    Cylinder(const Cylinder& other);

    Cylinder* 
	Clone(void) const;

    Cylinder& 
	operator= (const Cylinder& rhs);

    void 
	SetRadius(const double val);

    double 
	GetRadius(void) const;

    void 
	SetY0(const double val);

    double 
	GetY0(void) const;

    void 
	SetY1(const double val);

    double 
	GetY1(void) const;

    virtual void 
	UpdateBoundingBox(void);

    virtual bool 
	Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

	virtual bool 
	ShadowHit(const Ray& ray, double& tmin) const;


protected:

    Disk*			m_pTop;
    OpenCylinder*	m_pSide;
    Disk*			m_pBottom;
};



inline void 
Cylinder::SetRadius(const double val) 
{
    m_pTop->SetRadius(val);
    m_pSide->SetRadius(val);
    m_pBottom->SetRadius(val);
    UpdateBoundingBox();
}


inline double 
Cylinder::GetRadius(void) const 
{
    return (m_pTop->GetRadius());
}


inline void 
Cylinder::SetY0(const double val) 
{
    Point3D center = m_pTop->GetCenter();
    center.y = val;
    m_pBottom->SetCenter(center);
    m_pSide->SetY0(val);
    UpdateBoundingBox();
}


inline double 
Cylinder::GetY0(void) const 
{
    return (m_pSide->GetY0());
}


inline void 
Cylinder::SetY1(const double val) 
{
    Point3D center = m_pBottom->GetCenter();
    center.y = val;
    m_pTop->SetCenter(center);
    m_pSide->SetY1(val);
    UpdateBoundingBox();
}


inline double 
Cylinder::GetY1(void) const 
{
    return (m_pSide->GetY1());
}


inline bool 
Cylinder::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
	bool result = false;

    if( m_bbox.Hit(ray) )
	{
		if( result = Compound::Hit(ray, tmin, sr) )
		{
			if( m_reverseNormal )
				sr.normal = -sr.normal;
		}
	}

	return (result);
}


inline bool 
Cylinder::ShadowHit(const Ray& ray, double& tmin) const 
{
	if( !m_shadowing )
		return (false);

    if( m_bbox.Hit(ray) )
        return (Compound::ShadowHit(ray, tmin));

    return (false);
}


#endif