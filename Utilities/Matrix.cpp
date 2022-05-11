//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Utilities/Matrix.h"

Matrix::Matrix(void) 
{	
	for( int x = 0; x < 4; ++x )
		for( int y = 0; y < 4; ++y ) 
		{
			if( x == y )
				m[x][y] = 1.0;
			else
				m[x][y] = 0.0;
		}
}


Matrix::Matrix (const Matrix& rhs) 
{
	for( int x = 0; x < 4; ++x ) 
	{
		for( int y = 0; y < 4; ++y )			
			m[x][y] = rhs.m[x][y];	
	}
}


Matrix::~Matrix (void) 
{}   


Matrix& 
Matrix::operator= (const Matrix& rhs) 
{
	if( this == &rhs )
		return (*this);

	for( int x = 0; x < 4; ++x )
	{
		for( int y = 0; y < 4; ++y )			
			m[x][y] = rhs.m[x][y];	
	}

	return (*this);
}


Matrix 
Matrix::operator* (const Matrix& rhs) const 
{
	Matrix temp;
	
	for( int y = 0; y < 4; ++y )
		for( int x = 0; x < 4; ++x ) 
		{
			double sum = 0.0;

			for( int i = 0; i < 4; ++i )
				sum += m[x][i] * rhs.m[i][y];
 
			temp.m[x][y] = sum;			
		}
	
	return (temp);
}


Matrix 
Matrix::operator/ (const double d) 
{
	for( int x = 0; x < 4; ++x )				
		for( int y = 0; y < 4; ++y )			
			m[x][y] = m[x][y] / d;	

	return (*this);
}


void											
Matrix::SetIdentity(void) 
{
    for( int x = 0; x < 4; ++x )
		for( int y = 0; y < 4; ++y ) 
		{
			if( x == y )
				m[x][y] = 1.0;
			else
				m[x][y] = 0.0;
		}
}