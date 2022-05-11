//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __OPEN_CONE__
#define __OPEN_CONE__


#include "../Objects/OpenCylinder.h"
#include "../Utilities/Maths.h"

class OpenCone : public OpenCylinder {
public:

    OpenCone(Material* mp = NULL);

    OpenCone(const double y0, const double y1, const double radius, Material* mp = NULL);

    OpenCone(const OpenCone& other);

    OpenCone& 
	operator= (const OpenCone& rhs);

    virtual OpenCone* 
	Clone(void) const;

    virtual bool 
	Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

    virtual bool 
	ShadowHit(const Ray& ray, double& tmin) const;
};


#endif