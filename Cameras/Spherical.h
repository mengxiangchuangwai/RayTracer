//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __SPHERICAL__
#define __SPHERICAL__


#include "../Utilities/Point2D.h"
#include "../World/World.h"

class Spherical: public Camera {
	public:

		Spherical(void);

		Spherical(const Spherical& other);

		virtual Spherical*
		Clone(void) const;

		Spherical&
		operator= (const Spherical& rhs);

		virtual
		~Spherical(void);

		virtual void
		RenderRows(Sampler* pSampler, const World* pWorld, const int roff, const int nrows, const float xdelta = 0, const int coff = 0);

		void
		SetHorizontalFov(const float value);

		float
		GetHorizontalFov(void) const;

		void
		SetVerticalFov(const float value);

		float
		GetVerticalFov(void) const;


	private:

		Vector3D
		GetRayDir(	const Point2D& pp,
					const int 	hres,
					const int 	vres,
					const float s) const;


		float   m_lambdaMax;	// in degrees
		float	m_psiMax;		// in degrees
};



inline void
Spherical::SetHorizontalFov(const float value)
{
    m_lambdaMax = value / 2.0f;
}


inline float
Spherical::GetHorizontalFov(void) const
{
	return (m_lambdaMax * 2);
}


inline void
Spherical::SetVerticalFov(const float value)
{
	m_psiMax = value / 2.0f;
}


inline float
Spherical::GetVerticalFov(void) const
{
	return (m_psiMax * 2);
}


#endif
