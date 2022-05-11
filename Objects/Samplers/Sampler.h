//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __SAMPLER__
#define __SAMPLER__


#include <vector>
#include <cmath>

#include "../Utilities/Point2D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/RefCounter.h"
#include "../Utilities/Maths.h"

typedef enum {
	ST_Hammersley,
	ST_Jittered,
	ST_MultiJittered,
	ST_NRooks,
	ST_PureRandom,
	ST_Regular
} SamplerType;

class Sampler {
	public:

		Sampler(void);

		Sampler(const int numSamples);

		Sampler(const int numSamples, const int numSets);

		Sampler(const Sampler& other);

		Sampler&
		operator= (const Sampler& rhs);

		virtual Sampler*
		Clone(void) const = 0;

		virtual
		~Sampler(void);

		virtual void							        // generate sample patterns in a unit square
		GenerateSamples(void) = 0;

		virtual void
		GenerateSamples(const int numSamples, const int numSets);

		void
		SetNumSets(const int num);

		int 
		GetNumSets(void) const;

		void
		SetNumSamples(const int num);

		int
		GetNumSamples(void) const;

		void
		ShuffleXCoords(void);

		void
		ShuffleYCoords(void);

		void
		ShuffleCoords(void);

		void
		SamplesToUnitDisk(void);

		void
		SamplesToHemisphere(const float exp);

		void
		SamplesToSphere(void);


		// the following functions are not const because they change m_count and m_jump

		Point2D											// get next sample on unit square
		SampleUnitSquare(void);

		Point2D											// get next sample on unit disk
		SampleUnitDisk(void);

		Point3D											// get next sample on unit hemisphere
		SampleHemisphere(void);

		Point3D											// get next sample on unit sphere
		SampleSphere(void);

		Point2D											// only used to set up a vector noise table
		SampleFirstSet(void);							// this is not discussed in the book, but see the
														// file LatticeNoise.cpp in Chapter 31
		virtual Sampler*
		Release(void);

		virtual Sampler*
		AddRef(void);

		virtual int
		GetRef(void) const;


	protected:

		void
		SetupShuffledIndices(void);

		int 					m_numSamples;     		// the number of sample points in a set
		int 					m_numSets;				// the number of sample sets
		std::vector<Point2D>	m_samples;				// sample points on a unit square
		std::vector<int>		m_shuffledIndices;		// shuffled samples array indices
		std::vector<Point2D>	m_diskSamples;			// sample points on a unit disk
		std::vector<Point3D> 	m_hemisphereSamples;	// sample points on a unit hemisphere
		std::vector<Point3D> 	m_sphereSamples;		// sample points on a unit sphere
		unsigned long 			m_counts[4];			// the current number of sample points used
		int 					m_jumps[4];				// random index jump

		RefCounter				m_counter;
};



inline void
Sampler::SetNumSamples(const int num) 
{
	m_numSamples = num;
}


inline int
Sampler::GetNumSamples(void) const 
{
	return (m_numSamples);
}


inline void
Sampler::SetNumSets(const int num) 
{
	m_numSets = num;
}


inline int
Sampler::GetNumSets(void) const 
{
	return (m_numSets);
}


inline void
Sampler::ShuffleCoords(void) 
{
	ShuffleXCoords();
	ShuffleYCoords();
}


inline void
Sampler::GenerateSamples(const int num, const int nsets) 
{
	m_numSamples	= num;
	m_numSets		= nsets;
	GenerateSamples();
}


inline Sampler*
Sampler::Release(void) 
{
	m_counter.Release();
	return this;
}


inline Sampler*
Sampler::AddRef(void) 
{
	m_counter.AddRef();
	return this;
}


inline int
Sampler::GetRef(void) const 
{
	return (m_counter.GetRef());
}


#endif
