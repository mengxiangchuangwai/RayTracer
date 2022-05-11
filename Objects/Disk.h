//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __DISK__
#define __DISK__


#include "../Objects/GeometricObject.h"

class Disk : public GeometricObject {
public:

    Disk(Material* mp = NULL);

    Disk(const Point3D& center, const Normal& normal, const double radius, Material* mp = NULL);

    Disk(const Disk& other);

    Disk& 
	operator= (const Disk& rhs);

    virtual Disk* 
	Clone(void) const;

	virtual 
	~Disk(void);

    virtual bool 
	Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

	virtual bool 
	ShadowHit(const Ray& ray, double& tmin) const;

    void 
	SetCenter(const Point3D& val);

    const Point3D& 
	GetCenter(void) const;

    void 
	SetRadius(const double val);

    double 
	GetRadius(void) const;

    virtual void 
	SetNormal(const Normal& val);

    virtual Normal
    GetNormal(const Point3D& p) const;

    virtual const Normal&
    GetNormal(void) const;


protected:

    Point3D     m_center;
    Normal      m_normal;
    double      m_radius;
};



inline void 
Disk::SetCenter(const Point3D& val) 
{
    m_center = val;
}


inline const Point3D& 
Disk::GetCenter(void) const 
{
    return (m_center);
}


inline void 
Disk::SetRadius(const double val) 
{
    m_radius = val;
}


inline double 
Disk::GetRadius(void) const 
{
    return (m_radius);
}


inline void 
Disk::SetNormal(const Normal& val) 
{
    m_normal = val;
    m_normal.Normalize();
}


inline Normal 
Disk::GetNormal(const Point3D& p) const
{
    return (m_normal);
}


inline const Normal& 
Disk::GetNormal(void) const
{
    return (m_normal);
}


#endif