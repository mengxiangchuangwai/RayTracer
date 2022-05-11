//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __EMISSIVE__
#define __EMISSIVE__


#include "../Materials/Material.h"

class Emissive: public Material {
	public:

		Emissive(void);

		Emissive(const Emissive& other);

		virtual Emissive*
		Clone(void) const;

		Emissive&
		operator= (const Emissive& rhs);

		virtual 
		~Emissive(void);

		virtual RGBColor
		Shade(ShadeContext& sr);

		virtual RGBColor
		AreaLightShade(ShadeContext& sr);

		virtual RGBColor
		PathShade(ShadeContext& sr);

		void
		SetCe(const RGBColor &c);

		void
		SetCe(const float r, const float g, const float b);

		void
		SetCe(const float c);

		virtual RGBColor
		GetLe(ShadeContext& sr) const;

		void
		SetRadianceScaler(const float s);

	
	private:

		float		m_ls;		// radiance scaling factor
		RGBColor 	m_ce;		// color

};



inline void
Emissive::SetCe(const RGBColor& c) 
{
    m_ce = c;
}


inline void
Emissive::SetCe(const float r, const float g, const float b) 
{
    m_ce.r = r; m_ce.g = g; m_ce.b = b;
}


inline void
Emissive::SetCe(const float c) 
{
	m_ce.Set(c, c, c);
}


inline RGBColor
Emissive::GetLe(ShadeContext& sr) const 
{
    return (m_ls * m_ce);
}


inline void
Emissive::SetRadianceScaler(const float s) 
{
    m_ls = s;
}


inline RGBColor 
Emissive::Shade(ShadeContext& sr) 
{
    return (BLACK);
}


inline RGBColor
Emissive::AreaLightShade(ShadeContext& sr) 
{
	if( -sr.normal * sr.ray.d > 0.0 )
		return (m_ls * ((NULL != m_pEmissive) ? m_pEmissive->GetColor(sr) : m_ce));
	else
		return (BLACK);
}


inline RGBColor
Emissive::PathShade(ShadeContext& sr) 
{
//	if( 1 == sr.depth )
//		return (BLACK);

	if( -sr.normal * sr.ray.d > 0.0 )
		return (m_ls * ((NULL != m_pEmissive) ? m_pEmissive->GetColor(sr) : m_ce));
	else
		return (BLACK);
}


#endif