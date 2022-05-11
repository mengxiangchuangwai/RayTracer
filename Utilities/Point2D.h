//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __POINT_2D__
#define __POINT_2D__


class Point2D {
	public:

		float x, y;


	public:
	
		Point2D(void);										
		
		Point2D(const float val);							
		
		Point2D(const float x1, const float y1);			
		
		Point2D(const Point2D& rhs); 		

		~Point2D(void);									

		Point2D& 											
		operator= (const Point2D& rhs);

		Point2D
		operator* (float val);

		void 
		Set(const float x1, const float y1);

		void
		Get(float& x1, float& y1) const;
};



inline Point2D
Point2D::operator* (float val) 
{
	return (Point2D(val * x, val * y));
}


inline void 
Point2D::Set(const float x1, const float y1) 
{
	x = x1;
	y = y1;
}


inline void
Point2D::Get(float& x1, float& y1) const 
{
	x1 = x;
	y1 = y;
}


#endif
