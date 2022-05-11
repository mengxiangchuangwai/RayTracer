//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __CONSTANT_COLOR__
#define __CONSTANT_COLOR__


#include "../Textures/Texture.h"

class ConstantColor : public Texture
{
    public:

        ConstantColor(void);

        ConstantColor(const ConstantColor& other);

        ConstantColor& 
		operator= (const ConstantColor& rhs);

        virtual ConstantColor*
        Clone(void) const;

        virtual 
		~ConstantColor(void);

        virtual RGBColor
        GetColor(const ShadeContext& sr) const;

        void 
		SetColor(const RGBColor& c);


    private:

        RGBColor m_color;
};



inline RGBColor
ConstantColor::GetColor(const ShadeContext& sr) const 
{ 
	return (m_color); 
}


inline void 
ConstantColor::SetColor(const RGBColor& c) 
{ 
	m_color = c; 
}


#endif // __CONSTANTCOLOR__

