//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __SPHERE_CHECKER__
#define __SPHERE_CHECKER__


#include "../Textures/Texture.h"

// For checkers that are approximately square at the "equator" (polar angle theta = 90 degrees), there should be
// twice as many horizontal_checkers as vertical_checkers

class SphereChecker: public Texture {		
	public:
	
		SphereChecker(void);										
		
		SphereChecker(const SphereChecker& other);
		
		SphereChecker& 												
		operator= (const SphereChecker& rhs);		

		virtual SphereChecker*							
		Clone(void) const;				

		~SphereChecker(void);						
		
		virtual RGBColor																				
		GetColor(const ShadeContext& sr) const;
				
		void													
		SetNumHorizontalCheckers(const int num);
		
		void													
		SetNumVerticalCheckers(const int num);
		
		void													
		SetHorizontalLineWidth(const float val);
		
		void													
		SetVerticalLineWidth(const float val);
								
		void																	
		SetColor1(const float r, const float g, const float b);
		
		void																
		SetColor1(const float c);	
		
		void																
		SetColor1(const RGBColor& c);
		
		void																	
		SetColor2(const float r, const float g, const float b);
		
		void																
		SetColor2(const float c);	
		
		void																
		SetColor2(const RGBColor& c);									
		
		void																	
		SetLineColor(const float r, const float g, const float b); 
		
		void																	
		SetLineColor(const float c);
		
		void																
		SetLineColor(const RGBColor& c);	

		
	private:
	
		int			m_horizCheckers;		// number of checkers in the horizontal (azithum) direction
		int			m_vertCheckers;			// number of checkers in the vertical (polar) direction
		float		m_horizLineWidth;		// height of the horizontal lines as a fraction of the checker width
		float		m_vertLineWidth;		// width of the vertical lines as a fraction of the checker height
		RGBColor	m_color1;				// checker color 1
		RGBColor	m_color2;				// checker color 2
		RGBColor	m_lineColor;			// the outline color									
};



inline void													
SphereChecker::SetNumHorizontalCheckers(const int num) 
{
	m_horizCheckers = num;
}


inline void													
SphereChecker::SetNumVerticalCheckers(const int num) 
{
	m_vertCheckers = num;
}


inline void													
SphereChecker::SetHorizontalLineWidth(const float val) 
{
	m_horizLineWidth = val;
}


inline void													
SphereChecker::SetVerticalLineWidth(const float val) 
{
	m_vertLineWidth = val;
}


inline void																	
SphereChecker::SetColor1(const float r, const float g, const float b) 
{
	m_color1.Set(r, g, b);
}


inline void																
SphereChecker::SetColor1(const float c) 
{
	m_color1.Set(c, c, c);
}


inline void																
SphereChecker::SetColor1(const RGBColor& c) 
{
	m_color1 = c;
}


inline void																	
SphereChecker::SetColor2(const float r, const float g, const float b) 
{
	m_color2.Set(r, g, b);
}


inline void																
SphereChecker::SetColor2(const float c) 
{
	m_color2.Set(c, c, c);
}


inline void																
SphereChecker::SetColor2(const RGBColor& c) 
{
	m_color2 = c;
}											


inline void																	
SphereChecker::SetLineColor(const float r, const float g, const float b) 
{
	m_lineColor.Set(r, g, b);
}


inline void																	
SphereChecker::SetLineColor(const float c) 
{
	m_lineColor.Set(c, c, c);
}


inline void																	
SphereChecker::SetLineColor(const RGBColor& c) 
{
	m_lineColor = c;
}


#endif