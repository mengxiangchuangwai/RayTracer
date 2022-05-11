//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __GEOMETRIC_OBJECT__
#define __GEOMETRIC_OBJECT__


#include <vector>
#include <list>

#include "../Objects/BBox.h"
#include "../Samplers/Sampler.h"
#include "../Utilities/RefCounter.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Ray.h"
#include "../Utilities/ShadeContext.h"
#include "../Utilities/Maths.h"
#include "../Utilities/Constants.h"

class Material;

class GeometricObject {

	public:

        GeometricObject(Material* mp = NULL);

		GeometricObject(const GeometricObject& other);

		virtual GeometricObject*
		Clone(void) const = 0;

		virtual
		~GeometricObject (void);

		virtual bool
		Hit(const Ray& ray, double& tmin, ShadeContext& sr) const = 0;

		virtual bool
    	ShadowHit(const Ray& ray, double& tmin) const;

		virtual Material*
		GetMaterial(void) const;

		virtual void
		SetMaterial(Material* mp);

		void
		SetColor(const RGBColor &c);

		void
		SetColor(const float r, const float g, const float b);

		RGBColor
		GetColor(void);

		void
		ReverseNormal(const bool b);

		bool
		IsNormalReverse(void) const;

		virtual const BBox&
		GetBoundingBox(void) const;

		virtual void
		GetBoundingBox(BBox& box) const;

		virtual void
		SetBoundingBox(const BBox& box);

		virtual void
		UpdateBoundingBox(void);

		void
    	SetShadows(const bool b);

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
		Pdf(const ShadeContext& sr);

		virtual float
		Pdf(const ShadeContext& sr, const Vector3D&	wi);

		virtual GeometricObject*
		Release(void);

		virtual GeometricObject*
		AddRef(void);

		virtual int
		GetRef(void) const;
		

	protected:

		GeometricObject&
		operator= (const GeometricObject& rhs);

        Material*	m_pMaterial;
		RGBColor	m_color;
		BBox		m_bbox;
		bool		m_shadowing;
		bool		m_reverseNormal;

		RefCounter	m_counter;
};



inline Material*
GeometricObject::GetMaterial(void) const 
{
    return (m_pMaterial);
}


inline void
GeometricObject::SetColor(const RGBColor &c) 
{
	m_color = c;
}


inline void
GeometricObject::SetColor(const float r, const float g, const float b) 
{
	m_color.r = r;
	m_color.b = b;
	m_color.g = g;
}


inline RGBColor
GeometricObject::GetColor(void) 
{
	return (m_color);
}


inline void
GeometricObject::SetShadows(const bool b) 
{
    m_shadowing = b;
}


inline Point3D
GeometricObject::Sample(void) 
{
	return Point3D();
}


inline void
GeometricObject::ReverseNormal(const bool b)
{
	m_reverseNormal = b;
}

		
inline bool
GeometricObject::IsNormalReverse(void) const
{
	return (m_reverseNormal);
}


inline const BBox&
GeometricObject::GetBoundingBox(void) const 
{
	return m_bbox;
}


inline void
GeometricObject::GetBoundingBox(BBox& box) const 
{
	box = m_bbox;
}


inline void
GeometricObject::SetBoundingBox(const BBox& box) 
{}


inline void
GeometricObject::UpdateBoundingBox(void) 
{}


inline void 
GeometricObject::SetNormal(const Normal& val) 
{}


inline float
GeometricObject::Pdf(const ShadeContext& sr) 
{
	return 0.0f;
}


inline float
GeometricObject::Pdf(const ShadeContext& sr, const Vector3D& wi) 
{
	return 0.0f;
}


inline GeometricObject*
GeometricObject::Release(void) 
{
	m_counter.Release();
	return this;
}


inline GeometricObject*
GeometricObject::AddRef(void) 
{
	m_counter.AddRef();
	return this;
}


inline int 
GeometricObject::GetRef(void) const 
{
	return (m_counter.GetRef());
}


#endif
