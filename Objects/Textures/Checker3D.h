//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __CHECKER3D__
#define __CHECKER3D__


#include "../Textures/Texture.h"

class Checker3D : public Texture
{
public:

    Checker3D(void);

    Checker3D(const Checker3D& other);

    Checker3D&
    operator= (const Checker3D& rhs);

    virtual Checker3D*
    Clone(void) const;

    virtual
    ~Checker3D(void);

    virtual RGBColor
    GetColor(const ShadeContext& sr) const;

    void
    SetSize(const float s);

    void
    SetColor1(const RGBColor& c);

    void
    SetColor1(const float r, const float g, const float b);

    void
    SetColor2(const RGBColor& c);

    void
    SetColor2(const float r, const float g, const float b);


protected:

    RGBColor	m_color1;
    RGBColor	m_color2;
    float		m_size;
};



inline void
Checker3D::SetSize(const float s) 
{
    m_size = s;
}


inline void
Checker3D::SetColor1(const RGBColor &c) 
{
    m_color1 = c;
}


inline void
Checker3D::SetColor1(const float r, const float g, const float b) 
{
    m_color1.r = r; m_color1.g = g; m_color1.b = b;
}


inline void
Checker3D::SetColor2(const RGBColor &c) 
{
    m_color2 = c;
}


inline void
Checker3D::SetColor2(const float r, const float g, const float b) 
{
    m_color2.r = r; m_color2.g = g; m_color2.b = b;
}


#endif