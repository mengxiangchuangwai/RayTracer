//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/Box.h"
#include "../Utilities/Maths.h"

Box::Box(Material* mp)
    : GeometricObject(mp)
    , m_p0(0)
    , m_p1(0)
    , m_dims(0)
{}


Box::Box(const Point3D& a, const Point3D& b, Material* mp)
    : GeometricObject(mp)
    , m_p0(a)
    , m_p1(b)
    , m_dims(m_p1.x - m_p0.x, m_p1.y - m_p0.y, m_p1.z - m_p0.z)
{}


Box::Box(const Box& other)
    : GeometricObject(other)
    , m_p0(other.m_p0)
    , m_p1(other.m_p1)
    , m_dims(other.m_dims)
{}


Box* Box::Clone(void) const 
{
    return (new Box(*this));
}


Box& Box::operator= (const Box& rhs) 
{
    if( this == &rhs )
        return (*this);

    GeometricObject::operator= (rhs);
    m_p0	= rhs.m_p0;
    m_p1	= rhs.m_p1;
    m_dims	= rhs.m_dims;

    return (*this);
}


void Box::UpdateBoundingBox(void) 
{
    double delta = 0.0001;
    m_bbox.p0 = Point3D(min2(m_p0.x, m_p1.x) - delta,
                     min2(m_p0.y, m_p1.y) - delta,
                     min2(m_p0.z, m_p1.z) - delta);
    m_bbox.p1 = Point3D(max2(m_p0.x, m_p1.x) + delta,
                     max2(m_p0.y, m_p1.y) + delta,
                     max2(m_p0.z, m_p1.z) + delta);
}


bool Box::Intersect(const Ray& ray, double& tval, ShadeContext* pSR) const 
{
	const Point3D& o = ray.o;
	double tmin[3], tmax[3];

    double a = 1.0 / ray.d.x;
    if( a >= 0 )
	{
        tmin[0] = (m_p0.x - o.x) * a;
        tmax[0] = (m_p1.x - o.x) * a;
    }
    else 
	{
        tmin[0] = (m_p1.x - o.x) * a;
        tmax[0] = (m_p0.x - o.x) * a;
    }

    double b = 1.0 / ray.d.y;
    if( b >= 0 ) 
	{
        tmin[1] = (m_p0.y - o.y) * b;
        tmax[1] = (m_p1.y - o.y) * b;
    }
    else 
	{
        tmin[1] = (m_p1.y - o.y) * b;
        tmax[1] = (m_p0.y - o.y) * b;
    }

    double c = 1.0 / ray.d.z;
    if( c >= 0 )
	{
        tmin[2] = (m_p0.z - o.z) * c;
        tmax[2] = (m_p1.z - o.z) * c;
    }
    else
	{
        tmin[2] = (m_p1.z - o.z) * c;
        tmax[2] = (m_p0.z - o.z) * c;
    }

    double t0, t1;
    int faceIn, faceOut;

    // finding largest
    if( tmin[0] > tmin[1] )
	{
        t0 = tmin[0];
        faceIn = (a >= 0.0) ? 0 : 3;
    }
    else
	{
        t0 = tmin[1];
        faceIn = (b >= 0.0) ? 1 : 4;
    }

    if( tmin[2] > t0 )
	{
        t0 = tmin[2];
        faceIn = (c >= 0.0) ? 2 : 5;
    }

    // find smallest
    if( tmax[0] < tmax[1] )
	{
        t1 = tmax[0]; 
        faceOut = (a >= 0.0) ? 3 : 0;
    }
    else
	{
        t1 = tmax[1];
        faceOut = (b >= 0.0) ? 4 : 1;
    }

    if( tmax[2] < t1 )
	{
        t1 = tmax[2];
        faceOut = (c >= 0.0) ? 5 : 2;
    }

    if( t0 < t1 && t1 > kEpsilon )
	{
        if( t0 > kEpsilon )
		{
            tval = t0;
            if( pSR )
			{
				pSR->normal = GetNormal(faceIn);

				if( m_reverseNormal )
					pSR->normal = -pSR->normal;
			}
        }
        else
		{
            tval = t1;
            if( pSR )
			{
				pSR->normal = GetNormal(faceOut);
			
				if( m_reverseNormal )
					pSR->normal = -pSR->normal;
			}
        }

        if( pSR ) 
			pSR->localHitPoint = ray.o + tval * ray.d;

        return true;
    }
	
	return false;
}


Normal Box::GetNormal(const int faceId) const 
{
    switch( faceId ) 
	{
        case 0: return (Normal(-1, 0, 0)); // -x face
        case 1: return (Normal(0, -1, 0)); // -y face
        case 2: return (Normal(0, 0, -1)); // -z face
        case 3: return (Normal(1, 0, 0));  // +x face
        case 4: return (Normal(0, 1, 0));  // +y face
        case 5: return (Normal(0, 0, 1));  // +z face
    }

	return Normal();
}