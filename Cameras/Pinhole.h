//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __PIN_HOLE__
#define __PIN_HOLE__


#include "../Utilities/Point2D.h"
#include "../World/World.h"

class Pinhole: public Camera {
	public:

		Pinhole(void);

		Pinhole(const Pinhole& other);

		virtual Pinhole*
		Clone(void) const;

		Pinhole&
		operator= (const Pinhole& rhs);

		virtual
		~Pinhole(void);

		void
		SetViewDistance(const float value);

		float
		GetViewDistance(void) const;

		void
		SetZoom(const float value);

		float
		GetZoom(void) const;

		virtual void
		RenderRows(Sampler* pSampler, const World* pWorld, const int roff, const int nrows, const float xdelta = 0, const int coff = 0);


	private:

		Vector3D
		GetRayDir(const Point2D& p) const;

		float	m_vpd;		// view plane distance
		float	m_zoom;

};




inline void
Pinhole::SetViewDistance(float value) 
{
	m_vpd = value;
}


inline float
Pinhole::GetViewDistance(void) const
{
	return (m_vpd);
}


inline void
Pinhole::SetZoom(float value) 
{
	m_zoom = value;
}


inline float
Pinhole::GetZoom(void) const
{
	return (m_zoom);
}


#endif