//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __CAMERA__
#define __CAMERA__


// There is no view plane distance because the fisheye and panoramic cameras don't use it

#include <cmath>
#include <windows.h>
#include <process.h>	// for _beginthread and _endthread

#include "../Utilities/Point3D.h"
#include "../Utilities/Vector3D.h"

#define	MAX_WORKER_THREADS	10000

class World;
class Sampler;

class Camera {
	public:

		Camera(void);   					// default constructor

		Camera(const Camera& other);		// copy constructor

		virtual Camera*						// virtual copy constructor
		Clone(void) const = 0;

		virtual
		~Camera(void);

		virtual void
		RenderScene(const World& wr, const float xdelta = 0, const int coff = 0);

		virtual void
		RenderRows(Sampler* pSampler, const World* pWorld, const int roff, const int nrows, const float xdelta = 0, const int coff = 0);

		void
		SetEye(const Point3D& eye);

		void
		SetEye(const float x, const float y, const float z);

		const Point3D&
		GetEye(void) const;

		void
		SetLookat(const Point3D& at);

		void
		SetLookat(const float x, const float y, const float z);

		const Point3D&
		GetLookat(void) const;

		void
		SetUpVector(const Vector3D& up);

		void
		SetUpVector(const float x, const float y, const float z);

		const Vector3D&
		GetUpVector(void) const;

		void
		SetRollingAngle(const float value);

		float 
		GetRollingAngle(void) const;

		void
		SetExposureTime(const float exposure);

		float
		GetExposureTime(void) const;

		void
		ComputeONB(void);

		void
		SetNumWorkerThreads(const size_t num);

		size_t
		GetNumWorkerThreads(void) const;


	protected:

		Point3D		m_eye;				// eye point
		Point3D		m_lookat; 			// lookat point
		Vector3D	m_up;				// up vector
		Vector3D	m_u, m_v, m_w;		// orthonormal basis vectors
		float		m_ra;				// roll angle
		float		m_exposure;
		size_t		m_numWorkers;	

		Camera& 						// assignment operator
		operator= (const Camera& other);
};



struct WorkerThreadBlock {
	HANDLE			hThread;
	const World*	pWorld;
	Camera*			pCamera;
	Sampler*		pSampler;
	float			xdelta;
	int				coff;
	int				roff;
	int				nrows;
};


inline unsigned int __stdcall 
WorkerThreadFunc( void* pArgs )
{
	WorkerThreadBlock* pTB = (WorkerThreadBlock *)pArgs;
	pTB->pCamera->RenderRows(pTB->pSampler, pTB->pWorld, pTB->roff, pTB->nrows, pTB->xdelta, pTB->coff); 
	_endthreadex(0);
	return 0;
}


inline void
Camera::RenderRows(Sampler* pSampler, const World* pWorld, 
				   const int yoff, const int num, const float xdelta, const int xoff)
{}


inline void
Camera::SetEye(const Point3D& eye) 
{
	m_eye = eye;
}


inline void
Camera::SetEye(const float x, const float y, const float z) 
{
	m_eye.x = x; m_eye.y = y; m_eye.z = z;
}


inline const Point3D&
Camera::GetEye(void) const
{
	return (m_eye);
}


inline void
Camera::SetLookat(const Point3D& at) 
{
	m_lookat = at;
}


inline void
Camera::SetLookat(const float x, const float y, const float z) 
{
	m_lookat.x = x; m_lookat.y = y; m_lookat.z = z;
}


inline const Point3D&
Camera::GetLookat(void) const
{
	return (m_lookat);
}


inline void
Camera::SetUpVector(const Vector3D& up) 
{
	m_up = up;
}


inline void
Camera::SetUpVector(const float x, const float y, const float z) 
{
	m_up.x = x; m_up.y = y; m_up.z = z;
}


inline const Vector3D&
Camera::GetUpVector(void) const
{
	return (m_up);
}


inline void
Camera::SetRollingAngle(const float value) 
{
	m_ra = value;
}


inline float 
Camera::GetRollingAngle(void) const
{
	return (m_ra);
}


inline void
Camera::SetExposureTime(const float value) 
{
	m_exposure = value;
}


inline float
Camera::GetExposureTime(void) const
{
	return (m_exposure);
}


inline void
Camera::SetNumWorkerThreads(const size_t num)
{
	m_numWorkers = (num > MAX_WORKER_THREADS ? MAX_WORKER_THREADS : num);
}


inline size_t
Camera::GetNumWorkerThreads(void) const
{
	return (m_numWorkers);
}


#endif
