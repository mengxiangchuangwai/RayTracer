//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Samplers/Hammersley.h"
#include "../Utilities/Maths.h"

Hammersley::Hammersley(void)
	: Sampler()
{}


Hammersley::Hammersley(const int numSamples)
	: Sampler(numSamples) 
{
	GenerateSamples();
}


Hammersley::Hammersley(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) 
{
	GenerateSamples();
}


Hammersley::Hammersley(const Hammersley& other)
	: Sampler(other) 
{}


Hammersley&
Hammersley::operator= (const Hammersley& rhs)
{
	if( this == &rhs )
		return (*this);

	Sampler::operator= (rhs);

	return (*this);
}


Hammersley*
Hammersley::Clone(void) const 
{
	return (new Hammersley(*this));
}


Hammersley::~Hammersley(void) 
{}


double
Hammersley::Phi(int num) 
{
	double x = 0.0;
	double f = 0.5;

	while( num ) 
	{
		x += f * (double) (num % 2);
		num /= 2;
		f *= 0.5;
	}

	return (x);
}


void
Hammersley::GenerateSamples(void) 
{
	m_samples.erase(m_samples.begin(), m_samples.end());
	m_samples.reserve(m_numSamples * m_numSets);
	Point2D pt;

	for( int s = 0; s < m_numSets; ++s ) 
	{
		for( int i = 0; i < m_numSamples; ++i ) 
		{
			pt.x = (float)(i / m_numSamples);
			pt.y = (float)Phi(i);
			m_samples.push_back(pt);
		}
	}

	SetupShuffledIndices();
}