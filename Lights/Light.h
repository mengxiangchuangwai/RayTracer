//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __LIGHT__
#define __LIGHT__


#include "../Utilities/Vector3D.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/ShadeContext.h"
#include "../Utilities/Ray.h"
#include "../Utilities/Lock.h"

class Light {
	public:

		Light(void);

		Light(const Light& other);

		Light&
		operator= (const Light& rhs);

		virtual Light*
		Clone(void) const = 0;

		virtual
		~Light(void);

		virtual Vector3D
		GetDirection(ShadeContext& sr) = 0;

		virtual RGBColor
		L(ShadeContext& sr);

		virtual bool
    	InShadow(const Ray& ray, const ShadeContext& sr) const;

    	virtual float
		G(const ShadeContext& sr) const;

		virtual float
		Pdf(const ShadeContext &sr) const;

		virtual void 
		BeginSection(void);

		virtual void
		EndSection(void);

		void
    	SetShadows(bool val);

	    bool
	    CastsShadows(void) const;


	protected:
		
		bool m_shadowing;
		CriticalSection m_cs;
};



inline RGBColor
Light::L(ShadeContext& sr) 
{
	return (BLACK);
}


inline bool
Light::InShadow(const Ray &ray, const ShadeContext &sr) const 
{
    return false;
}


inline float
Light::G(const ShadeContext& sr) const 
{
	return 1.0f;
};


inline float
Light::Pdf(const ShadeContext &sr) const 
{
    return 1.0;
}


inline void 
Light::BeginSection(void)
{
	// m_cs.Lock();
}


inline void
Light::EndSection(void)
{
	// m_cs.unlock();
}


inline void
Light::SetShadows(bool val) 
{
    m_shadowing = val;
}


inline bool
Light::CastsShadows(void) const
{
    return m_shadowing;
}


#endif