//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __DIELECTRIC__
#define __DIELECTRIC__


#include "../BRDFs/FresnelReflector.h"
#include "../BTDFs/PerfectTransmitter.h"
#include "../Materials/Phong.h"
#include "../Utilities/Lock.h"

typedef PerfectTransmitter FresnelTransmitter;

class Dielectric: public Phong {	
	public:
	
		Dielectric(void);

		Dielectric(const Dielectric& other);

		virtual Dielectric *
		Clone(void) const;

		Dielectric&
		operator= (const Dielectric& rhs);

		virtual 
		~Dielectric(void);
	
		void													
		SetCr(const RGBColor& c);
		
		void
		SetCr(const float r, const float g, const float b);
		
		void
		SetCr(const float c);

		const RGBColor&
		GetCr(void) const;
	
		void													
		SetCt(const RGBColor& c);
		
		void
		SetCt(const float r, const float g, const float b);
		
		void
		SetCt(const float c);

		const RGBColor&
		GetCt(void) const;

		void 
		SetFilteringColors(const RGBColor& colorIn, const RGBColor& colorOut);

		void 
		SetRefractionIndices(const float etaIn, const float etaOut);

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

		RGBColor 			m_filterIn;		// interior filter color 
		RGBColor 			m_filterOut;	// exterior filter color
		
		FresnelReflector	m_reflector;
		FresnelTransmitter	m_transmitter;
};



inline void
Dielectric::SetCr(const RGBColor& c) 
{
	m_reflector.SetColor(c);
	
}


inline void
Dielectric::SetCr(const float r, const float g, const float b) 
{
	m_reflector.SetColor(r, g, b);
}


inline void
Dielectric::SetCr(const float c) 
{
	m_reflector.SetColor(c);
}


inline const RGBColor&
Dielectric::GetCr(void) const
{
	return (m_reflector.GetColor());
}


inline void
Dielectric::SetCt(const RGBColor& c) 
{
	m_transmitter.SetColor(c);
}


inline void
Dielectric::SetCt(const float r, const float g, const float b) 
{
	m_transmitter.SetColor(r, g, b);
}


inline void
Dielectric::SetCt(const float c) 
{
	m_transmitter.SetColor(c);
}


inline const RGBColor&
Dielectric::GetCt(void) const
{
	return (m_transmitter.GetColor());
}


inline void 
Dielectric::SetFilteringColors(const RGBColor& colorIn, const RGBColor& colorOut) 
{
	m_filterIn	= colorIn;
	m_filterOut	= colorOut;
}


inline void 
Dielectric::SetRefractionIndices(const float etaIn, const float etaOut) 
{
	m_reflector.SetRefractionIndices(etaIn, etaOut);
	m_transmitter.SetIor(etaIn / etaOut);
}


inline RGBColor
Dielectric::Shade(ShadeContext& sr) 
{	
	return (Phong::Shade(sr) + Trace(sr));
}


inline RGBColor
Dielectric::AreaLightShade(ShadeContext& sr) 
{	
	return (Phong::AreaLightShade(sr) + Trace(sr));
}


inline RGBColor
Dielectric::PathShade(ShadeContext& sr) 
{
	RGBColor result(0.0);
	
	if( 0 == sr.depth )
		result = Phong::AreaLightShade(sr); 
	
	result += Trace(sr);
	return (result);
}


inline bool
Dielectric::IsTransparent(void) const
{
	return (true);
}


#endif