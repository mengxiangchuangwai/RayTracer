//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Textures/ImageTexture.h"

ImageTexture::ImageTexture(void)
	: Texture()
	, m_hres(0)
	, m_vres(0)
	, m_pImage(NULL)
	, m_pMapping(NULL)
{}


ImageTexture::ImageTexture(Image* ip)
	: Texture()
	, m_hres(ip->GetHres())
	, m_vres(ip->GetVres())
	, m_pImage(ip)
	, m_pMapping(NULL)
{}


ImageTexture::ImageTexture(const ImageTexture& other)
	: Texture(other)
	, m_hres(other.m_hres)
	, m_vres(other.m_vres)
{
	if( other.m_pImage )
		m_pImage = new Image(*other.m_pImage);
	else
		m_pImage = NULL;

	if( other.m_pMapping )
		m_pMapping = other.m_pMapping->Clone();
	else
		m_pMapping = NULL;
}


ImageTexture&
ImageTexture::operator= (const ImageTexture& rhs) 
{
	if( this == &rhs )
		return (*this);

	Texture::operator= (rhs);

	m_hres = rhs.m_hres;
	m_vres = rhs.m_vres;

	SAFE_DELETE(m_pImage);

	if( rhs.m_pImage )
		*m_pImage = *rhs.m_pImage;

	SAFE_DELETE(m_pMapping);

	if( rhs.m_pMapping )
		m_pMapping = rhs.m_pMapping->Clone();

	return (*this);

}


ImageTexture*
ImageTexture::Clone(void) const 
{
	return (new ImageTexture (*this));
}


ImageTexture::~ImageTexture (void) 
{
	SAFE_DELETE(m_pImage);
	SAFE_DELETE(m_pMapping);
}


// When we ray trace a triangle mesh object with uv mapping, the mapping pointer may be NULL
// because we can define uv coordinates on an arbitrary triangle mesh.
// In this case we don't use the local hit point because the pixel coordinates are computed
// from the uv coordinates stored in the ShadeContext object in the uv triangles' hit functions
// See, for example, Listing 29.12.

RGBColor
ImageTexture::GetColor(const ShadeContext& sr) const 
{
	int row;
	int col;

	if( m_pMapping )
		m_pMapping->GetTexelCoords(sr.localHitPoint, m_hres, m_vres, row, col);
	else {
		row = (int)(sr.tv * (m_vres - 1));
		col = (int)(sr.tu * (m_hres - 1));
	}

	return (m_pImage->GetColor(row, col));
}


void
ImageTexture::SetImage(Image* ip) 
{
	SAFE_DELETE(m_pImage);

	if( m_pImage = ip ) 
	{
        m_hres = m_pImage->GetHres();
        m_vres = m_pImage->GetVres();
    }
}


void
ImageTexture::SetMapping(Mapping* mp) 
{
	SAFE_DELETE(m_pMapping);
	m_pMapping = mp;
}