//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __PARTIAL_CONE__
#define __PARTIAL_CONE__


#include "../Objects/PartialCylinder.h"
#include "../Utilities/Maths.h"

class PartialCone : public PartialCylinder {
public:

    PartialCone(Material* mp = NULL);

    PartialCone(const double y0,
				const double y1,
				const double radius,
				const double azimuthMin,		// in degrees
				const double azimuthMax,		// in degrees
				Material* mp = NULL);

    PartialCone(const PartialCone& other);

    PartialCone& 
	operator= (const PartialCone& rhs);

    virtual PartialCone* 
	Clone(void) const;

    virtual bool 
	Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

    virtual 
	bool ShadowHit(const Ray& ray, double& tmin) const;
};


#endif