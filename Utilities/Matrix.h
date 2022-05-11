//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __MATRIX__
#define __MATRIX__


class Matrix {
	
	public:
	
		double	m[4][4];								// elements

	
	public:
		
		Matrix(void);									// default constructor

		Matrix(const Matrix& rhs);						// copy constructor
		
		~Matrix (void);									// destructor
			
		Matrix& 										// assignment operator
		operator= (const Matrix& rhs); 	
			
		Matrix 											// multiplication of two matrices
		operator* (const Matrix& rhs) const;

		Matrix 											// divsion by a double
		operator/ (const double d);

		void											// set to the identity matrix
		SetIdentity(void);	
};


#endif


