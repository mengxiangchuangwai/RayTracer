//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __VECTOR_3D__
#define __VECTOR_3D__


#include "../Utilities/Matrix.h"

class Normal;
class Point3D;

class Vector3D {
	public:
	
		double	x, y, z;


	public:
	
		Vector3D(void);											// default constructor
		
		Vector3D(double val);									// constructor
		
		Vector3D(double x1, double y1, double z1);				// constructor
		
		Vector3D(const Vector3D& v);							// copy constructor
		
		Vector3D(const Normal& n);								// constructs a vector from a Normal
		
		Vector3D(const Point3D& p);								// constructs a vector from a point

		~Vector3D (void);										// destructor

		Vector3D& 												// assignment operator
		operator= (const Vector3D& rhs);
		
		Vector3D& 												// assign a Normal to a vector
		operator= (const Normal& rhs); 
		
		Vector3D& 												// assign a Point3D to a vector
		operator= (const Point3D& rhs); 
		
		Vector3D												// unary minus
		operator- (void) const;									
				
		double													// length
		Length(void);
		
		double													// square of the length
		LengthSq(void);
		
		Vector3D												// multiplication by a double on the right
		operator* (const double val) const;
				
		Vector3D&
		operator*= (const double val);

		Vector3D												// division by a double
		operator/ (const double val) const;

		Vector3D&
		operator/= (const double val);
		
		Vector3D												// addition
		operator+ (const Vector3D& v) const;
		
		Vector3D& 												// compound addition
		operator+= (const Vector3D& v);					
		
		Vector3D												// subtraction
		operator- (const Vector3D& v) const;					
		
		Vector3D& 												// compound subtraction
		operator-= (const Vector3D& v);		

		double 													// dot product							
		operator* (const Vector3D& v) const;
		
		Vector3D 												// cross product				
		operator^ (const Vector3D& v) const;
		
		void 													// convert vector to a unit vector
		Normalize(void); 
		
		Vector3D& 												// return a unit vector, and normalize the vector												
		Hat(void);

		void 
		Set(const double x1, const double y1, const double z1);	// set the content of a vector

		void
		Get( double& x1, double& y1, double& z1) const;			// get the content of a vector

};



inline Vector3D 
Vector3D::operator- (void) const 
{
	return (Vector3D(-x, -y, -z));    
}


inline double													
Vector3D::LengthSq(void) 
{	
	return (x * x + y * y + z * z);
}


inline Vector3D
Vector3D::operator* (const double val) const 
{	
	return (Vector3D(x * val, y * val, z * val));	
}


inline Vector3D
Vector3D::operator/ (const double val) const 
{	
	return (Vector3D(x / val, y / val, z / val));	
}


inline Vector3D
Vector3D::operator+ (const Vector3D& v) const 
{
	return (Vector3D(x + v.x, y + v.y, z + v.z));
}


inline Vector3D
Vector3D::operator- (const Vector3D& v) const 
{
	return (Vector3D(x - v.x, y - v.y, z - v.z));
}


inline double 
Vector3D::operator* (const Vector3D& v) const 
{
	return (x * v.x + y * v.y + z * v.z);
} 


inline Vector3D 									
Vector3D::operator^ (const Vector3D& v) const 
{
	return (Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x));
}


inline Vector3D& 
Vector3D::operator*= (const double val) 
{
	x *= val; y *= val; z *= val;
	return (*this);
}


inline Vector3D& 
Vector3D::operator/= (const double val) 
{
	x /= val; y /= val; z /= val;
	return (*this);
}


inline Vector3D& 
Vector3D::operator+= (const Vector3D& v) 
{
	x += v.x; y += v.y; z += v.z;
	return (*this);
}


inline Vector3D& 
Vector3D::operator-= (const Vector3D& v) 
{
	x -= v.x; y -= v.y; z -= v.z;
	return (*this);
}


inline void 
Vector3D::Set(const double x1, const double y1, const double z1) 
{
	x = x1;
	y = y1;
	z = z1;
}


inline void
Vector3D::Get( double& x1, double& y1, double& z1) const 
{
	x1 = x;
	y1 = y;
	z1 = z;
}


Vector3D 											// prototype
operator* (const double a, const Vector3D& v);

inline Vector3D 
operator* (const double a, const Vector3D& v) 
{
	return (Vector3D(a * v.x, a * v.y, a * v.z));	
}


Vector3D 											// prototype
operator* (const Matrix& mat, const Vector3D& v);


#endif