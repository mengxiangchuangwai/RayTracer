// 	Copyright (C) Kevin Suffern 2000-2007.
// 	Copyright (C) Stefan Brumme 2005.
// 	Copyright (C) Sverre Kvaale 2007.
//	This C++ code is for non-commercial purposes only.
//	This C++ code is licensed under the GNU General Public License Version 2.
//	See the file COPYING.txt for the full license.


#include <iostream>
#include <cstdio>
#include "../Utilities/Constants.h"
#include "../Textures/Image.h"

Image::Image(void)
	: m_hres(100)
	, m_vres(100)
{}


Image::Image(const Image& other)
	: m_hres(other.m_hres)
	, m_vres(other.m_vres)
	, m_buff(other.m_buff)
{}


Image&
Image::operator= (const Image& rhs) 
{
	if( this == &rhs )
		return (*this);

	m_hres 		= rhs.m_hres;
	m_vres 		= rhs.m_vres;
	m_buff 		= rhs.m_buff;

	return (*this);
}


Image::~Image(void)	
{}


void
Image::ReadFilePPM(const char* pFileName) 
{
    // read-only binary sequential access

    FILE* file = fopen(pFileName, "rb");

    if( file == 0 )
		std::cout << "could not open file" << std::endl;
	else
		std::cout << "file opened" << std::endl;

    // PPM header

    unsigned char type;
    if( fscanf(file, "P%c\n", &type) != 1 )
		std::cout << "Invalid PPM signature" << std::endl;

    // only binary PPM supported

    if( type != '6' )
		std::cout << "Only binary PPM supported" << std::endl;

    // skip comments

    unsigned char dummy;
    while( fscanf(file ,"#%c", &dummy) )
        while( fgetc(file) != '\n');

    // read image size

    if( fscanf(file, "%d %d\n", &m_hres, &m_vres) != 2 )
		std::cout << "Invalid image size" << std::endl;

    if( m_hres <= 0 )
		std::cout << "Invalid image width" << std::endl;
	else
		std::cout << "hres = " << m_hres << std::endl;


	if( m_vres <= 0 )
		std::cout << "Invalid image height" << std::endl;
	else
		std::cout << "vres = " << m_vres << std::endl;


    // maximum value to be found in the PPM file (usually 255)

    unsigned int maxValue;
    if( fscanf(file, "%d\n", &maxValue) != 1 )
		std::cout << "Invalid max value" << std::endl;

	float invMaxValue = 1.0 / (float)maxValue;

    // allocate memory

	m_buff.reserve(m_hres * m_vres);

    // read pixel data

    for( int y = 0; y < m_vres; ++y ) 
	{
        for( int x = 0; x < m_hres; ++x ) 
		{
            unsigned char red;
            unsigned char green;
            unsigned char blue;

            if( fscanf(file, "%c%c%c", &red, &green, &blue) != 3 )
				std::cout << "Invalid image" << std::endl;

			float r = red   * invMaxValue;
			float g = green * invMaxValue;
			float b = blue  * invMaxValue;

			m_buff.push_back(RGBColor(r, g, b));
        }
    }

    // close file

    fclose(file);

	std::cout << "finished reading PPM file" << std::endl;
}


RGBColor
Image::GetColor(const int row, const int column) const 
{
	unsigned int index = column + m_hres * (m_vres - row - 1);
//	unsigned int index = column + m_hres * row;
	

	if( index < m_buff.size() )
		return (m_buff[index]);
	else
		return (RED);    // useful for debugging
}