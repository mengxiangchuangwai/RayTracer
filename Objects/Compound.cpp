//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/Compound.h"

Compound::Compound(Material* mp)
    : GeometricObject(mp)
    , m_pLocalMaterial(NULL)
{}


Compound::Compound(const Compound& other)
    : GeometricObject(other)
    , m_pLocalMaterial(NULL)
{
    m_objects.reserve(other.m_objects.size());

    for( size_t i = 0; i < other.m_objects.size(); ++i )
		AddObject(other.m_objects[i]->Clone());
}


Compound& 
Compound::operator= (const Compound& rhs) 
{
    if( this == &rhs )
        return (*this);

    GeometricObject::operator= (rhs);
    m_pLocalMaterial = NULL;
    DeleteObjects();
    m_objects.reserve(rhs.m_objects.size());

    for( size_t i = 0; i < rhs.m_objects.size(); ++i )
		AddObject(rhs.m_objects[i]->Clone());

	return (*this);
}


Compound* 
Compound::Clone(void) const 
{
    return (new Compound(*this));
}


Compound::~Compound(void) 
{
    DeleteObjects();
}


void Compound::AddObject(GeometricObject* op) 
{
    if( NULL != op )
        m_objects.push_back(op);
}


void Compound::DeleteObjects(void) 
{
    for( size_t i = 0; i < m_objects.size(); ++i )
		SAFE_DELETE(m_objects[i]);

    m_objects.clear();
}


void 
Compound::UpdateBoundingBox(void) 
{
    BBox obb;
	Point3D& p0 = m_bbox.p0;
	Point3D& p1 = m_bbox.p1;
	p0 = Point3D(kHugeValue);
	p1 = Point3D(-kHugeValue);
	
	size_t num	= m_objects.size();
    
	for( size_t i = 0; i < num; ++i )
	{   
        m_objects[i]->UpdateBoundingBox();
        m_objects[i]->GetBoundingBox(obb);
        
		if( obb.p0.x < p0.x )
            p0.x = obb.p0.x;
      
        if( obb.p0.y < p0.y )
            p0.y = obb.p0.y;
     
        if( obb.p0.z < p0.z )
            p0.z = obb.p0.z;


		if( obb.p1.x > p1.x )
            p1.x = obb.p1.x;
       
        if( obb.p1.y > p1.y )
            p1.y = obb.p1.y;
        
        if( obb.p1.z > p1.z )
            p1.z = obb.p1.z;
    }

    p0.x -= kEpsilon;
    p0.y -= kEpsilon;
    p0.z -= kEpsilon;
    p1.x += kEpsilon;
    p1.y += kEpsilon;
    p1.z += kEpsilon;
}


bool Compound::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
    Normal		normal;
    Point3D		localHitPoint;
	double		tv;
	Material*	pMaterial = NULL;
    bool		hit = false;
    size_t		num = m_objects.size();
    tmin = kHugeValue;

    for( size_t i = 0; i < num; ++i ) 
	{
		sr.pMaterial = NULL;
        if( m_objects[i]->Hit(ray, tv, sr) && (tv < tmin) ) 
		{
            hit = true;
            tmin = tv;
            pMaterial = (NULL == sr.pMaterial ? m_objects[i]->GetMaterial() : sr.pMaterial);
            normal = sr.normal;
            localHitPoint = sr.localHitPoint;
        }
    }

    if( hit ) 
	{
        sr.normal = normal;
        sr.localHitPoint = localHitPoint;
		sr.pMaterial = m_pLocalMaterial = pMaterial;
    }

    return (hit);
}


bool Compound::ShadowHit(const Ray& ray, double& tmin) const 
{
    if( !m_shadowing )
		return (false);

    size_t num = m_objects.size();

    for( size_t i = 0; i < num; ++i ) 
	{
        if( m_objects[i]->ShadowHit(ray, tmin) )
            return (true);
    }

    return (false);
}