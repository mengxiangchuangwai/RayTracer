//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __BBOX__
#define __BBOX__


#include "../Utilities/Ray.h"
#include "../Utilities/Constants.h"

class BBox {
public:

    BBox(void);

    BBox(const double x0, const double x1,
         const double y0, const double y1,
         const double z0, const double z1);

    BBox(const Point3D& a, const Point3D& b);

    BBox(const BBox& other);

    virtual BBox* 
	Clone(void) const;

    BBox& 
	operator= (const BBox& rhs);

    virtual 
	~BBox(void);

    virtual bool 
	Hit(const Ray& ray) const;

    virtual bool 
	Inside(const Point3D p) const;


public:

	Point3D		p0;
	Point3D		p1;
};


#endif