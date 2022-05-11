//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Textures/ConstantColor.h"

ConstantColor::ConstantColor(void)
    : Texture()
{}


ConstantColor::ConstantColor(const ConstantColor& other)
    : Texture(other)
{}


ConstantColor&
ConstantColor::operator= (const ConstantColor& rhs) 
{
    if( this == &rhs )
        return (*this);

    Texture::operator= (rhs);
    m_color = rhs.m_color;

    return (*this);
}


ConstantColor*
ConstantColor::Clone(void) const 
{
    return (new ConstantColor(*this));
}


ConstantColor::~ConstantColor(void) 
{}