//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __POINT_LIGHT__
#define __POINT_LIGHT__


#include "../Lights/Light.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/RGBColor.h"

class PointLight: public Light {
	public:

		PointLight(void);

		PointLight(const PointLight& other);

		virtual PointLight*
		Clone(void) const;

		PointLight&
		operator= (const PointLight& rhs);

		virtual
		~PointLight(void);

		void
		SetRadianceScaler(const float s);

		float
		GetRadianceScaler(void) const;

		void
		SetColor(const float c);

		void
		SetColor(const RGBColor& c);

		void
		SetColor(const float r, const float g, const float b);

		const RGBColor&
		GetColor(void) const;

		void
		SetLocation(const Point3D& pt);

		void
		SetLocation(const float x, const float y, const float z);

		const Point3D&
		GetLocation(void) const;

		virtual Vector3D
		GetDirection(ShadeContext& sr);

		virtual RGBColor
		L(ShadeContext& sr);

		virtual bool
    	InShadow(const Ray& ray, const ShadeContext& sr) const;


	private:

		float		m_ls;
		RGBColor	m_color;
		Point3D     m_location;
};



inline void
PointLight::SetRadianceScaler(const float s) 
{
	m_ls = s;
}


inline float
PointLight::GetRadianceScaler(void) const
{
	return (m_ls);
}


inline void
PointLight::SetColor(const float c) 
{
	m_color.r = c; m_color.g = c; m_color.b = c;
}


inline void
PointLight::SetColor(const RGBColor& c) 
{
	m_color = c;
}


inline void
PointLight::SetColor(const float r, const float g, const float b) 
{
	m_color.r = r; m_color.g = g; m_color.b = b;
}


inline const RGBColor&
PointLight::GetColor(void) const
{
	return (m_color);
}


inline void
PointLight::SetLocation(const Point3D& pt) 
{
	m_location = pt;
}


inline void
PointLight::SetLocation(const float x, const float y, const float z) 
{
	m_location.x = x;
	m_location.y = y;
	m_location.z = z;
}


inline const Point3D&
PointLight::GetLocation(void) const
{
	return (m_location);
}


inline Vector3D
PointLight::GetDirection(ShadeContext& sr) 
{
	return (m_location - sr.hitPoint).Hat();
}


inline RGBColor
PointLight::L(ShadeContext& sr) 
{
	return (m_ls * m_color);
}


#endif