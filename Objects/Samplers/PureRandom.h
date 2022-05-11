//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __PURE_RANDOM__
#define __PURE_RANDOM__


#include "../Samplers/Sampler.h"

class PureRandom: public Sampler {
	public:

		PureRandom(void);

		PureRandom(const int numSamples);

		PureRandom(const int numSamples, const int numSets);

		PureRandom(const PureRandom& other);

		PureRandom&
		operator= (const PureRandom& rhs);

		virtual PureRandom*
		Clone(void) const;

		virtual
		~PureRandom(void);

		virtual void
		GenerateSamples(void);
};


#endif
