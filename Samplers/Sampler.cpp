//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <algorithm>   // for random_shuffle in Sampler::setup_shuffled_indices
#include <iostream>

#include "../Samplers/Sampler.h"
#include "../Utilities/Constants.h"
#include "../Utilities/Random.h"

Sampler::Sampler(void)
	: m_numSamples(1)
	, m_numSets(83)
{
	for( int i = 0; i < 4; ++i )
	{
		m_counts[i]	= 0;
		m_jumps[i]	= 0;
	}
}


Sampler::Sampler(const int numSamples)
	: m_numSamples(numSamples)
	, m_numSets(83)
{
	for( int i = 0; i < 4; ++i )
	{
		m_counts[i]	= 0;
		m_jumps[i]	= 0;
	}
}


Sampler::Sampler(const int numSamples, const int numSets)
	: m_numSamples(numSamples)
	, m_numSets(numSets)
{
	for( int i = 0; i < 4; ++i )
	{
		m_counts[i]	= 0;
		m_jumps[i]	= 0;
	}
}


Sampler::Sampler(const Sampler& other)
	: m_numSamples(other.m_numSamples)
	, m_numSets(other.m_numSets)
	, m_samples(other.m_samples)
	, m_shuffledIndices(other.m_shuffledIndices)
	, m_diskSamples(other.m_diskSamples)
	, m_hemisphereSamples(other.m_hemisphereSamples)
	, m_sphereSamples(other.m_sphereSamples)
{
	for( int i = 0; i < 4; ++i )
	{
		m_counts[i]	= other.m_counts[i];
		m_jumps[i]	= other.m_jumps[i];
	}
}


Sampler&
Sampler::operator= (const Sampler& rhs)	
{
	if( this == &rhs )
		return (*this);

	m_numSamples 		= rhs.m_numSamples;
	m_numSets			= rhs.m_numSets;
	m_samples			= rhs.m_samples;
	m_shuffledIndices	= rhs.m_shuffledIndices;
	m_diskSamples		= rhs.m_diskSamples;
	m_hemisphereSamples	= rhs.m_hemisphereSamples;
	m_sphereSamples		= rhs.m_sphereSamples;

	for( int i = 0; i < 4; ++i )
	{
		m_counts[i]	= rhs.m_counts[i];
		m_jumps[i]	= rhs.m_jumps[i];
	}

	return (*this);
}

Sampler::~Sampler(void) 
{}


// shuffle the x coordinates of the points within each set

void
Sampler::ShuffleXCoords(void) 
{
	for( int s = 0; s < m_numSets; ++s ) 
	{
		for( int i = 0; i < m_numSamples; ++i ) 
		{
			int target = RandInt() % m_numSamples + s * m_numSamples;
			swap2(m_samples[i + s * m_numSamples].x, m_samples[target].x);
		}
	}
}


// shuffle the y coordinates of the points within set

void
Sampler::ShuffleYCoords(void) 
{
	for( int s = 0; s < m_numSets; ++s ) 
	{
		for( int i = 0; i <  m_numSamples; ++i ) 
		{
			int target = RandInt() % m_numSamples + s * m_numSamples;
			swap2(m_samples[i + s * m_numSamples].y, m_samples[target].y);  
		}
	}
}


// sets up randomly shuffled indices for the m_samples array

void
Sampler::SetupShuffledIndices(void) 
{
	m_shuffledIndices.reserve(m_numSamples * m_numSets);
	std::vector<int> indices;
	indices.reserve(m_numSamples);
	
	for( int i = 0; i < m_numSamples; ++i )
		indices.push_back(i);
	
	for( int s = 0; s < m_numSets; ++s ) 
	{ 
		random_shuffle(indices.begin(), indices.end());	
		
		for( int i = 0; i < m_numSamples; ++i )
			m_shuffledIndices.push_back(indices[i]);
	}
}


// Maps the 2D sample points in the square [0,1] X [0,1] to a unit disk, using Peter Shirley's
// concentric map function

