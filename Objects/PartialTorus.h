//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __PARTIAL_TORUS__
#define __PARTIAL_TORUS__


#include "../Objects/Torus.h"

class PartialTorus: public Torus {
	public:

		PartialTorus(Material* mp = NULL);

		PartialTorus(const double	a, 
					 const double	b, 
					 const double 	azimuthMin,		// in degrees
					 const double 	azimuthMax,		// in degrees
					 const double 	polarMin,		// in degrees measured counter clockwise from the (x, z) plane
					 const double 	polarMax,		// in degrees measured counter clockwise from the (x, z) plane
					 Material* mp = NULL);

		virtual PartialTorus*
		Clone(void) const;

		PartialTorus(const PartialTorus& other);

		virtual
		~PartialTorus(void);

		PartialTorus&
		operator= (const PartialTorus& rhs);

		virtual bool
		Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

		virtual bool 
		ShadowHit(const Ray& ray, double& tmin) const;


	protected:

		double 	m_phi1;			// minimum azimiuth angle in degrees measured counter clockwise from the +ve z axis
		double 	m_phi2;			// maximum azimiuth angle in degrees measured counter clockwise from the +ve z axis
		double 	m_theta1;		// minimum polar angle in degrees measured counter clockwise from the (x, z) plane
		double 	m_theta2;		// maximum polar angle in degrees measured counter clockwise from the (x, z) plane
};


#endif