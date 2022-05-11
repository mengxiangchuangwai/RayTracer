//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __JITTERED__
#define __JITTERED__


#include "../Samplers/Sampler.h"

class Jittered: public Sampler {
	public:

		Jittered(void);

		Jittered(const int numSamples);

		Jittered(const int numSamples, const int numSets);

		Jittered(const Jittered& other);

		Jittered&
		operator= (const Jittered& rhs);

		virtual Jittered*
		Clone(void) const;

		virtual
		~Jittered(void);

		virtual void
		GenerateSamples(void);
};


#endif