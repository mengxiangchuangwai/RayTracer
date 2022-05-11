//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/Cone.h"

Cone::Cone(Material* mp)
    : Compound(mp) 
{
    m_pSide		= new OpenCone(0, 1, 1);
    m_pBottom	= new Disk(Point3D(0, 0, 0), Normal(0, -1, 0), 1);
    AddObject(m_pSide);
    AddObject(m_pBottom);
    UpdateBoundingBox();
}


Cone::Cone(const double y0, const double y1, const double radius, Material* mp)
    : Compound(mp) 
{
    m_pSide		= new OpenCone(y0, y1, radius);
    m_pBottom	= new Disk(Point3D(0, y0, 0), Normal(0, -1, 0), radius);
    AddObject(m_pSide);
    AddObject(m_pBottom);
    UpdateBoundingBox();
}


Cone::Cone(const Cone& other)
	: Compound(other) 
{
	if( other.m_objects.size() >= 2 ) 
	{
		m_pSide		= (OpenCone*)other.m_objects[0];
		m_pBottom	= (Disk*)other.m_objects[1];
	}
	else 
	{
		m_pSide		= NULL;
		m_pBottom	= NULL;
	}
}


Cone* 
Cone::Clone(void) const 
{
    return (new Cone(*this));
}


Cone& 
Cone::operator= (const Cone& rhs) 
{
    if( this == &rhs )
        return (*this);
  
    DeleteObjects();
    Compound::operator= (rhs);

    if( rhs.m_objects.size() >= 2 ) 
	{
		m_pSide		= (OpenCone*)rhs.m_objects[0];
		m_pBottom	= (Disk*)rhs.m_objects[1];
	}
	else 
	{
		m_pSide		= NULL;
		m_pBottom	= NULL;
	}

    return (*this);
}


void 
Cone::UpdateBoundingBox(void) 
{
    Point3D center(0, m_pSide->GetY0(), 0);
    float radius = m_pSide->GetRadius();
    m_bbox.p0 = Point3D(center.x - radius, center.y, center.z - radius);
    m_bbox.p1 = Point3D(center.x + radius, m_pSide->GetY1(), center.z + radius);
}