//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __LIGHT_PROBE__
#define __LIGHT_PROBE__


#include "../Utilities/Constants.h"
#include "../Textures/Mapping.h"

typedef enum {
	LP_Default, 
	LP_Panoramic
} LightProbeType;

class LightProbe: public Mapping {
	public:

		LightProbe(void);

		LightProbe(const LightProbe& other);

		LightProbe&
		operator= (const LightProbe& rhs);

		virtual LightProbe*
		Clone(void) const;

		virtual 
		~LightProbe(void);

		virtual void
		GetTexelCoords(	const 	Point3D& 	localHitPoint,
						const 	int 		xres,
						const 	int 		yres,
								int& 		row,
								int& 		column ) const;

		void 
		SetMapType(const LightProbeType val);

		LightProbeType 
		GetMapType(void) const;


	private:
		LightProbeType m_mapType;
};



inline void 
LightProbe::SetMapType(const LightProbeType val)
{
	m_mapType = val;
}


inline LightProbeType 
LightProbe::GetMapType(void) const
{
	return (m_mapType);
}


#endif