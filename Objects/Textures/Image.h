// 	Copyright (C) Kevin Suffern 2000-2007.
// 	Copyright (C) Stefan Brumme 2005.
// 	Copyright (C) Sverre Kvaale 2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#ifndef __IMAGE__
#define __IMAGE__


// This is not a texture
// The Image class stores an image in PPM format
// This is used for image based textures, including ramp textures such as marble and sandstone
// I originally chose the PPM format because it's simple to parse

#include <vector>
#include "../Utilities/RefCounter.h"
#include "../Utilities/RGBColor.h"

typedef std::vector<RGBColor> RGBBuffer;

class Image {
	public:

		Image(void);

		Image(const Image& other);

		Image&
		operator= (const Image& rhs);

		virtual 
		~Image(void) ;

		void
		ReadFilePPM(const char* pFileName);

		int
		GetHres(void);

		int
		GetVres(void);

		RGBColor
		GetColor(const int row, const int col) const;

		virtual Image*
		Release(void);

		virtual Image*
		AddRef(void);

		virtual int
		GetRef(void) const;


	private:

		int 		m_hres;			// horizontal resolution of image
		int			m_vres;			// vertical resolution of image
		RGBBuffer	m_buff;
		RefCounter	m_counter;			
};



inline int
Image::GetHres(void) 
{
	return (m_hres);
}


inline int
Image::GetVres(void) 
{
	return (m_vres);
}


inline Image*
Image::Release(void) 
{
	m_counter.Release();
	return this;
}


inline Image*
Image::AddRef(void) 
{
	m_counter.AddRef();
	return this;
}


inline int
Image::GetRef(void) const 
{
	return (m_counter.GetRef());
}


#endif