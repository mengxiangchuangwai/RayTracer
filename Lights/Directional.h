//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__


#include "../Lights/Light.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeContext.h"

class Directional: public Light {
	public:

		Directional(void);

		Directional(const Directional& other);

		Directional&
		operator= (const Directional& rhs);

		virtual Directional*
		Clone(void) const;

		virtual
		~Directional(void);

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
		SetDirection(const Vector3D& dir);

		void
		SetDirection(const float dx, const float dy, const float dz);

		virtual Vector3D
		GetDirection(ShadeContext& sr);

		virtual RGBColor
		L(ShadeContext& sr);

		virtual bool
    	InShadow(const Ray& ray, const ShadeContext& sr) const;


	private:

		float		m_ls;
		RGBColor	m_color;
		Vector3D	m_dir;		// direction the light comes from
};



inline void
Directional::SetRadianceScaler(const float s) 
{
	m_ls = s;
}


inline float
Directional::GetRadianceScaler(void) const
{
	return (m_ls);
}


inline void
Directional::SetColor(const float c) 
{
	m_color.r = c; m_color.g = c; m_color.b = c;
}


inline void
Directional::SetColor(const RGBColor& c) 
{
	m_color = c;
}


inline void
Directional::SetColor(const float r, const float g, const float b) 
{
	m_color.r = r; m_color.g = g; m_color.b = b;
}


inline const RGBColor&
Directional::GetColor(void) const
{
	return (m_color);
}


inline void
Directional::SetDirection(const Vector3D& dir) 
{
	m_dir = dir;
	m_dir.Normalize();
}


inline void
Directional::SetDirection(const float dx, const float dy, const float dz) 
{
	m_dir.x = dx; m_dir.y = dy; m_dir.z = dz;
	m_dir.Normalize();
}


inline Vector3D
Directional::GetDirection(ShadeContext& sr) 
{
	return (m_dir);
}


inline RGBColor
Directional::L(ShadeContext& sr) 
{
	return (m_ls * m_color);
}


#endif