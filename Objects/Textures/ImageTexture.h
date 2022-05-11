//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __IMAGE_TEXTURE__
#define __IMAGE_TEXTURE__


#include "../Textures/Image.h"
#include "../Textures/Mapping.h"
#include "../Textures/Texture.h"

class ImageTexture: public Texture {
	public:

		ImageTexture(void);

		ImageTexture(Image* ip);

		ImageTexture(const ImageTexture& other);

		ImageTexture&
		operator= (const ImageTexture& rhs);

		virtual ImageTexture*
		Clone(void) const;

		virtual
		~ImageTexture(void) ;

		virtual RGBColor
		GetColor(const ShadeContext& sr) const;

		void
		SetImage(Image* ip);

		void
		SetMapping(Mapping* mp);

		int
		GetWidth(void) const;

		int
		GetHeight(void) const;


	private:

		int 		m_hres;			// horizontal resolution of the image
		int			m_vres;			// vertical resolution of the image
		Image*		m_pImage;		// the image
		Mapping*	m_pMapping;		// mapping technique used, if any
};



inline int
ImageTexture::GetWidth(void) const
{
	return (m_hres);
}


inline int
ImageTexture::GetHeight(void) const
{
	return (m_vres);
}


#endif