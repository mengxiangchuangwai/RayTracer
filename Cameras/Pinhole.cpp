//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Cameras/Pinhole.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Samplers/Sampler.h"

Pinhole::Pinhole(void)
	: Camera()
	, m_vpd(500)
	, m_zoom(1.0)
{}


Pinhole::Pinhole(const Pinhole& other)
	: Camera(other)
	, m_vpd(other.m_vpd)
	, m_zoom(other.m_zoom)
{}


Pinhole*
Pinhole::Clone(void) const 
{
	return (new Pinhole(*this));
}


Pinhole&
Pinhole::operator= (const Pinhole& rhs) 
{
	if( this == &rhs )
		return (*this);

	Camera::operator= (rhs);
	m_vpd 	= rhs.m_vpd;
	m_zoom	= rhs.m_zoom;

	return (*this);
}


Pinhole::~Pinhole(void) 
{}


Vector3D
Pinhole::GetRayDir(const Point2D& p) const 
{
	Vector3D dir = p.x * m_u + p.y * m_v - m_vpd * m_w;
	dir.Normalize();
	return(dir);
}


void
Pinhole::RenderRows(Sampler* pSampler, const World* pWorld, const int roff, const int num, const float xdelta, const int coff)
{
	const ViewPlane& vp = pWorld->GetViewPlane();
	RGBColor	result;
	Ray			ray;
	Point2D		sp;		// sample point in [0, 1] x [0, 1]
	Point2D 	pp;		// sample point on a pixel
	float		s = vp.GetPixelSize() / m_zoom;
	float		invNumSamples = 1.0f / (float)(vp.GetNumSamples());
	int			rend = roff + num;
	int			cursor = 0;
	int 		depth = 0;
	RGBColor*	pBuffer = new RGBColor[num * vp.GetHres()];

	ray.o = m_eye;

	if( pBuffer )
	{
		for( int j = roff; j < rend; ++j )				// up
		{
			for( int k = 0; k < vp.GetHres(); ++k )		// across
			{
				result = BLACK;

				for( int i = 0; i < vp.GetNumSamples(); ++i ) 
				{
					sp = pSampler->SampleUnitSquare();
					pp.x = s * (k - 0.5f * vp.GetHres() + sp.x) + xdelta;
					pp.y = s * (j - 0.5f * vp.GetVres() + sp.y);
					ray.d = GetRayDir(pp);
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