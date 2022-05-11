//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Cameras/Stereo.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Maths.h"
#include "../Samplers/Sampler.h"
#include "../World/ViewPlane.h"

Stereo::Stereo(void)
	: Camera()
	, m_viewingType(parallel)
	, m_imageGap(5)
	, m_stereoAngle(5.0f)
	, m_pLeftCamera(NULL)
	, m_pRightCamera(NULL)
{}


Stereo::Stereo(Camera* pLeftCamera, Camera* pRightCamera)
	: Camera()
	, m_viewingType(parallel)
	, m_imageGap(5)
	, m_stereoAngle(5.0f)
	, m_pLeftCamera(pLeftCamera)
	, m_pRightCamera(pRightCamera)
{
	if( pLeftCamera == pRightCamera )
		m_pRightCamera = pLeftCamera->Clone();
}


Stereo::Stereo(const Stereo& other)
	: 	Camera(other)
	,	m_viewingType(other.m_viewingType)
	,	m_imageGap(other.m_imageGap)
	,	m_stereoAngle(other.m_stereoAngle)
{
	if( other.m_pLeftCamera )
		m_pLeftCamera = other.m_pLeftCamera->Clone();
	else
		m_pLeftCamera = NULL;

	if( other.m_pRightCamera )
		m_pRightCamera = other.m_pRightCamera->Clone();
	else
		m_pRightCamera = NULL;
}


Stereo*
Stereo::Clone(void) const 
{
	return (new Stereo(*this));
}


Stereo&
Stereo::operator= (const Stereo& rhs) 
{
	if( this == &rhs )
		return (*this);

	Camera::operator= (rhs);

	m_viewingType = rhs.m_viewingType;
	m_imageGap = rhs.m_imageGap;
	m_stereoAngle = rhs.m_stereoAngle;

	if( m_pLeftCamera ) 
	{
		delete m_pLeftCamera;
		m_pLeftCamera = NULL;
	}

	if( rhs.m_pLeftCamera )
		m_pLeftCamera = rhs.m_pLeftCamera->Clone();

	if( m_pRightCamera ) 
	{
		delete m_pRightCamera;
		m_pRightCamera = NULL;
	}

	if( rhs.m_pRightCamera )
		m_pRightCamera = rhs.m_pRightCamera->Clone();

	return (*this);
}


Stereo::~Stereo(void) 
{
	if( m_pLeftCamera ) 
	{
		delete m_pLeftCamera;
		m_pLeftCamera = NULL;
	}

	if( m_pRightCamera ) 
	{
		delete m_pRightCamera;
		m_pRightCamera = NULL;
	}
}


void 
Stereo::SetCameras(Camera* pLeft, Camera* pRight) 
{
	if( pLeft == pRight )
		pRight = pLeft->Clone();

	if( m_pLeftCamera != pLeft )
	{
		if( m_pLeftCamera )
			delete m_pLeftCamera;
			
		m_pLeftCamera = pLeft;
	}

	if( m_pRightCamera != pRight )
	{
		if( m_pRightCamera )
			delete m_pRightCamera;
			
		m_pRightCamera = pRight;
	}
}


void
Stereo::SetupCameras(void) 
{
	double r = m_eye.Distance(m_lookat);
	double x = r * tan(0.5 * degreeToRadian(m_stereoAngle));  //  half the camera separation distance

	m_pLeftCamera->SetEye(m_eye - x * m_u);
	m_pLeftCamera->SetLookat(m_lookat - x * m_u);
	m_pLeftCamera->ComputeONB();

	m_pRightCamera->SetEye(m_eye + x * m_u);
	m_pRightCamera->SetLookat(m_lookat + x * m_u);
	m_pRightCamera->ComputeONB();
}


void
Stereo::RenderScene(const World& wr, const float xdelta /*= 0*/, const int coff /*= 0*/) 
{
	int hres	= wr.GetViewPlane().GetHres();
	int vres 	= wr.GetViewPlane().GetVres();

	double r	= m_eye.Distance(m_lookat);
	float xdiff = (float)(r * tan(0.5 * degreeToRadian(m_stereoAngle)));

	if( m_viewingType == parallel ) 
	{
		m_pLeftCamera->RenderScene(wr, xdiff, 0);						// left view on left
		m_pRightCamera->RenderScene(wr, -xdiff, hres + m_imageGap);		// right view on right
	}
	else
	{
		m_pRightCamera->RenderScene(wr, -xdiff, 0);   					// right view on left
		m_pLeftCamera->RenderScene(wr, xdiff, hres + m_imageGap);    	// left view on right
	}

	for( int i = 0; i < vres; ++i ) 
	{
		for( int j = hres; j < hres + m_imageGap; ++j )
			wr.SaveColor(i, j, WHITE);
	}
}