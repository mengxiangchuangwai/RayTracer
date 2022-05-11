//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Cameras/ThinLens.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Samplers/Sampler.h"

ThinLens::ThinLens(void)
	: Camera()
	, m_viewDist(500)
	, m_zoom(1.0)
	, m_pSampler(NULL)
{}


ThinLens::ThinLens(const ThinLens& other)
	: Camera(other)
	, m_lensRadius(other.m_lensRadius)
	, m_viewDist(other.m_viewDist)
	, m_focalDist(other.m_focalDist)
	, m_zoom(other.m_zoom)
{
	if (other.m_pSampler)
		m_pSampler = other.m_pSampler->Clone();
	else
		m_pSampler = NULL;
}


ThinLens*
ThinLens::Clone(void) const 
{
	return (new ThinLens(*this));
}


ThinLens&
ThinLens::operator= (const ThinLens& rhs) 
{
	if( this == &rhs )
		return (*this);

	Camera::operator= (rhs);

	m_lensRadius	= rhs.m_lensRadius;
	m_viewDist		= rhs.m_viewDist;
	m_focalDist		= rhs.m_focalDist;
	m_zoom			= rhs.m_zoom;

	if( m_pSampler )
		delete m_pSampler;

	if( rhs.m_pSampler )
		m_pSampler = rhs.m_pSampler->Clone();
	else
		m_pSampler = NULL;

	return (*this);
}


ThinLens::~ThinLens(void) 
{
	SAFE_DELETE(m_pSampler);
}


void
ThinLens::SetSampler(Sampler* sp) 
{
	SAFE_DELETE(m_pSampler);

	if( m_pSampler = sp )
		m_pSampler->SamplesToUnitDisk();
}


Vector3D
ThinLens::GetRayDir(const Point2D& pixelPoint, const Point2D& lensPoint) const 
{
	Point2D p(pixelPoint.x * m_focalDist / m_viewDist, pixelPoint.y * m_focalDist / m_viewDist);   // hit point on focal plane
	Vector3D dir = (p.x - lensPoint.x) * m_u + (p.y - lensPoint.y) * m_v - m_focalDist * m_w;
	dir.Normalize();

	return (dir);
}


void
ThinLens::RenderRows(Sampler* pSampler, const World* pWorld, const int roff, const int num, const float xdelta, const int coff)
{
	const ViewPlane& vp = pWorld->GetViewPlane();
	float		s = vp.GetPixelSize() / m_zoom;
	float		invNumSamples = 1.0f / (float)(vp.GetNumSamples());
	int			rend = roff + num;
	int			cursor = 0;
	int 		depth = 0;
	RGBColor*	pBuffer = new RGBColor[num * vp.GetHres()];
	RGBColor	result;
	Ray			ray;
	Point2D		sp;			// sample point in [0, 1] X [0, 1]
	Point2D		pp;			// sample point on a pixel
	Point2D		lp;			// sample point on lens

	if( pBuffer )
	{
		for( int j = roff; j < rend; ++j )
		{												// up
			for( int k = 0; k < vp.GetHres(); ++k )		// across
			{												
				result = BLACK;

				for( int i = 0; i < vp.GetNumSamples(); ++i ) 
				{
					sp = pSampler->SampleUnitSquare();
					pp.x = s * (k - vp.GetHres() / 2.0f + sp.x) + xdelta;
					pp.y = s * (j - vp.GetVres() / 2.0f + sp.y);

					sp = m_pSampler->SampleUnitDisk();
					lp = sp * m_lensRadius;

					ray.o = m_eye + lp.x * m_u + lp.y * m_v;
					ray.d = GetRayDir(pp, lp);
					result += pWorld->GetTracer()->TraceRay(ray, depth);
				}

				result *= invNumSamples;
				result *= m_exposure;
				pBuffer[cursor++].Set( result.r, result.g, result.b );
			}
		}

		if( coff != 0 )
		{
			cursor = 0;

			for( int j = roff; j < rend; ++j )
			{
				for( int k = 0; k < vp.GetHres(); ++k )
					pWorld->SaveColor(j, k + coff, pBuffer[cursor++]);
			}
		}
		else
			pWorld->SaveColors(roff, num, pBuffer);

		delete[] pBuffer;
	}
}