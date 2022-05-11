//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __TRANSPARENT__
#define __TRANSPARENT__


#include "../BRDFs/PerfectSpecular.h"
#include "../BTDFs/PerfectTransmitter.h"
#include "../Materials/Phong.h"

class Transparent: public Phong {	
	public:
	
		Transparent(void);

		Transparent(const Transparent& other);

		virtual Transparent *
		Clone(void) const;

		Transparent&
		operator= (const Transparent& rhs);

		virtual 
		~Transparent(void);
	
		void
		SetKr(const float k);

		float
		GetKr(void) const;
	
		void													
		SetCr(const RGBColor& c);
		
		void
		SetCr(const float r, const float g, const float b);
		
		void
		SetCr(const float c);

		const RGBColor&
		GetCr(void) const;

		void
		SetKt(const float k);

		float
		GetKt(void) const;
	
		void													
		SetCt(const RGBColor& c);
		
		void
		SetCt(const float r, const float g, const float b);
		
		void
		SetCt(const float c);

		const RGBColor&
		GetCt(void) const;

		void
		SetIor(const float val);

		float
		GetIor(void) const;

		virtual RGBColor
		Shade(ShadeContext& sr);
	
		virtual RGBColor
		AreaLightShade(ShadeContext& sr);

		virtual RGBColor
		PathShade(ShadeContext& sr);

		virtual bool
		IsTransparent(void) const;

	
	private:
	
		RGBColor 
		Trace(ShadeContext& sr);

		PerfectSpecular 	m_reflector;
		PerfectTransmitter	m_transmitter;	
};



inline void
Transparent::SetKr(const float k) 
{
	m_reflector.SetCoeff(k);
}


inline float
Transparent::GetKr(void) const 
{
	return (m_reflector.GetCoeff());
}


inline void
Transparent::SetCr(const RGBColor& c) 
{
	m_reflector.SetColor(c);
	
}


inline void
Transparent::SetCr(const float r, const float g, const float b) 
{
	m_reflector.SetColor(r, g, b);
}


inline void
Transparent::SetCr(const float c) 
{
	m_reflector.SetColor(c);
}


inline const RGBColor&
Transparent::GetCr(void) const
{
	return (m_reflector.GetColor());
}


inline void
Transparent::SetKt(const float k) 
{
	m_transmitter.SetCoeff(k);
}


inline float
Transparent::GetKt(void) const 
{
	return (m_transmitter.GetCoeff());
}


inline void
Transparent::SetCt(const RGBColor& c) 
{
	m_transmitter.SetColor(c);
	
}


inline void
Transparent::SetCt(const float r, const float g, const float b) 
{
	m_transmitter.SetColor(r, g, b);
}


inline void
Transparent::SetCt(const float c) 
{
	m_transmitter.SetColor(c);
}


inline const RGBColor&
Transparent::GetCt(void) const  
{
	return (m_transmitter.GetColor());
}


inline void
Transparent::SetIor(const float val) 
{
	m_transmitter.SetIor(val);
}


inline float
Transparent::GetIor(void) const
{
	return (m_transmitter.GetIor());
}


inline RGBColor
Transparent::Shade(ShadeContext& sr) 
{	
	return (Phong::Shade(sr) + Trace(sr));
}


inline RGBColor
Transparent::AreaLightShade(ShadeContext& sr) 
{	
	return (Phong::AreaLightShade(sr) + Trace(sr));
}


inline RGBColor
Transparent::PathShade(ShadeContext& sr) 
{		
	RGBColor result(0.0);
	
	if( 0 == sr.depth )
		result = Phong::AreaLightShade(sr); 
	
	result += Trace(sr);
	return (result);
}


inline bool
Transparent::IsTransparent(void) const
{
	return (true);
}


#endif