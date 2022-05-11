//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __N_ROOKS__
#define __N_ROOKS__


#include "../Samplers/Sampler.h"

class NRooks: public Sampler {
	public:

		NRooks(void);

		NRooks(const int numSamples);

		NRooks(const int numSamples, const int numSets);

		NRooks(const NRooks& other);

		NRooks&
		operator= (const NRooks& rhs);

		virtual NRooks*
		Clone(void) const;

		virtual
		~NRooks(void);

		virtual void
		GenerateSamples(void);
};


#endif