//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __FISH_EYE__
#define __FISH_EYE__


#include "../Utilities/Point2D.h"
#include "../World/World.h"

class FishEye: public Camera {
	public:

		FishEye(void);

		FishEye(const FishEye& other);

		virtual FishEye*
		Clone(void) const;

		FishEye&
		operator= (const FishEye& rhs);

		virtual
		~FishEye(void);

		virtual void
		RenderRows(Sampler* pSampler, const World* pWorld, const int roff, const int nrows, const float xdelta = 0, const int coff = 0);

		void
		SetFov(const float fov);

		float
		GetFov(void) const;


	private:

		Vector3D
		GetRayDir(	const Point2D&	pp,
					const int 		hres,
					const int 		vres,
					const float		s,
					float& 			rsquared) const;

		float	m_psiMax;	// in degrees
};



inline void
FishEye::SetFov(const float fov)
{
    m_psiMax = fov / 2.0f;
}


inline float
FishEye::GetFov(void) const
{
	return (m_psiMax * 2);
}


#endif
