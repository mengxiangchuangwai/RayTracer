//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/Cylinder.h"

Cylinder::Cylinder(Material* mp)
    : Compound(mp) 
{
    m_pTop		= new Disk(Point3D(0, 1, 0), Normal(0, 1, 0), 1);
    m_pSide		= new OpenCylinder(0, 1, 1);
    m_pBottom	= new Disk(Point3D(0, 0, 0), Normal(0, -1, 0), 1);
    AddObject(m_pTop);
    AddObject(m_pSide);
    AddObject(m_pBottom);
    UpdateBoundingBox();
}


Cylinder::Cylinder(const double y0, const double y1, const double radius, Material* mp)
    : Compound(mp) 
{
    m_pTop		= new Disk(Point3D(0, y1, 0), Normal(0, 1, 0), radius);
    m_pSide		= new OpenCylinder(y0, y1, radius);
    m_pBottom	= new Disk(Point3D(0, y0, 0), Normal(0, -1, 0), radius);
    AddObject(m_pTop);
    AddObject(m_pSide);
    AddObject(m_pBottom);
    UpdateBoundingBox();
}


Cylinder::Cylinder(const Cylinder& other)
	: Compound(other) 
{
	if( other.m_objects.size() >= 3 ) 
	{
		m_pTop		= (Disk*)other.m_objects[0];
		m_pSide		= (OpenCylinder*)other.m_objects[1];
		m_pBottom	= (Disk*)other.m_objects[2];
	}
	else 
	{
		m_pTop		= NULL;
		m_pSide		= NULL;
		m_pBottom	= NULL;
	}
}


Cylinder* 
Cylinder::Clone(void) const 
{
    return (new Cylinder(*this));
}


Cylinder& 
Cylinder::operator= (const Cylinder& rhs) 
{
    if( this == &rhs )
        return (*this);
  
    DeleteObjects();
    Compound::operator= (rhs);

    if( rhs.m_objects.size() >= 3 ) 
	{
		m_pTop		= (Disk*)rhs.m_objects[0];
		m_pSide		= (OpenCylinder*)rhs.m_objects[1];
		m_pBottom	= (Disk*)rhs.m_objects[2];
	}
	else 
	{
		m_pTop		= NULL;
		m_pSide		= NULL;
		m_pBottom	= NULL;
	}

    return (*this);
}


void 
Cylinder::UpdateBoundingBox(void) 
{
    Point3D center(0, m_pSide->GetY0(), 0);
    float radius = m_pSide->GetRadius();
    m_bbox.p0 = Point3D(center.x - radius, center.y, center.z - radius);
    m_bbox.p1 = Point3D(center.x + radius, m_pSide->GetY1(), center.z + radius);
}