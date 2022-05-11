//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __STEREO__
#define __STEREO__


typedef enum {
	parallel,
	transverse
} StereoViewType;

#include "../Utilities/Point2D.h"
#include "../World/World.h"

class Stereo: public Camera {
	public:

		Stereo(void);

		Stereo(Camera* pLeftCamera, Camera* pRightCamera);

		Stereo(const Stereo& other);

		virtual Stereo*
		Clone(void) const;

		Stereo&
		operator= (const Stereo& rhs);

		virtual
		~Stereo(void);

		void 
		SetCameras(Camera* pLeft, Camera* pRight);
		
		void
		SetupCameras(void);

		virtual void
		RenderScene(const World& wr, const float xdelta = 0, const int coff = 0);

		void
		UseParallelViewing(void);

		bool
		IsParallelViewing(void) const;

		void
		UseTransverseViewing(void);

		void
		SetPixelGap(const int gap);

		int
		GetPixelGap(void) const;

		void
		SetStereoAngle(const float angle);

		float
		GetStereoAngle(void) const;


	private:

		StereoViewType	m_viewingType;		// parallel or transverse viewing
		int				m_imageGap;			// gap in pixels between the left and right images
		float			m_stereoAngle;		// stereo separation angle
		Camera*			m_pLeftCamera;		// left eye camera
		Camera*			m_pRightCamera;		// right eye camera
};



inline void
Stereo::UseParallelViewing(void) 
{
	m_viewingType = parallel;
}


inline void
Stereo::UseTransverseViewing(void) 
{
	m_viewingType = transverse;
}


inline bool
Stereo::IsParallelViewing(void) const
{
	return (m_viewingType == parallel);
}


inline void
Stereo::SetPixelGap(int gap) 
{
	m_imageGap = gap;
}


inline int
Stereo::GetPixelGap(void) const
{
	return (m_imageGap);
}


inline void
Stereo::SetStereoAngle(float angle) 
{
	m_stereoAngle = angle;
}


inline float
Stereo::GetStereoAngle(void) const
{
	return (m_stereoAngle);
}


#endif // __STEREO__