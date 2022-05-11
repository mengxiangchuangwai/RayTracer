//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __TRIANGLE__
#define __TRIANGLE__


#include "../Objects/GeometricObject.h"
#include "../Utilities/Maths.h"

class Triangle : public GeometricObject {
    public:

        Triangle(Material* mp = NULL);

        Triangle(const Point3D& a, const Point3D& b, const Point3D& c, Material* mp = NULL);

        Triangle(const Triangle& other);

        Triangle& operator= (const Triangle& rhs);

        Triangle* Clone(void) const;

        void 
		GetVertices(Point3D& a, Point3D& b, Point3D& c) const;

        void 
		SetVertices(const Point3D& a, const Point3D& b, const Point3D& c);

        virtual Normal 
		GetNormal(const Point3D& p) const;

        virtual const Normal& 
		GetNormal(void) const;

        void 
		ComputeNormal(void);

        virtual void 
		UpdateBoundingBox(void);

        virtual bool 
		Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

        virtual bool 
		ShadowHit(const Ray& ray, double& tmin) const;


    protected:

		bool 
		Intersect(const Ray& ray, double& tval) const;

        Point3D m_v0, m_v1, m_v2;
        Normal m_normal;
};



inline bool 
Triangle::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{ 	
	if( Intersect(ray, tmin) )
	{
		sr.normal = m_normal;
		sr.localHitPoint = ray.o + tmin * ray.d;
		return (true);
	}

	return (false);
}


inline bool 
Triangle::ShadowHit(const Ray& ray, double& tmin) const 
{    
	if( !m_shadowing )
		return (false);

	return (Intersect(ray, tmin));
}


inline void 
Triangle::GetVertices(Point3D& a, Point3D& b, Point3D& c) const
{
    a = m_v0, b = m_v1, c = m_v2;
}


inline void 
Triangle::SetVertices(const Point3D& a, const Point3D& b, const Point3D& c)
{
    m_v0 = a, m_v1 = b, m_v2 = c;
}


inline Normal 
Triangle::GetNormal(const Point3D& p) const
{
    return (m_normal);
}


inline const Normal& 
Triangle::GetNormal(void) const
{
    return (m_normal);
}


inline void 
Triangle::ComputeNormal(void) 
{
    m_normal = (m_v1 - m_v0) ^ (m_v2 - m_v0);
	m_normal.Normalize();
}


#endif