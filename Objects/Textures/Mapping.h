//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __MAPPING__
#define __MAPPING__


#include <cmath>
#include "../Utilities/RefCounter.h"
#include "../Utilities/Point3D.h"


class Mapping {
	public:

		Mapping(void);

		Mapping(const Mapping& other);

		Mapping&
		operator= (const Mapping& rhs);

		virtual Mapping*
		Clone(void) const = 0;

		virtual 
		~Mapping(void);

		virtual void
		GetTexelCoords(	const 	Point3D& 	localHitPoint,
						const 	int 		xres,
						const 	int 		yres,
								int& 		row,
								int& 		column ) const = 0;

		Mapping*
		Release(void);

		Mapping*
		AddRef(void);

		int
		GetRef(void) const;


	private:

		RefCounter	m_counter;
};



inline Mapping*
Mapping::Release(void) 
{
	m_counter.Release();
	return this;
}


inline Mapping*
Mapping::AddRef(void) 
{
	m_counter.AddRef();
	return this;
}


inline int
Mapping::GetRef(void) const 
{
	return (m_counter.GetRef());
}



#endif