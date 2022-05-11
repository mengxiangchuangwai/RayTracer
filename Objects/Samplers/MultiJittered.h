//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __MULTI_JITTERED__
#define __MULTI_JITTERED__


#include "../Samplers/Sampler.h"

class MultiJittered: public Sampler {
	public:

		MultiJittered(void);

		MultiJittered(const int numSamples);

		MultiJittered(const int numSamples, const int numSets);

		MultiJittered(const MultiJittered& other);

		MultiJittered&
		operator= (const MultiJittered& rhs);

		virtual MultiJittered*
		Clone(void) const;

		virtual
		~MultiJittered(void);

		virtual void
		GenerateSamples(void);
};


#endif

