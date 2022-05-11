//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __SMOOTH_TRIANGLE__
#define __SMOOTH_TRIANGLE__


// This triangle has three normals which are linearly interpolated at the hit point
// for smooth shading
// Making the normals public simplifies the code in the Grid::tessellate_smooth_sphere. This is currently
// the only function that uses this class. The only figure that uses it is Figure 23.3

#include "../Objects/GeometricObject.h"

class SmoothTriangle: public GeometricObject {
	public:

		SmoothTriangle (Material* mp = NULL);

		SmoothTriangle (const Point3D& a, const Point3D& b, const Point3D& c, Material* mp = NULL);

		virtual SmoothTriangle*
		Clone(void) const;

		SmoothTriangle(const SmoothTriangle& other);

		virtual
		~SmoothTriangle(void);

		SmoothTriangle&
		operator= (const SmoothTriangle& rhs);

        virtual void 
		UpdateBoundingBox(void);

		virtual bool
		Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

		virtual bool
		ShadowHit(const Ray& ray, double& tmin) const;


	protected:

		bool 
		Intersect(const Ray& ray, double& tval, double& beta, double& gamma) const;

		Normal
		InterpolateNormal(const float beta, const float gamma) const;

		Point3D		m_v0, m_v1, m_v2;
		Normal		m_n0, m_n1, m_n2;		// normals at each vertex
};



inline bool
SmoothTriangle::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
	double beta, gamma;
	
	if( Intersect(ray, tmin, beta, gamma) )
	{
		sr.normal = InterpolateNormal(beta, gamma);
		sr.localHitPoint = ray.o + tmin * ray.d;

		return (true);
	}

	return (false);
}


// Hit function for shadow rays

inline bool
SmoothTriangle::ShadowHit(const Ray& ray, double& tmin) const 
{
    if( !m_shadowing )
		return (false);

	double beta, gamma;
	return (Intersect(ray, tmin, beta, gamma));
}


#endif