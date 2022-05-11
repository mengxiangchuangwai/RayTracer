//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../World/ViewPlane.h"
#include "../Samplers/Hammersley.h"
#include "../Samplers/Jittered.h"
#include "../Samplers/MultiJittered.h"
#include "../Samplers/NRooks.h"
#include "../Samplers/PureRandom.h"
#include "../Samplers/Regular.h"

ViewPlane::ViewPlane(void)							
	: m_hres(450) 
	, m_vres(450)
	, m_psize(1.0)
	, m_gamma(1.0)
	, m_invGamma(1.0)
	, m_showBeyondGamut(false)
	, m_pSampler(new Regular(1))
	, m_numSamples(1)
	, m_maxDepth(0)
{}


ViewPlane::ViewPlane(const ViewPlane& other)   
	: m_hres(other.m_hres)
	, m_vres(other.m_vres) 
	, m_psize(other.m_psize)
	, m_gamma(other.m_gamma)
	, m_invGamma(other.m_invGamma)
	, m_showBeyondGamut(other.m_showBeyondGamut)
	, m_pSampler(other.m_pSampler->Clone())
	, m_numSamples(other.m_numSamples)
	, m_maxDepth(other.m_maxDepth)
{}


ViewPlane& ViewPlane::operator= (const ViewPlane& rhs) 
{
	if( this == &rhs )
		return (*this);
		
	m_hres 				= rhs.m_hres;
	m_vres 				= rhs.m_vres;
	m_psize				= rhs.m_psize;
	m_gamma				= rhs.m_gamma;
	m_invGamma			= rhs.m_invGamma;
	m_showBeyondGamut	= rhs.m_showBeyondGamut;
	m_numSamples 		= rhs.m_numSamples;
	m_maxDepth 			= rhs.m_maxDepth;

	SAFE_DELETE(m_pSampler);

	m_pSampler 			= rhs.m_pSampler->Clone();
	return (*this);
}


ViewPlane::~ViewPlane(void) 
{
	SAFE_DELETE(m_pSampler);
}


void
ViewPlane::SetupSampler(const int num, const SamplerType type) 
{
	m_numSamples = num;
	SAFE_DELETE(m_pSampler);

	if( num > 1 )
	{
		switch( type ) 
		{
		case ST_Hammersley:
			m_pSampler = new Hammersley(num);
			break;
		case ST_Jittered:
			m_pSampler = new Jittered(num);
			break;
		case ST_MultiJittered:
		default:
			m_pSampler = new MultiJittered(num);
			break;
		case ST_NRooks:
			m_pSampler = new NRooks(num);
			break;
		case ST_PureRandom:
			m_pSampler = new PureRandom(num);
			break;
		case ST_Regular:
			m_pSampler = new Regular(num);
			break;
		}
	}
	else
		m_pSampler = new Regular(1);
}


void
ViewPlane::SetSampler(Sampler* sp) 
{
	SAFE_DELETE(m_pSampler);

	if( sp ) 
	{
		m_numSamples = sp->GetNumSamples();
		m_pSampler = sp;
	}
}