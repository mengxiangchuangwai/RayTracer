//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Cameras/Spherical.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Maths.h"
#include "../Samplers/Sampler.h"

Spherical::Spherical(void)
	: Camera()
	, m_psiMax(120)	
{}


Spherical::Spherical(const Spherical& other)
	: Camera(other)
	, m_psiMax(other.m_psiMax)
	, m_lambdaMax(other.m_lambdaMax)
{}


Spherical*
Spherical::Clone(void) const 
{
	return (new Spherical(*this));
}


Spherical&
Spherical::operator= (const Spherical& rhs) 
{
	if( this == &rhs )
		return (*this);

	Camera::operator= (rhs);

	m_psiMax = rhs.m_psiMax;
	m_lambdaMax = rhs.m_lambdaMax;

	return (*this);
}


Spherical::~Spherical(void) 
{}


Vector3D
Spherical::GetRayDir(	const Point2D& 	pp,
						const int 		hres,
						const int 		vres,
						const float 	s) const 
{

	// compute the normalized device coordinates

	Point2D pn(2.0f / (s * (float)hres) * pp.x, 2.0f / (s * (float)vres) * pp.y);

	// compute the angles lambda and psi in radians

	float lambda = pn.x * degreeToRadian(m_lambdaMax);
	float psi = pn.y * degreeToRadian(m_psiMax);

	// compute the sherical azimuth and polar angles

	float phi = PI - lambda;
	float theta = 0.5f * PI - psi;

	float sinPhi	= sinf(phi);
	float cosPhi	= cosf(phi);
	float sinTheta	= sinf(theta);
	float cosTheta	= cosf(theta);

	Vector3D dir = sinTheta * sinPhi * m_u + cosTheta * m_v + sinTheta * cosPhi * m_w;

	return dir;
}


void
Spherical::RenderRows(Sampler* pSampler, const World* pWorld, const int roff, const int num, const float xdelta, const int coff)
{
	const ViewPlane& vp = pWorld->GetViewPlane();
	int 		hres	= vp.GetHres();
	int 		vres 	= vp.GetVres();
	float		s 		= vp.GetPixelSize();	
	int 		depth 	= 0;
	Point2D 	sp; 			// sample point in [0, 1] X [0, 1]
	Point2D 	pp;				// sample point on the pixel
	float		invNumSamples = 1.0f / (float)(vp.GetNumSamples());
	int			rend = roff + num;
	int			cursor = 0;
	RGBColor*	pBuffer = new RGBColor[num * vp.GetHres()];
	RGBColor	result;
	Ray			ray; 
				
	ray.o = m_eye;

	if( pBuffer )
	{
		for( int j = roff; j < rend; ++j )				// up
			for( int k = 0; k < hres; ++k )			// across
			{										
				result = BLACK;

				for( int i = 0; i < vp.GetNumSamples(); ++i ) 
				{
					sp = pSampler->SampleUnitSquare();
					pp.x = s * (k - 0.5f * hres + sp.x) + xdelta;
					pp.y = s * (j - 0.5f * vres + sp.y);
					ray.d = GetRayDir(pp, hres, vres, s);
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