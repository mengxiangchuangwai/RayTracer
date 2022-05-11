//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __AREA_LIGHT_ADAPTER__
#define __AREA_LIGHT_ADAPTER__


#include "../Utilities/RGBColor.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Lights/Light.h"
#include "../Materials/Material.h"
#include "../Objects/GeometricObject.h"

class AreaLightAdapter: public Light {
	public:

		AreaLightAdapter(void);

		AreaLightAdapter(const AreaLightAdapter& other);

		AreaLightAdapter&
		operator= (const AreaLightAdapter& rhs);

		virtual AreaLightAdapter*
		Clone(void) const;

		virtual
		~AreaLightAdapter(void);

		void
		SetEmitter(GeometricObject* pObject);

		GeometricObject*
		GetEmitter(void) const;

		virtual Vector3D
		GetDirection(ShadeContext& sr);

		virtual RGBColor
		L(ShadeContext& sr);

		virtual bool
		InShadow(const Ray& ray, const ShadeContext& sr) const;

		virtual float
		G(const ShadeContext& sr) const;

		virtual float
		Pdf(const ShadeContext& sr) const;

		virtual void 
		BeginSection(void);
		
		virtual void
		EndSection(void);


	private:

		GeometricObject* 	m_pEmitter;
		Point3D				m_samplePoint;
		Normal				m_lightNormal;	// assigned in get_direction - which therefore can't be const for any light
		Vector3D			m_wi;			// unit direction from hit point being shaded to sample point on light surface

};



inline void
AreaLightAdapter::SetEmitter(GeometricObject* pObject) 
{
	SAFE_DELETE(m_pEmitter);
	m_pEmitter = pObject;
}


inline GeometricObject*
AreaLightAdapter::GetEmitter(void) const
{
	return (m_pEmitter);
}


inline Vector3D
AreaLightAdapter::GetDirection(ShadeContext& sr) 
{
	m_samplePoint = m_pEmitter->Sample();    // used in the G function
	m_lightNormal = m_pEmitter->GetNormal(m_samplePoint);
	m_wi = m_samplePoint - sr.hitPoint;  	// used in the G function
	m_wi.Normalize();
	return (m_wi);
}


inline RGBColor
AreaLightAdapter::L(ShadeContext& sr) 
{
	double ndotd = -m_lightNormal * m_wi;

	if( ndotd > 0.0 )
		return (m_pEmitter->GetMaterial()->GetLe(sr));
	else
		return BLACK;
}


// G is part of the geometric factor

inline float
AreaLightAdapter::G(const ShadeContext& sr) const 
{
	double ndotd = -m_lightNormal * m_wi;
	double d2 = m_samplePoint.DistanceSq(sr.hitPoint);
	return (float)(ndotd / d2);
}


inline float
AreaLightAdapter::Pdf(const ShadeContext& sr) const 
{
	return (m_pEmitter->Pdf(sr, m_wi));
}


inline void 
AreaLightAdapter::BeginSection(void)
{
	m_cs.lock();
}


inline void
AreaLightAdapter::EndSection(void)
{
	m_cs.unlock();
}


#endif