//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __RECTANGLEX__
#define __RECTANGLEX__


#include "../Objects/GeometricObject.h"

class Sampler;

class RectangleX: public GeometricObject {
	public:

		RectangleX(Material* mp = NULL);

		RectangleX(const Point3D& p0, const Vector3D& a, const Vector3D& b, Material* mp = NULL);

		RectangleX(const Point3D& p0, const Vector3D& a, const Vector3D& b, const Normal& normal, Material* mp = NULL);

		virtual RectangleX*
		Clone(void) const;

		RectangleX(const RectangleX& other);

		virtual
		~RectangleX(void);

		RectangleX&
		operator= (const RectangleX& rhs);

		virtual void
		UpdateBoundingBox(void);

		virtual bool
		Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

		virtual bool
		ShadowHit(const Ray& ray, double& tmin) const;

		// the following functions are used when the rectangle is a light source

		virtual void
		SetSampler(Sampler* sampler);

		virtual Point3D
		Sample(void);

		virtual void
		SetNormal(const Normal& val);

		virtual Normal
		GetNormal(const Point3D& p) const;

		virtual const Normal&
		GetNormal(void) const;

		virtual float
		Pdf(const ShadeContext& sr, const Vector3D& wi);


	protected:
		
		bool
		Intersect(const Ray& ray, double& tmin, ShadeContext* pContext) const;

		Point3D 		m_p0;   		// corner vertex
		Vector3D		m_a;			// side
		Vector3D		m_b;			// side
		double			m_alenSq;		// square of the length of side a
		double			m_blenSq;		// square of the length of side b
		Normal			m_normal;

		double			m_area;			// for rectangular lights
		double			m_invArea;		// for rectangular lights
		Sampler*		m_pSampler;		// for rectangular lights
};



inline bool
RectangleX::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
	return (Intersect(ray, tmin, &sr));
}


inline bool
RectangleX::ShadowHit(const Ray& ray, double& tmin) const
{
	if( !m_shadowing )
		return (false);

	return (Intersect(ray, tmin, NULL));
}


inline void
RectangleX::SetNormal(const Normal& val) 
{
	m_normal = val;
}


inline Normal 
RectangleX::GetNormal(const Point3D& p) const
{
    return (m_normal);
}


inline const Normal& 
RectangleX::GetNormal(void) const
{
    return (m_normal);
}


inline float
RectangleX::Pdf(const ShadeContext& sr, const Vector3D& wi) 
{
	return ((float)(m_invArea));
}


typedef RectangleX	RectangleEmitter;


#endif