//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __PARTIAL_CYLINDER__
#define __PARTIAL_CYLINDER__


#include "../Objects/GeometricObject.h"
#include "../Utilities/Maths.h"

class PartialCylinder : public GeometricObject {
public:

    PartialCylinder(Material* mp = NULL);

    PartialCylinder(const double y0, 
					const double y1, 
					const double radius, 
					const double azimuthMin,		// in degrees
					const double azimuthMax,		// in degrees
					Material* mp = NULL);

    PartialCylinder(const PartialCylinder& other);

    PartialCylinder& 
	operator= (const PartialCylinder& rhs);

    virtual PartialCylinder* 
	Clone(void) const;

    virtual void 
	UpdateBoundingBox();

    virtual bool 
	Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

    virtual 
	bool ShadowHit(const Ray& ray, double& tmin) const;

    void 
	SetY0(const double val);
    
	double 
	GetY0(void) const;

    void 
	SetY1(const double val);
    
	double 
	GetY1(void) const;

    void 
	SetRadius(const double val);
    
	double 
	GetRadius(void) const;

	void 
	SetMinAzimuth(const double val);
    
	double 
	GetMinAzimuth(void) const;

	void 
	SetMaxAzimuth(const double val);
    
	double 
	GetMaxAzimuth(void) const;


protected:

    double m_y0;
    double m_y1;
    double m_radius;
	double m_phi1;
	double m_phi2;
};



inline void 
PartialCylinder::SetY0(const double val) 
{
    m_y0 = val;
}


inline double 
PartialCylinder::GetY0(void) const 
{
    return (m_y0);
}


inline void 
PartialCylinder::SetY1(const double val) 
{
    m_y1 = val;
}


inline double 
PartialCylinder::GetY1(void) const 
{
    return (m_y1);
}


inline void 
PartialCylinder::SetRadius(const double val) 
{
    m_radius = val;
}


inline double 
PartialCylinder::GetRadius(void) const 
{
    return (m_radius);
}


inline void 
PartialCylinder::SetMinAzimuth(const double val) 
{
	m_phi1 = degreeToRadian(val);
}


inline double 
PartialCylinder::GetMinAzimuth(void) const 
{
	return (radianToDegree(m_phi1));
}


inline void 
PartialCylinder::SetMaxAzimuth(const double val) 
{
	m_phi2 = degreeToRadian(val);
}


inline double 
PartialCylinder::GetMaxAzimuth(void) const 
{
	return (radianToDegree(m_phi2));
}


#endif