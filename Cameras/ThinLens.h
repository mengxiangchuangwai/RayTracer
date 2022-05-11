//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __THIN_LENS__
#define __THIN_LENS__


#include "../Utilities/Point2D.h"
#include "../World/World.h"

class ThinLens: public Camera {

	public:

		ThinLens(void);

		ThinLens(const ThinLens& other);

		virtual ThinLens*
		Clone(void) const;

		ThinLens&
		operator= (const ThinLens& rhs);

		virtual
		~ThinLens(void);

		void
		SetSampler(Sampler* sp);

		virtual void
		RenderRows(Sampler* pSampler, const World* pWorld, const int roff, const int nrows, const float xdelta = 0, const int coff = 0);

		void
		SetViewDistance(const float value);

		float
		GetViewDistance(void) const;

		void
		SetFocalDistance(const float value);

		float
		GetFocalDistance(void) const;

		void
		SetLensRadius(const float value);

		float
		GetLensRadius(void) const;


	private:

		Vector3D
		GetRayDir(const Point2D& pixelPoint, const Point2D& lensPoint) const;

		float		m_lensRadius;	// lens radius
		float		m_viewDist;		// view plane distance
		float		m_focalDist;	// focal distance
		float		m_zoom;			// zoom factor
		Sampler*	m_pSampler;		// sampler object
};



inline void
ThinLens::SetViewDistance(const float value) 
{
	m_viewDist = value;
}


inline float
ThinLens::GetViewDistance(void) const
{
	return (m_viewDist);
}


inline void
ThinLens::SetFocalDistance(const float value) 
{
	m_focalDist = value;
}


inline float
ThinLens::GetFocalDistance(void) const
{
	return (m_focalDist);
}


inline void
ThinLens::SetLensRadius(const float value) 
{
	m_lensRadius = value;
}


inline float
ThinLens::GetLensRadius(void) const
{
	return (m_lensRadius);
}


#endif