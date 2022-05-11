//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Samplers/MultiJittered.h"
#include "../Utilities/Random.h"

MultiJittered::MultiJittered(void)
	: Sampler()
{}


MultiJittered::MultiJittered(const int numSamples)
	: Sampler(numSamples) 
{
	GenerateSamples();
}


MultiJittered::MultiJittered(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) 
{
	GenerateSamples();
}


MultiJittered::MultiJittered(const MultiJittered& other)
	: Sampler(other)
{}


MultiJittered&
MultiJittered::operator= (const MultiJittered& rhs)	
{
	if( this == &rhs )
		return (*this);

	Sampler::operator= (rhs);

	return (*this);
}


MultiJittered*
MultiJittered::Clone(void) const 
{
	return (new MultiJittered(*this));
}


MultiJittered::~MultiJittered(void) 
{}


// This is based on code in Chui et al. (1994), cited in the references
// The overloaded functions rand_int and rand_float (called from rand_int), which take arguments,
// are defined in Maths.h
// They should be defined here, as this is the only place they are usedm but I couldn't get them to compile

void
MultiJittered::GenerateSamples(void) 
{
	m_samples.erase(m_samples.begin(), m_samples.end());
	m_samples.resize(m_numSamples * m_numSets);

	// m_numSamples needs to be a perfect square

	int		num  = (int)sqrt((float)m_numSamples);
	float	step = 1.0f / (num * num);

	// distribute points in the initial patterns

	for( int s = 0; s < m_numSets; ++s ) 
	{
		for( int i = 0; i < num; ++i ) 
		{
			for( int j = 0; j < num; ++j ) 
			{
				int index = i * num + j + s * m_numSamples;
				m_samples[index].x = (i * num + j) * step + RandFloat(0.0, step);
				m_samples[index].y = (j * num + i) * step + RandFloat(0.0, step);
			}
		}
	}

	// shuffle x coordinates

	for( int s = 0; s < m_numSets; ++s ) 
	{
		for( int i = 0; i < num; ++i ) 
		{
			for( int j = 0; j < num; ++j ) 
			{
				int k = RandInt(j, num - 1);
				swap2( m_samples[i * num + j + s * m_numSamples].x, m_samples[i * num + k + s * m_numSamples].x);
			}
		}
	}

	// shuffle y coordinates

	for( int s = 0; s < m_numSets; ++s ) 
	{
		for( int i = 0; i < num; ++i ) 
		{
			for( int j = 0; j < num; ++j ) 
			{
				int k = RandInt(j, num - 1);
				swap2( m_samples[j * num + i + s * m_numSamples].y, m_samples[k * num + i + s * m_numSamples].y);
			}
		}
	}

	SetupShuffledIndices();
}