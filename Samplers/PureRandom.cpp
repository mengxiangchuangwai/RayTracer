//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Samplers/PureRandom.h"
#include "../Utilities/Random.h"

PureRandom::PureRandom(void)
	: Sampler()
{}


PureRandom::PureRandom(const int numSamples)
	: Sampler(numSamples) 
{
	GenerateSamples();
}


PureRandom::PureRandom(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) 
{
	GenerateSamples();
}


PureRandom::PureRandom(const PureRandom& other)
	: Sampler(other) 
{}


PureRandom&
PureRandom::operator= (const PureRandom& rhs) 
{
	if( this == &rhs )
		return (*this);

	Sampler::operator= (rhs);
	return (*this);
}


PureRandom*
PureRandom::Clone(void) const 
{
	return (new PureRandom(*this));
}


PureRandom::~PureRandom(void) 
{}


void
PureRandom::GenerateSamples(void) 
{
	m_samples.erase(m_samples.begin(), m_samples.end());
	m_samples.reserve(m_numSamples * m_numSets);
	Point2D pt;

	for( int s = 0; s < m_numSets; ++s ) 
	{
		for( int i = 0; i < m_numSamples; ++i ) 
		{
			pt.x = RandFloat();
			pt.y = RandFloat();
			m_samples.push_back(pt);
		}
	}

	SetupShuffledIndices();
}