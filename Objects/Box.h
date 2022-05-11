//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __BOX__
#define __BOX__


#include "../Objects/GeometricObject.h"

class Box : public GeometricObject {
public:

    Box(Material* mp = NULL);

    Box(const Point3D& a, const Point3D& b, Material* mp = NULL);

    Box(const Box& other);

    virtual Box* 
	Clone(void) const;

    Box& 
	operator= (const Box& rhs);

    virtual void 
	UpdateBoundingBox(void);

    virtual bool 
	Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

    virtual bool 
	ShadowHit(const Ray& ray, double& tmin) const;

    Normal 
	GetNormal(const int faceId) const;

    void 
	SetP0(const Point3D& val);

    const Point3D& 
	GetP0(void) const;

    void 
	SetP1(const Point3D& val);
    
	const Point3D& 
	GetP1(void) const;

    void 
	SetDimensions(const Point3D& val);
    
	const Point3D& 
	GetDimensions(void) const;

    void 
	SetDimensionX(const double width);
    
	void 
	SetDimensionY(const double height);
    
	void 
	SetDimensionZ(const double depth);


protected:

	bool 
	Intersect(const Ray& ray, double& tval, ShadeContext* pSR = NULL) const;

    Point3D m_p0;
    Point3D m_p1;
    Point3D m_dims;
};



inline void 
Box::SetP0(const Point3D& val) 
{
    m_p0 = val;
}


inline const Point3D& 
Box::GetP0(void) const 
{
    return (m_p0);
}


inline void 
Box::SetP1(const Point3D& val) 
{
	m_p1 = val;
    m_dims.x = m_p1.x - m_p0.x;
	m_dims.y = m_p1.y - m_p0.y;
	m_dims.z = m_p1.z - m_p0.z;
}


inline const Point3D& 
Box::GetP1(void) const 
{
    return (m_p1);
}


inline void 
Box::SetDimensions(const Point3D& val) 
{
    m_dims	= val;
    m_p1.x	= m_p0.x + m_dims.x;
    m_p1.y	= m_p0.y + m_dims.y;
    m_p1.z	= m_p0.z + m_dims.z;
}


inline const Point3D& 
Box::GetDimensions(void) const 
{
    return	(m_dims);
}


inline void 
Box::SetDimensionX(const double width)
{
	m_dims.x	= width;
	m_p1.x		= m_p0.x + width;		
}
    

inline void 
Box::SetDimensionY(const double height)
{
	m_dims.y	= height;
	m_p1.y		= m_p0.y + height;
}
 

inline void 
Box::SetDimensionZ(const double depth)
{
	m_dims.z	= depth;
	m_p1.z		= m_p0.z + depth;
}


inline bool 
Box::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
    return Intersect(ray, tmin, &sr);
}


inline bool 
Box::ShadowHit(const Ray& ray, double& tmin) const 
{
    if( !m_shadowing )
		return false;

    return Intersect(ray, tmin);
}


#endif