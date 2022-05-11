//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __RGB_COLOR__
#define __RGB_COLOR__


#include <cmath>
#include "../Utilities/maths.h"

class RGBColor {

	public:
	
		float	r, g, b;			

				
	public:
	
		RGBColor(void);										// default constructor
		
		RGBColor(float val);								// constructor
		
		RGBColor(float r1, float g1, float b1);				// constructor
		
		RGBColor(const RGBColor& c); 						// copy constructor
		
		~RGBColor(void);									// destructor
		
		RGBColor& 											// assignment operator
		operator= (const RGBColor& rhs); 

		RGBColor 											// addition
		operator+ (const RGBColor& c) const;	

		RGBColor& 											// compound addition
		operator+= (const RGBColor& c);
		
		RGBColor 											// subtraction
		operator- (const RGBColor& c) const;	

		RGBColor& 											// compound subtraction
		operator-= (const RGBColor& c);

		RGBColor 											// multiplication by a float on the right
		operator* (const float val) const;
		
		RGBColor& 											// compound multiplication by a float on the right
		operator*= (const float val);					
				
		RGBColor 											// division by a float
		operator/ (const float val) const;
		
		RGBColor& 											// compound division by a float
		operator/= (const float val); 
				
		RGBColor 											// component-wise multiplication
		operator* (const RGBColor& c) const;
		
		bool												// are two RGBColours the same?
		operator== (const RGBColor& c) const;				

		RGBColor											// raise components to a power
		Powc(const float p) const;
		
		float												// the average of the components
		Average(void) const;

		void
		Set(const float r1, const float g1, const float b1);// set the values of a color

		void 
		Get(float& r1, float& g1, float& b1) const;			// get the values of a color


		static const RGBColor Black;
		static const RGBColor White;
		static const RGBColor Red;
		static const RGBColor Yellow;
		static const RGBColor DarkYellow;
		static const RGBColor Brown;
		static const RGBColor Orange;
		static const RGBColor Green;
		static const RGBColor LightGreen;
		static const RGBColor DarkGreen;
		static const RGBColor LightPurple;
		static const RGBColor DarkPurple;
		static const RGBColor Grey;


		#define BLACK			RGBColor::Black
		#define WHITE			RGBColor::White
		#define RED				RGBColor::Red
		#define YELLOW			RGBColor::Yellow
		#define DARK_YELLOW		RGBColor::DarkYellow
		#define BROWN			RGBColor::Brown
		#define ORANGE			RGBColor::Orange
		#define GREEN			RGBColor::Green
		#define LIGHT_GREEN		RGBColor::LightGreen
		#define DARK_GREEN		RGBColor::DarkGreen
		#define LIGHT_PURPLE	RGBColor::LightPurple
		#define DARK_PURPLE		RGBColor::DarkPurple
		#define GREY			RGBColor::Grey 	
};



// addition of two colors

inline RGBColor 
RGBColor::operator+ (const RGBColor& c) const 
{
	return (RGBColor(r + c.r, g + c.g, b + c.b));
}


// compound addition of two colors

inline RGBColor& 
RGBColor::operator+= (const RGBColor& c) 
{
	r += c.r; g += c.g; b += c.b;
    return (*this);
}


// subtraction of two colors

inline RGBColor 
RGBColor::operator- (const RGBColor& c) const 
{
	return (RGBColor(r - c.r, g - c.g, b - c.b));
}


// compound subtraction of two colors

inline RGBColor& 
RGBColor::operator-= (const RGBColor& c) 
{
	r -= c.r; g -= c.g; b -= c.b;
    return (*this);
}


// multiplication by a float on the right

inline RGBColor 
RGBColor::operator* (const float val) const 
{
	return (RGBColor (r * val, g * val, b * val));	
}


// compound multiplication by a float on the right

inline RGBColor& 
RGBColor::operator*= (const float val) 
{
	r *= val; g *= val; b *= val;
	return (*this);
}


// division by float

inline RGBColor 
RGBColor::operator/ (const float val) const 
{
	return (RGBColor (r / val, g / val, b / val));
}


// compound division by float

inline RGBColor& 
RGBColor::operator/= (const float val) 
{	
	r /= val; g /= val; b /= val;
	return (*this);
}


// component-wise multiplication of two colors

inline RGBColor 
RGBColor::operator* (const RGBColor& c) const 
{
	return (RGBColor (r * c.r, g * c.g, b * c.b));
} 


// are two RGBColors the same?

inline bool
RGBColor::operator== (const RGBColor& c) const 
{
	return (r == c.r && g == c.g && b == c.b);
}


// the average of the three components

inline float											
RGBColor::Average(void) const 
{
	return (float)(0.333333333333 * (r + g + b));
}


// set the values of a color

inline void
RGBColor::Set(const float r1, const float g1, const float b1) 
{
	r = r1; g = g1; b = b1;
}


// get the values of a color

inline void 
RGBColor::Get(float& r1, float& g1, float& b1) const 
{
	r1 = r; g1 = g; b1 = b;
}


// raise each component to the specified power

inline RGBColor
RGBColor::Powc(const float p) const 
{
	RGBColor result(r, g, b);

	if( r != 1.0 && r != 0.0 )
		result.r = pow(r, p);

	if( g != 1.0 && g != 0.0 )
		result.g = pow(g, p);

	if( b != 1.0 && b != 0.0 )
		result.b = pow(b, p);

	return result;
}


// multiplication by a float on the left

RGBColor 
operator* (const float a, const RGBColor& c);

inline RGBColor 
operator* (const float a, const RGBColor& c) 
{
	return (RGBColor (a * c.r, a * c.g, a * c.b));	
}


RGBColor
NormalizeColor(const RGBColor& c);

inline RGBColor
NormalizeColor(const RGBColor& color)
{
	float maxc = max2(color.r, max2(color.g, color.b));
	return (maxc > 1.0 ? (color / maxc) : color);
}


// Set color to red if any component is greater than one

RGBColor
ClampColorToRed(const RGBColor& c);

inline RGBColor
ClampColorToRed(const RGBColor& color)
{
	RGBColor result(color);

	if( color.r > 1.0 || color.g > 1.0 || color.b > 1.0) 
	{
		result.r = 1.0; result.g = 0.0; result.b = 0.0;
	}

	return (result);
}


#endif