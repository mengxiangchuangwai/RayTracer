//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __AMBIENT__
#define __AMBIENT__

#include "../Lights/Light.h"

class Ambient: public Light {
	public:

		Ambient(void);

		Ambient(const Ambient& other);

		Ambient&
		operator= (const Ambient& rhs);

		virtual Ambient*
		Clone(void) const;

		virtual
		~Ambient(void);

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

		virtual Vector3D
		GetDirection(ShadeContext& sr);

		virtual RGBColor
		L(ShadeContext& s);


	private:

		float		m_ls;
		RGBColor	m_color;
};



inline void
Ambient::SetRadianceScaler(const float s) 
{
	m_ls = s;
}


inline float
Ambient::GetRadianceScaler(void) const
{
	return (m_ls);
}


inline void
Ambient::SetColor(const float c) 
{
	m_color.r = c; m_color.g = c; m_color.b = c;
}


inline void
Ambient::SetColor(const RGBColor& c) 
{
	m_color = c;
}


inline const RGBColor&
Ambient::GetColor(void) const
{
	return (m_color);
}


inline void
Ambient::SetColor(const float r, const float g, const float b) 
{
	m_color.r = r; m_color.g = g; m_color.b = b;
}


inline Vector3D
Ambient::GetDirection(ShadeContext& sr) 
{
	return (Vector3D(0.0));
}


inline RGBColor
Ambient::L(ShadeContext& sr) 
{
	return (m_ls * m_color);
}


#endif