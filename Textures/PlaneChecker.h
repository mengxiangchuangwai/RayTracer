//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __PLANE_CHECKER__
#define __PLANE_CHECKER__


#include "../Textures/Checker3D.h"

class PlaneChecker : public Checker3D
{
public:

    PlaneChecker(void);

    PlaneChecker(const PlaneChecker& other);

    PlaneChecker&
    operator= (const PlaneChecker& rhs);

    virtual PlaneChecker*
    Clone(void) const;

    virtual
    ~PlaneChecker(void);

    virtual RGBColor
    GetColor(const ShadeContext& sr) const;

    void
    SetOutlineColor(const RGBColor& c);

    void
    SetOutlineColor(const float r, const float g, const float b);

	void
    SetOutlineWidth(float val);


protected:

    RGBColor m_outlineColor;
	float	 m_outlineWidth;
};



inline void
PlaneChecker::SetOutlineColor(const RGBColor &c) 
{
    m_outlineColor = c;
}


inline void
PlaneChecker::SetOutlineColor(const float r, const float g, const float b) 
{
    m_outlineColor.r = r; m_outlineColor.g = g; m_outlineColor.b = b;
}


inline void
PlaneChecker::SetOutlineWidth(float val) 
{
    m_outlineWidth = val;
}


#endif