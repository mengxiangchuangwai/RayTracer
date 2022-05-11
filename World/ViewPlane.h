//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __VIEW_PLANE__
#define __VIEW_PLANE__


#include "../Samplers/Sampler.h"

class ViewPlane {
public:

	ViewPlane(void);   							// default Constructor
	
	ViewPlane(const ViewPlane& other);			// copy constructor
	
	ViewPlane& 
	operator= (const ViewPlane& rhs);			// assignment operator
	
	virtual 
	~ViewPlane(void);   						// destructor
					
	void 
	SetHres(const int val);

	int
	GetHres(void) const;
	
	void 
	SetVres(const int val);

	int
	GetVres(void) const;
	
	void 
	SetPixelSize(const float size);

	float
	GetPixelSize(void) const;
	
	void 
	SetupSampler(const int num, const SamplerType type = ST_MultiJittered);

	int  
	GetNumSamples(void) const;
	
	void 
	SetSampler(Sampler* ps);

	Sampler* 
	GetSampler(void) const;
	
	void 
	SetGamma(const float val);

	float
	GetGamma(void) const;

	float
	GetInverseGamma(void) const;
	
	void 
	SetBeyondGamutShow(const bool val);

	bool
	IsBeyondGamutShow(void) const;
	
	void 
	SetMaxDepth(const int val);

	int
	GetMaxDepth(void) const;


public:

	int			m_hres;   						// horizontal image resolution 
	int			m_vres;   						// vertical image resolution
	float		m_psize;						// pixel size

	float		m_gamma;						// gamma correction factor
	float		m_invGamma;						// the inverse of the gamma correction factor
	bool		m_showBeyondGamut;				// display red if RGBColor out of gamut								
	int			m_maxDepth;

	Sampler*	m_pSampler;
	int			m_numSamples;
};



inline void
ViewPlane::SetHres(const int val) 
{
	m_hres = val;
}


inline int
ViewPlane::GetHres(void) const
{
	return (m_hres);
}


inline void
ViewPlane::SetVres(const int val) 
{
	m_vres = val;
}


inline int
ViewPlane::GetVres(void) const
{
	return (m_vres);
}


inline void
ViewPlane::SetPixelSize(const float size) 
{
	m_psize = size;
}


inline float
ViewPlane::GetPixelSize(void) const
{
	return (m_psize);
}


inline void
ViewPlane::SetGamma(const float val) 
{
	m_gamma = val;
	m_invGamma = 1.0f / m_gamma;
}


inline float
ViewPlane::GetGamma(void) const
{
	return (m_gamma);
}


inline float
ViewPlane::GetInverseGamma(void) const
{
	return (m_invGamma);
}


inline void
ViewPlane::SetBeyondGamutShow(const bool val) 
{
	m_showBeyondGamut = val;
}


inline bool
ViewPlane::IsBeyondGamutShow(void) const
{
	return (m_showBeyondGamut);
}


inline void
ViewPlane::SetMaxDepth(int val) 
{
	m_maxDepth = val;
}


inline int
ViewPlane::GetMaxDepth(void) const
{
	return (m_maxDepth);
}


inline int  
ViewPlane::GetNumSamples(void) const 
{
	return (m_numSamples);
}
	
	
inline Sampler* 
ViewPlane::GetSampler(void) const 
{
	return (m_pSampler);
}


#endif
