//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __TEXTURE__
#define __TEXTURE__


#include <cmath>
#include "../Utilities/RefCounter.h"
#include "../Utilities/ShadeContext.h"
#include "../Utilities/RGBColor.h"

class Texture {
	public:

		Texture(void);

		Texture(const Texture& other);

		virtual Texture*
		Clone(void) const = 0;

		virtual
		~Texture(void);

		virtual RGBColor
		GetColor(const ShadeContext& sr) const = 0;

		virtual Texture*
		Release(void);

		virtual Texture*
		AddRef(void);

		virtual int
		GetRef(void) const;



	protected:

		Texture&
		operator= (const Texture& rhs);

		RefCounter	m_counter;
};



inline Texture*
Texture::Release(void) 
{
	m_counter.Release();
	return this;
}


inline Texture*
Texture::AddRef(void) 
{
	m_counter.AddRef();
	return this;
}


inline int
Texture::GetRef(void) const 
{
	return (m_counter.GetRef());
}


#endif