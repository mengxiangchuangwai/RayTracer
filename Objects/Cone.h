//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __CONE__
#define __CONE__


#include "../Objects/Compound.h"
#include "../Objects/OpenCone.h"
#include "../Objects/Disk.h"

class Cone : public Compound {
public:

    Cone(Material* mp = NULL);

    Cone(const double y0, const double y1, const double radius, Material* mp = NULL);

    Cone(const Cone& other);

    Cone* 
	Clone(void) const;

    Cone& 
	operator= (const Cone& rhs);

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

	OpenCone*	m_pSide;
    Disk*		m_pBottom;
};



inline void 
Cone::SetRadius(const double val) 
{
    m_pSide->SetRadius(val);
    m_pBottom->SetRadius(val);
    UpdateBoundingBox();
}


inline double 
Cone::GetRadius(void) const 
{
    return (m_pBottom->GetRadius());
}


inline void 
Cone::SetY0(const double val) 
{
    Point3D center = m_pBottom->GetCenter();
    center.y = val;
    m_pBottom->SetCenter(center);
    m_pSide->SetY0(val);
    UpdateBoundingBox();
}


inline double 
Cone::GetY0(void) const 
{
    return (m_pSide->GetY0());
}


inline void 
Cone::SetY1(const double val) 
{
    m_pSide->SetY1(val);
    UpdateBoundingBox();
}


inline double 
Cone::GetY1(void) const 
{
    return (m_pSide->GetY1());
}


inline bool 
Cone::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
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
Cone::ShadowHit(const Ray& ray, double& tmin) const 
{
	if( !m_shadowing )
		return (false);

    if( m_bbox.Hit(ray) )
        return (Compound::ShadowHit(ray, tmin));

    return (false);
}


#endif