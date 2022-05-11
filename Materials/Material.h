//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __MATERIAL__
#define __MATERIAL__


#include "../World/World.h"			// required for the shade function in all derived classes
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeContext.h"
#include "../Samplers/Sampler.h"
#include "../Textures/Texture.h"

class Material {
	public:

		Material(void);

		Material(const Material& other);

		virtual Material*
		Clone(void) const = 0;

		virtual
		~Material(void);

		virtual RGBColor
		Shade(ShadeContext& sr);

		virtual RGBColor
		AreaLightShade(ShadeContext &sr);

		virtual RGBColor
		PathShade(ShadeContext& sr);

		virtual RGBColor
    	GetLe(ShadeContext& sr) const;

		virtual void
		SetSampler(Sampler* sp);

		virtual void
		SetupSampler(const int numSamples, const float exp = 1.0f, const SamplerType samplerType = ST_MultiJittered);

		void 
		SetAmbientTexture(Texture* tp);

		Texture*
		GetAmbientTexture(void) const;

		void 
		SetDiffuseTexture(Texture* tp);

		Texture* 
		GetDiffuseTexture(void) const;

		void 
		SetSpecularTexture(Texture* tp);

		Texture* 
		GetSpecularTexture(void) const;

		void 
		SetEmissiveTexture(Texture* tp);

		Texture* 
		GetEmissiveTexture(void) const;

		virtual bool
		IsTransparent(void) const;

		virtual Material*
		Release(void);

		virtual Material*
		AddRef(void);

		virtual int
		GetRef(void) const;


	protected:

		Material&
		operator= (const Material& rhs);

		Texture*		m_pDiffuse;
		Texture*		m_pSpecular;
		Texture*		m_pEmissive;
		bool			m_shadowing;

		CriticalSection	m_cs;
		RefCounter		m_counter;
};



inline void
Material::SetSampler(Sampler* sp)
{
}


inline void
Material::SetupSampler(const int numSamples, const float exp, const SamplerType samplerType)
{
}


inline Material*
Material::Release(void) 
{
	m_counter.Release();
	return this;
}


inline Material*
Material::AddRef(void) 
{
	m_counter.AddRef();
	return this;
}


inline int
Material::GetRef(void) const 
{
	return (m_counter.GetRef());
}


inline bool
Material::IsTransparent(void) const
{
	return (false);
}


#endif