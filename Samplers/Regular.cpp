//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Samplers/Regular.h"

Regular::Regular(void)
	: Sampler()
{}


Regular::Regular(const int numSamples)
	: Sampler(numSamples)
{
	GenerateSamples();
}


Regular::Regular(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets)
{
	GenerateSamples();
}


Regular::Regular(const Regular& other)
	: Sampler(other)
{}


Regular&
Regular::operator= (const Regular& rhs)	
{
	if( this == &rhs )
		return (*this);

	Sampler::operator= (rhs);
	return (*this);
}


Regular*
Regular::Clone(void) const 
{
	return (new Regular(*this));
}


Regular::~Regular(void) 
{}


void
Regular::GenerateSamples(void) 
{
	m_samples.erase(m_samples.begin(), m_samples.end());
	m_samples.reserve(m_numSamples * m_numSets);
	
	int num = (int) sqrt((float)m_numSamples);
	float sy, sx;

	for( int s = 0; s < m_numSets; ++s ) 
	{
		for( int i = 0; i < num; ++i ) 
		{
			sy = ((float)i + 0.5f) / num;

			for( int j = 0; j < num; ++j ) 
			{
				sx = ((float)j + 0.5f) / num;
				m_samples.push_back(Point2D(sx, sy));
			}
		}
		
		for( int i = num * num; i < m_numSamples; ++i )
			m_samples.push_back(Point2D());
	}

	SetupShuffledIndices();
}