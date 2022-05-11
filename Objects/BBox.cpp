//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Utilities/Maths.h"
#include "../Objects/BBox.h"

BBox::BBox(void) 
{
    p0.x = -1, p1.x = 1, p0.y = -1, p1.y = 1, p0.z = -1, p1.z = 1;
}


BBox::BBox(const double x0, const double x1,
           const double y0, const double y1,
           const double z0, const double z1) 
{
    p0.x = x0, p1.x = x1, p0.y = y0, p1.y = y1, p0.z = z0, p1.z = z1;
}


BBox::BBox(const Point3D& a, const Point3D& b)
    : p0(a)
    , p1(b)
{}


BBox::BBox(const BBox& other)
    : p0(other.p0)
    , p1(other.p1)
{}


BBox* BBox::Clone(void) const 
{
    return (new BBox(*this));
}


BBox& BBox::operator= (const BBox& rhs) 
{
    if( this == &rhs )
        return *this;

    p0 = rhs.p0;
    p1 = rhs.p1;

    return *this;
}


BBox::~BBox(void)
{}


bool 
BBox::Hit(const Ray& ray) const 
{
    const Point3D& o = ray.o;
	double tmin[3], tmax[3];

    double a = 1.0 / ray.d.x;
    if( a >= 0 )
	{
        tmin[0] = (p0.x - o.x) * a;
        tmax[0] = (p1.x - o.x) * a;
    }
    else 
	{
        tmin[0] = (p1.x - o.x) * a;
        tmax[0] = (p0.x - o.x) * a;
    }

    double b = 1.0 / ray.d.y;
    if( b >= 0 ) 
	{
        tmin[1] = (p0.y - o.y) * b;
        tmax[1] = (p1.y - o.y) * b;
    }
    else 
	{
        tmin[1] = (p1.y - o.y) * b;
        tmax[1] = (p0.y - o.y) * b;
    }

    double c = 1.0 / ray.d.z;
    if( c >= 0 )
	{
        tmin[2] = (p0.z - o.z) * c;
        tmax[2] = (p1.z - o.z) * c;
    }
    else
	{
        tmin[2] = (p1.z - o.z) * c;
        tmax[2] = (p0.z - o.z) * c;
    }
	
    double t0 = max3(tmin[0], tmin[1], tmin[2]);	// find largest
	double t1 = min3(tmax[0], tmax[1], tmax[2]);	// find smallest
  
    return (t0 < t1 && t1 > kEpsilon);
}


bool 
BBox::Inside(const Point3D p) const 
{
    return ((p.x > p0.x && p.x < p1.x)
         && (p.y > p0.y && p.y < p1.y)
         && (p.z > p0.z && p.z < p1.z));
}