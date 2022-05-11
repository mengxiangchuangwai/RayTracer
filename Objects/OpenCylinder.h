//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __OPEN_CYLINDER__
#define __OPEN_CYLINDER__


#include "../Objects/GeometricObject.h"
#include "../Utilities/Maths.h"

class OpenCylinder : public GeometricObject {
public:

    OpenCylinder(Material* mp = NULL);

    OpenCylinder(const double y0, const double y1, const double radius, Material* mp = NULL);

    OpenCylinder(const OpenCylinder& other);

    OpenCylinder& 
	operator= (const OpenCylinder& rhs);

    virtual OpenCylinder* 
	Clone(void) const;

    virtual void 
	UpdateBoundingBox();

    virtual bool 
	Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

    virtual bool 
	ShadowHit(const Ray& ray, double& tmin) const;

    void 
	SetY0(const double val);

    double 
	GetY0(void) const;

    void 
	SetY1(const double val);
    
	double 
	GetY1(void) const;

    void 
	SetRadius(const double val);
    
	double 
	GetRadius(void) const;


protected:

    double m_y0;
    double m_y1;
    double m_radius;
};


inline void 
OpenCylinder::SetY0(const double val) 
{
    m_y0 = val;
}


inline double 
OpenCylinder::GetY0(void) const 
{
    return (m_y0);
}


inline void 
OpenCylinder::SetY1(const double val) 
{
    m_y1 = val;
}


inline double 
OpenCylinder::GetY1(void) const 
{
    return (m_y1);
}


inline void 
OpenCylinder::SetRadius(const double val) 
{
    m_radius = val;
}


inline double 
OpenCylinder::GetRadius(void) const 
{
    return (m_radius);
}


#endif