//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Textures/Texture.h"

Texture::Texture(void)
{}


Texture::Texture(const Texture& other)
{}


Texture&
Texture::operator= (const Texture& rhs) 
{
	if( this == &rhs )
		return (*this);

	return (*this);
}


Texture::~Texture(void) 
{}