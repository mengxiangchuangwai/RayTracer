//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __REGULAR__
#define __REGULAR__


#include "../Samplers/Sampler.h"

class Regular: public Sampler {
	public:

		Regular(void);

		Regular(const int numSamples);

		Regular(const int numSamples, const int numSets);

		Regular(const Regular& other);

		Regular&
		operator= (const Regular& rhs);

		virtual Regular*
		Clone(void) const;

		virtual
		~Regular(void);

		virtual void
		GenerateSamples(void);
};


#endif

