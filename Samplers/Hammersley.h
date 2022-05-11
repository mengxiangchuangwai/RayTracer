//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __HAMMERSLEY__
#define __HAMMERSLEY__


#include "../Samplers/Sampler.h"

class Hammersley: public Sampler {
	public:
		
		Hammersley(void);							
		
		Hammersley(const int numSamples);

		Hammersley(const int numSamples, const int numSets);					

		Hammersley(const Hammersley& other);			

		Hammersley& 
		operator= (const Hammersley& rhs);			

		virtual Hammersley*							
		Clone(void) const;

		virtual
		~Hammersley(void);

		virtual void
		GenerateSamples(void);
		
	private:
		
		double 
		Phi(int num);	
};


#endif