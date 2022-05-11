//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __PARTIAL_SPHERE__
#define __PARTIAL_SPHERE__


#include "../Objects/GeometricObject.h"

class PartialSphere: public GeometricObject {
	public:

		PartialSphere(Material* mp = NULL);

		PartialSphere(	const Point3D 	center,
						const double 	radius,
						const double 	azimuthMin,		// in degrees
						const double 	azimuthMax,		// in degrees
						const double 	polarMin,		// in degrees measured from top
						const double 	polarMax,		// in degrees measured from top
						Material* mp = NULL);

		PartialSphere(const Point3D center, const double radius, Material* mp = NULL);

		virtual PartialSphere*
		Clone(void) const;

		PartialSphere(const PartialSphere& other);

		virtual
		~PartialSphere(void);

		PartialSphere&
		operator= (const PartialSphere& rhs);

		virtual void
		UpdateBoundingBox(void);

		virtual bool
		Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

		virtual bool
		ShadowHit(const Ray& ray, double& tmin) const;


    protected:

		bool
		Intersect(const Ray& ray, double& tval, ShadeContext* pContext = NULL) const;

		Point3D		m_center;   	// center coordinates
		double 		m_radius;		// sphere radius
		double 		m_phi1;			// minimum azimiuth angle in degrees measured counter clockwise from the +ve z axis
		double 		m_phi2;			// maximum azimiuth angle in degrees measured counter clockwise from the +ve z axis
		double 		m_theta1;		// minimum polar angle in degrees measured down from the +ve y axis
		double 		m_theta2;		// maximum polar angle in degrees measured down from the +ve y axis

		double		m_cosTheta1;	// stored to avoid repeated calculations
		double		m_cosTheta2;	// stored to avoid repeated calculations
};



inline bool
PartialSphere::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const
{
	return (Intersect(ray, tmin, &sr));
}


inline bool
PartialSphere::ShadowHit(const Ray& ray, double& tmin) const
{
	if( !m_shadowing )
		return (false);

	return (Intersect(ray, tmin));
}


#endif