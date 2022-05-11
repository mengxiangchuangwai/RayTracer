//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __DISK_EMITTER__
#define __DISK_EMITTER__


#include "../Objects/Disk.h"
#include "../Samplers/Sampler.h"

class DiskEmitter : public Disk {
public:

    DiskEmitter(Material* mp = NULL);

    DiskEmitter(const Point3D& center, const Normal& normal, const double radius, Material* mp = NULL);

    DiskEmitter(const DiskEmitter& other);

    DiskEmitter& 
	operator= (const DiskEmitter& rhs);

    virtual DiskEmitter* 
	Clone(void) const;

	virtual 
	~DiskEmitter(void);

    virtual void 
	SetNormal(const Normal& val);

	virtual void
	SetSampler(Sampler* sampler);

	virtual Point3D
	Sample(void);

	virtual Normal
	GetNormal(const Point3D& pt) const;

	virtual float
	Pdf(const ShadeContext& sr, const Vector3D& wi);


protected:

	Vector3D	m_u, m_v, m_w;
    Sampler*	m_pSampler;
};



inline void 
DiskEmitter::SetNormal(const Normal& val) 
{
	m_normal = val;
	m_w = m_normal;
	m_v = m_w ^ Vector3D(0.0072, 1.0, 0.0034); // jitter the up vector in case normal is vertical
	m_v.Normalize();
	m_u = m_v ^ m_w;
}


inline void
DiskEmitter::SetSampler(Sampler* sampler) 
{ 
   SAFE_DELETE(m_pSampler);

	if( m_pSampler = sampler )
		m_pSampler->SamplesToUnitDisk();
}


inline Point3D
DiskEmitter::Sample(void) 
{
	Point2D samplePoint = m_pSampler->SampleUnitDisk();
	return (Point3D(m_center + m_u * samplePoint.x + m_v * samplePoint.y));
}


inline Normal 
DiskEmitter::GetNormal(const Point3D& pt) const 
{
   return (m_normal);
}


inline float
DiskEmitter::Pdf(const ShadeContext& sr, const Vector3D& wi) 
{
	return (float)(1.0 / (PI * m_radius * m_radius));
}


#endif