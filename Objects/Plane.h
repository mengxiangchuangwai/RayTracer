//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __PLANE__
#define __PLANE__


#include "../Objects/GeometricObject.h"

class Plane: public GeometricObject {

	public:

		Plane(Material* mp = NULL);   							// default constructor

		Plane(const Point3D& point, const Normal& normal);		// constructor

		Plane(const Plane& other); 								// copy constructor

		virtual Plane* 											// virtual copy constructor
		Clone(void) const;

		Plane& 													// assignment operator
		operator= (const Plane& rhs);

		virtual													// destructor
		~Plane(void);

		virtual bool
		Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

		virtual bool
		ShadowHit(const Ray &ray, double &tmin) const;

		virtual void
		SetNormal(const Normal& val);

		virtual Normal
		GetNormal(const Point3D& p) const;

		virtual const Normal&
		GetNormal(void) const;


	protected:

		Point3D 	m_point;   			// point through which plane passes
		Normal 		m_normal;			// normal to the plane
};



inline void
Plane::SetNormal(const Normal& val) 
{
	m_normal = val;
}


inline Normal 
Plane::GetNormal(const Point3D& p) const 
{
    return (m_normal);
}


inline const Normal& 
Plane::GetNormal(void) const 
{
    return (m_normal);
}


#endif