void
Sampler::SamplesToUnitDisk(void) 
{
	size_t num = m_samples.size();
	double r, phi;		// polar coordinates
	Point2D pt; 		// sample point on unit disk

	
	if( !m_diskSamples.empty() )
		m_diskSamples.erase(m_diskSamples.begin(), m_diskSamples.end());

	m_diskSamples.resize(num);

	for( size_t i = 0; i < num; ++i ) 
	{
		pt.x = 2.0f * m_samples[i].x - 1.0f;
		pt.y = 2.0f * m_samples[i].y - 1.0f;

		if( pt.x > -pt.y ) 
		{							// sectors 1 and 2
			if( pt.x > pt.y ) 
			{						// sector 1
				r = pt.x;
				phi = pt.y / pt.x;
			}
			else 
			{						// sector 2
				r = pt.y;
				phi = 2 - pt.x / pt.y;
			}
		}
		else 
		{							// sectors 3 and 4
			if (pt.x < pt.y) 
			{						// sector 3
				r = -pt.x;
				phi = 4 + pt.y / pt.x;
			}
			else 
			{						// sector 4
				r = -pt.y;
				phi = (pt.y != 0.0 ? 6 - pt.x / pt.y : 0.0);
			}
		}

		phi *= PI / 4.0;
		m_diskSamples[i].x = (float)(r * ::cos(phi));
		m_diskSamples[i].y = (float)(r * ::sin(phi));
	}
}


// Maps the 2D sample points to 3D points on a unit hemisphere with a cosine power
// density distribution in the polar angle

void
Sampler::SamplesToHemisphere(const float exp) 
{
	size_t num = m_samples.size();

	if( !m_hemisphereSamples.empty() )
		m_hemisphereSamples.erase(m_hemisphereSamples.begin(), m_hemisphereSamples.end());

	m_hemisphereSamples.reserve(num);
	double phi, cosPhi, sinPhi;
	double cosTheta, sinTheta;
	double pu, pv, pw;

	for( size_t i = 0; i < num; ++i ) 
	{
		phi = 2.0 * PI * m_samples[i].x;
		cosPhi = cos(phi);
		sinPhi = sin(phi);
		cosTheta = pow((1.0 - m_samples[i].y), 1.0 / (exp + 1.0));
		sinTheta = sqrt(1.0 - cosTheta * cosTheta);
		pu = sinTheta * cosPhi;
		pv = sinTheta * sinPhi;
		pw = cosTheta;
		m_hemisphereSamples.push_back(Point3D(pu, pv, pw));
	}
}


// Maps the 2D sample points to 3D points on a unit sphere with a uniform density
// distribution over the surface
// this is used for modelling a spherical light

void
Sampler::SamplesToSphere(void) 
{
	size_t num = m_samples.size();

	if( !m_sphereSamples.empty() )
		m_sphereSamples.erase(m_sphereSamples.begin(), m_sphereSamples.end());

	m_sphereSamples.reserve(num);
	double x, y, z, r, phi;

	for( size_t i = 0; i < num; ++i ) 
	{
    	z 	= 1.0f - 2.0f * m_samples[i].x;
    	r 	= sqrt(1.0 - z * z);
    	phi	= TWO_PI * m_samples[i].y;
    	x 	= r * cos(phi);
    	y 	= r * sin(phi);
		m_sphereSamples.push_back(Point3D(x, y, z));
	}
}


// the final version in Listing 5.13

Point2D
Sampler::SampleUnitSquare(void) 
{
	if( 0 == m_counts[0] % m_numSamples ) 							// start of a new pixel
		m_jumps[0] = (RandInt() % m_numSets) * m_numSamples;		// random index jumps initialised to zero in constructor

	size_t index = m_jumps[0] + m_shuffledIndices[m_jumps[0] + m_counts[0]++ % m_numSamples];
	
	return (m_samples[index]);
}


Point2D
Sampler::SampleUnitDisk(void) 
{
	if( 0 == m_counts[1] % m_numSamples )							// start of a new pixel
		m_jumps[1] = (RandInt() % m_numSets) * m_numSamples;

	size_t index = m_jumps[1] + m_shuffledIndices[m_jumps[1] + m_counts[1]++ % m_numSamples];
	return (m_diskSamples[index]);
}


Point3D
Sampler::SampleHemisphere(void) 
{
	if( 0 == m_counts[2] % m_numSamples )							// start of a new pixel
		m_jumps[2] = (RandInt() % m_numSets) * m_numSamples;
	
	size_t index = m_jumps[2] + m_shuffledIndices[m_jumps[2] + m_counts[2]++ % m_numSamples];
	return (m_hemisphereSamples[index]);
}


Point3D
Sampler::SampleSphere(void) 
{
	if( 0 == m_counts[3] % m_numSamples )							// start of a new pixel
		m_jumps[3] = (RandInt() % m_numSets) * m_numSamples;

	size_t index = m_jumps[3] + m_shuffledIndices[m_jumps[3] + m_counts[3]++ % m_numSamples];
	return (m_sphereSamples[index]);
}


// This is a specialised function called in LatticeNoise::init_vector_table
// It doesn't shuffle the indices

Point2D
Sampler::SampleFirstSet(void) 
{
	return (m_samples[m_counts[0]++ % m_numSamples]);
}