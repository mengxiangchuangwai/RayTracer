//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Cameras/FishEye.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Samplers/Sampler.h"

FishEye::FishEye(void)
	: Camera()
	, m_psiMax(120)
{}


FishEye::FishEye(const FishEye& other)
	: Camera(other)
	, m_psiMax(other.m_psiMax)
{}


FishEye*
FishEye::Clone(void) const 
{
	return (new FishEye(*this));
}


FishEye&
FishEye::operator= (const FishEye& rhs) 
{
	if( this == &rhs )
		return (*this);

	Camera::operator= (rhs);
	m_psiMax = rhs.m_psiMax;

	return (*this);
}


FishEye::~FishEye(void) 
{}


Vector3D
FishEye::GetRayDir(	const Point2D& 	pp,
					const int 		hres,
					const int 		vres,
					const float 	s,
					float& 			rsquared) const 
{

	// compute the normalized device coordinates
	Vector3D dir(0.0);
	Point2D pn(2.0f / (s * (float)hres) * pp.x, 2.0f / (s * (float)vres) * pp.y);
	rsquared = pn.x * pn.x + pn.y * pn.y;

	if( rsquared <= 1.0 ) 
	{
		float r 		= sqrtf(rsquared);
		float psi 		= r * m_psiMax * PI_ON_180;
		float sinPsi 	= sinf(psi);
		float cosPsi 	= cosf(psi);
		float sinAlpha	= pn.y / r;
		float cosAlpha	= pn.x / r;
		dir 			= sinPsi * cosAlpha * m_u +  sinPsi * sinAlpha * m_v - cosPsi * m_w;
	}
	
	return (dir);
}


void
FishEye::RenderRows(Sampler* pSampler, const World* pWorld, const int roff, const int num, const float xdelta, const int coff)
{
	const ViewPlane& vp	= pWorld->GetViewPlane();
	int 		hres = vp.GetHres();
	int 		vres = vp.GetVres();
	float		s = vp.GetPixelSize();
	int 		depth = 0;
	Point2D 	sp; 			// sample point in [0, 1] X [0, 1]
	Point2D 	pp;				// sample point on the pixel
	float		rsquared;		// sum of squares of normalised device coordinates
	float		invNumSamples = 1.0f / (float)(vp.GetNumSamples());
	int			rend = roff + num;
	int			cursor = 0;
	RGBColor*	pBuffer = new RGBColor[num * hres];
	RGBColor	result;
	Ray			ray;

	ray.o = m_eye;

	if( pBuffer )
	{
		for( int j = roff; j < rend; ++j )			// up
			for( int k = 0; k < hres; ++k ) 
			{										// across
				result = BLACK;

				for( int i = 0; i < vp.GetNumSamples(); ++i ) 
				{
					sp		= pSampler->SampleUnitSquare();
					pp.x	= s * (k - 0.5f * hres + sp.x) + xdelta;
					pp.y	= s * (j - 0.5f * vres + sp.y);
					ray.d	= GetRayDir(pp, hres, vres, s, rsquared);

					if( rsquared <= 1.0 )
						result += pWorld->GetTracer()->TraceRay(ray, depth);
				}

				result *= invNumSamples;
				result *= m_exposure;
				pBuffer[cursor++].Set( result.r, result.g, result.b );
			}


		if( coff != 0 )
		{
			cursor = 0;

			for( int j = roff; j < rend; ++j )
			{
				for( int k = 0; k < hres; ++k )
					pWorld->SaveColor(j, k + coff, pBuffer[cursor++]);
			}
		}
		else
			pWorld->SaveColors(roff, num, pBuffer);

		delete[] pBuffer;
	}
}