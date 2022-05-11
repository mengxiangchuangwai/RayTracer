//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Samplers/NRooks.h"
#include "../Utilities/Random.h"

NRooks::NRooks(void)
	: Sampler()
{}


NRooks::NRooks(const int numSamples)
	: Sampler(numSamples) 
{
	GenerateSamples();
}


NRooks::NRooks(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) 
{
	GenerateSamples();
}


NRooks::NRooks(const NRooks& other)
	: Sampler(other) 
{}


NRooks&
NRooks::operator= (const NRooks& rhs) 
{
	if( this == &rhs )
		return (*this);

	Sampler::operator= (rhs);
	return (*this);
}


NRooks*
NRooks::Clone(void) const 
{
	return (new NRooks(*this));
}


NRooks::~NRooks(void) 
{}


void
NRooks::GenerateSamples(void) 
{
	m_samples.erase(m_samples.begin(), m_samples.end());
	m_samples.reserve(m_numSamples * m_numSets);
	Point2D pt;

	for( int s = 0; s < m_numSets; ++s ) 
	{
		for( int i = 0; i < m_numSamples; ++i ) 
		{
			pt.x = (i + RandFloat()) / m_numSamples;
			pt.y = (i + RandFloat()) / m_numSamples;;
			m_samples.push_back(pt);
		}
	}

	ShuffleCoords();
	SetupShuffledIndices();
}