//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __NORMAL__
#define __NORMAL__


#include "../Utilities/Matrix.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"

class Normal {	
	public:
	
		double	x, y, z;

				
	public:
	
		Normal(void);										// default constructor
		
		Normal(double a);									// constructor
		
		Normal(double x1, double y1, double z1);			// constructor
		
		Normal(const Normal& n); 							// copy constructor
		
		Normal(const Vector3D& v);							// constructs a normal from a vector
		
		~Normal(void);										// destructor

		Normal& 											// assignment operator
		operator= (const Normal& rhs); 	
		
		Normal& 											// assignment of a vector to a normal
		operator= (const Vector3D& rhs);
		
		Normal& 											// assignment of a point to a normal
		operator= (const Point3D& rhs);
		
		Normal 												// unary minus
		operator- (void) const;	
		
		Normal 												// addition
		operator+ (const Normal& n) const;
		
		Normal& 											// compound addition
		operator+= (const Normal& n);
		
		double
		operator* (const Vector3D& v) const;				// dot product with a vector on the right
		
		Normal 												// multiplication by a double on the right
		operator* (const double a) const;
				
		void 												// convert normal to a unit normal
		Normalize(void); 									 		

		void 
		Set(const double x1, const double y1, const double z1);	// set the values

		void
		Get(double& x1, double& y1, double& z1) const;		// get the values
};


// unary minus

inline Normal 											
Normal::operator- (void) const 
{
	return (Normal(-x, -y, -z));
}


// addition of two normals

inline Normal 											
Normal::operator+ (const Normal& n) const 
{
	return (Normal(x + n.x, y + n.y, z + n.z));
}


// compound addition of two normals

inline Normal& 
Normal::operator+= (const Normal& n) 
{
	x += n.x; y += n.y; z += n.z;
    return (*this);
}


// dot product of a normal on the left and a vector on the right

inline double
Normal::operator* (const Vector3D& v) const 
{
	return (x * v.x + y * v.y + z * v.z);
}


// multiplication by a double on the right

inline Normal
Normal::operator* (const double a) const 
{
	return (Normal(x * a, y * a, z * a));
}


// set the values

inline void 
Normal::Set(const double x1, const double y1, const double z1) 
{
	x = x1;
	y = y1;
	z = z1;
}


// get the values

inline void
Normal::Get(double& x1, double& y1, double& z1) const 
{
	x1 = x;
	y1 = y;
	z1 = z;
}


// multiplication by a double on the left

Normal											// prototype
operator* (const double a, const Normal& n);

inline Normal
operator*(const double f, const Normal& n) 
{
	return (Normal(f * n.x, f * n.y,f * n.z));
}


// addition of a vector on the left to return a vector 

Vector3D										// prototype
operator+ (const Vector3D& v, const Normal& n);

inline Vector3D
operator+ (const Vector3D& v, const Normal& n) 
{	
	return (Vector3D(v.x + n.x, v.y + n.y, v.z + n.z));
}	


// subtraction of a normal from a vector to return a vector

Vector3D
operator- (const Vector3D&, const Normal& n);

inline Vector3D
operator- (const Vector3D& v, const Normal& n) 
{
	return (Vector3D(v.x - n.x, v.y - n.y, v.z - n.z));
}


// dot product of a vector on the left and a normal on the right

double
operator* (const Vector3D& v, const Normal& n);

inline double
operator* (const Vector3D& v, const Normal& n) 
{
	return (v.x * n.x + v.y * n.y + v.z * n.z);     
}


// multiplication by a matrix on the left

Normal 												// prototype							
operator* (const Matrix& mat, const Normal& n);


#endif