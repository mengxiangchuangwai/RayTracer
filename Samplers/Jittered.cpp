//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Samplers/Jittered.h"
#include "../Utilities/Random.h"

Jittered::Jittered(void)
	: Sampler()
{}


Jittered::Jittered(const int numSamples)
	: Sampler(numSamples) 
{
	GenerateSamples();
}


Jittered::Jittered(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) 
{
	GenerateSamples();
}


Jittered::Jittered(const Jittered& other)
	: Sampler(other) 
{}


Jittered&
Jittered::operator= (const Jittered& rhs) 
{
	if( this == &rhs )
		return (*this);

	Sampler::operator= (rhs);
	return (*this);
}


Jittered*
Jittered::Clone(void) const 
{
	return (new Jittered(*this));
}


Jittered::~Jittered(void) 
{}


void
Jittered::GenerateSamples(void) 
{
	m_samples.erase(m_samples.begin(), m_samples.end());
	m_samples.reserve(m_numSamples * m_numSets);
	int	num = (int)sqrt((float)m_numSamples);
	Point2D pt;

	for( int s = 0; s < m_numSets; ++s ) 
	{
		for( int j = 0; j < num; ++j ) 
		{
			for( int k = 0; k < num; ++k ) 
			{
				pt.x = (k + RandFloat()) / num;
				pt.y = (j + RandFloat()) / num;
				m_samples.push_back(pt);
			}
		}

		pt.x = pt.y = 0.0;

		for( int i = num * num; i < m_numSamples; ++i )
			m_samples.push_back(pt);
	}

	SetupShuffledIndices();
}