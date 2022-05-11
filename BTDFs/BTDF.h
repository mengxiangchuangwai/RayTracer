//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __BTDF__
#define __BTDF__


#include <cmath>

#include "../Textures/Texture.h"
#include "../Utilities/Constants.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/ShadeContext.h"

class BTDF {
	public:
	
		BTDF(void);
		
		BTDF(const BTDF& other);
		
		virtual BTDF*
		Clone(void) = 0;
		
		BTDF&							
		operator= (const BTDF& rhs);
		
		virtual
		~BTDF(void);
		
		virtual RGBColor
		Rho(const ShadeContext& sr, const Vector3D& wo) const;

		virtual RGBColor
		Rho(const Texture* tp, const ShadeContext& sr, const Vector3D& wo) const;

		virtual RGBColor
		Sample(const ShadeContext& sr, const Vector3D& wo, Vector3D& wt) const;

		virtual RGBColor
		Sample(const Texture* tp, const ShadeContext& sr, const Vector3D& wo, Vector3D& wt) const;

		virtual void
		SetColor(const RGBColor& c);

		virtual void													
		SetColor(const float r, const float g, const float b);
		
		virtual void													
		SetColor(const float c);

		virtual const RGBColor&
		GetColor(void) const;

		virtual void
		SetCoeff(const float coeff);

		virtual float
		GetCoeff(void) const;


	protected:
		
		RGBColor	m_color;
		float		m_coeff;
};



inline void
BTDF::SetColor(const RGBColor& c) 
{
	m_color = c;
}


inline void
BTDF::SetColor(const float r, const float g, const float b) 
{
	m_color.Set(r, g, b);
}
		

inline void													
BTDF::SetColor(const float c) 
{
	m_color.Set(c, c, c);
}


inline const RGBColor&
BTDF::GetColor(void) const 
{
	return (m_color);
}


inline void
BTDF::SetCoeff(const float coeff) 
{
	m_coeff = coeff;
}


inline float
BTDF::GetCoeff(void) const 
{
	return m_coeff;
}


#endif