//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Cameras/Camera.h"
#include "../World/World.h"

Camera::Camera(void)
	: m_eye(0, 0, 500)
	, m_lookat(0)
	, m_up(0, 1, 0)
	, m_u(1, 0, 0)
	, m_v(0, 1, 0)
	, m_w(0, 0, 1)
	, m_ra(0)
	, m_exposure(1.0)
	, m_numWorkers(6)
{}


Camera::Camera(const Camera& other)
	: m_eye(other.m_eye)
	, m_lookat(other.m_lookat)
	, m_up(other.m_up)
	, m_u(other.m_u)
	, m_v(other.m_v)
	, m_w(other.m_w)
	, m_ra(other.m_ra)
	, m_exposure(other.m_exposure)
	, m_numWorkers(other.m_numWorkers)
{}


Camera&
Camera::operator= (const Camera& rhs) 
{
	if( this == &rhs )
		return (*this);

	m_eye			= rhs.m_eye;
	m_lookat		= rhs.m_lookat;
	m_up			= rhs.m_up;
	m_u				= rhs.m_u;
	m_v				= rhs.m_v;
	m_w				= rhs.m_w;
	m_ra			= rhs.m_ra;
	m_exposure 		= rhs.m_exposure;
	m_numWorkers	= rhs.m_numWorkers;

	return (*this);
}


Camera::~Camera(void) 
{}


// This computes an orthornormal basis given the view point, lookat point, and up vector

void
Camera::ComputeONB(void) 
{
	m_w = m_eye - m_lookat;
	m_w.Normalize();
	m_u = m_up ^ m_w;
	m_u.Normalize();
	m_v = m_w ^ m_u;

	// take care of the singularity by hardwiring in specific camera orientations

	if( m_eye.x == m_lookat.x && m_eye.z == m_lookat.z && m_eye.y > m_lookat.y ) 
	{									// camera looking vertically down
		m_u = Vector3D(0, 0, 1);
		m_v = Vector3D(1, 0, 0);
		m_w = Vector3D(0, 1, 0);
	}

	if( m_eye.x == m_lookat.x && m_eye.z == m_lookat.z && m_eye.y < m_lookat.y ) 
	{									// camera looking vertically up
		m_u = Vector3D(1, 0, 0);
		m_v = Vector3D(0, 0, 1);
		m_w = Vector3D(0, -1, 0);
	}
}


void
Camera::RenderScene(const World& wr, const float xdelta, const int coff )
{
	const ViewPlane& vp = wr.GetViewPlane();

	if( m_numWorkers < 2 )
	{
		RenderRows(vp.GetSampler(), &wr, 0, vp.GetVres(), xdelta, coff);
	}
	else
	{
		int numRows	= (vp.GetVres() > m_numWorkers ? vp.GetVres() / m_numWorkers : 1);
		int numWorkers = (vp.GetVres() > m_numWorkers ? m_numWorkers : vp.GetVres());
		WorkerThreadBlock* pThreadBlocks = new WorkerThreadBlock[numWorkers];

		if( pThreadBlocks )
		{
			int roff	= 0;

			for( int i = 0; i < numWorkers; ++i )
			{
				pThreadBlocks[i].pCamera	= this;
				pThreadBlocks[i].pWorld		= &wr;
				pThreadBlocks[i].pSampler	= vp.GetSampler()->Clone();
				pThreadBlocks[i].xdelta		= xdelta;
				pThreadBlocks[i].coff		= coff;
				pThreadBlocks[i].roff		= roff;
				pThreadBlocks[i].nrows		= numRows;
				roff += numRows;
			}

			if( numRows > 1 )
				pThreadBlocks[numWorkers - 1].nrows += vp.GetVres() % numWorkers;

			for( int i = 0; i < numWorkers; ++i )
				pThreadBlocks[i].hThread	= (HANDLE)_beginthreadex( 
				NULL, 0, &WorkerThreadFunc, (void *)(pThreadBlocks + i), 0, NULL );

			for( int i = 0; i < numWorkers; ++i )
			{
				WaitForSingleObject( pThreadBlocks[i].hThread, INFINITE );

				if( 0 == pThreadBlocks[i].hThread )
					RenderRows(pThreadBlocks[i].pSampler, &wr, pThreadBlocks[i].roff, pThreadBlocks[i].nrows, xdelta, coff);

				delete pThreadBlocks[i].pSampler;
				CloseHandle(pThreadBlocks[i].hThread);
			}

			delete[] pThreadBlocks;
		}
	}
}