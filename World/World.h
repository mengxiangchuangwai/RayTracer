//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __WORLD__
#define __WORLD__


// The World class does not have a copy constructor or an assignment operator, for the followign reasons:

// 1 	There's no need to copy construct or assign the World
// 2 	We wouldn't want to do this anyway, because the world can contain an arbitray amount of data
// 3 	These operations wouldn't work because the world is self-referencing:
//	 	the Tracer base class contains a pointer to the world. If we wrote a correct copy constructor for the
// 	  	Tracer class, the World copy construtor would call itself recursively until we ran out of memory.


#include <vector>
#include "../World/ViewPlane.h"
#include "../Utilities/RGBColor.h"
#include "../Utilities/Ray.h"
#include "../Utilities/Lock.h"
#include "../Tracers/Tracer.h"
#include "../Objects/GeometricObject.h"
#include "../Objects/Sphere.h"

#include "../Cameras/Camera.h"
#include "../Lights/Light.h"
#include "../Lights/Ambient.h"

typedef std::vector<int>				ColorBuffer;
typedef std::vector<GeometricObject*>	ObjectArray;
typedef std::vector<Light*>				LightArray;

class World {
	public:

		World(void);

		virtual 
		~World(void);

		const ViewPlane&
		GetViewPlane(void) const;

		const RGBColor&
		GetBackgroundColor(void) const;

		Tracer*
		GetTracer(void) const;

		Camera*
		GetCamera(void) const;

		Light*
		GetAmbient(void) const;

		void
		AddObject(GeometricObject* pObject);

		void
		AddLight(Light* pLight);

		void 
		SetBackgroundColor(const RGBColor& c);
		
		void
		SetBackgroundColor(const float r, const float g, const float b);

		void
		SetBackgroundColor(const float c);

		void
		SetTracer(Tracer* pTracer);

		void
		SetCamera(Camera* pCamera);

		void
		SetAmbientLight(Light* pAmbient);

		void
		SaveColor(const int row, const int column, const RGBColor& value) const;

		void
		SaveColors( const int firstRow, const int numRows, const RGBColor* pColors) const;

		void 
		SetupFrameBuffer(const int width, const int height);

		ShadeContext
		TestObjects(const Ray& ray);

		void
		SaveToPPM(void) const;

		void
		Build(void);

		void
		RenderScene(void) const;


	public:

		ObjectArray			m_objects;		
		LightArray			m_lights;


	protected:

		ViewPlane			m_vp;
		RGBColor			m_bgcolor;

		Tracer*				m_pTracer;
		Camera*				m_pCamera;
		Light*				m_pAmbient;

		mutable ColorBuffer	m_imageBuffer;
		int					m_imageWidth;
		int					m_imageHeight;

		void
		DeleteObjects(void);

		void
		DeleteLights(void);
};



inline const ViewPlane&
World::GetViewPlane(void) const
{
	return (m_vp);
}


inline void 
World::SetBackgroundColor(const RGBColor& c)
{
	m_bgcolor = c;
}


inline void
World::SetBackgroundColor(const float r, const float g, const float b)
{
	m_bgcolor.Set(r, g, b);
}

		
inline void
World::SetBackgroundColor(const float c)
{
	m_bgcolor.Set(c, c, c);
}


inline const RGBColor&
World::GetBackgroundColor(void) const
{
	return (m_bgcolor);
}


inline Tracer*
World::GetTracer(void) const
{
	return (m_pTracer);
}


inline Camera*
World::GetCamera(void) const
{
	return (m_pCamera);
}


inline Light*
World::GetAmbient(void) const
{
	return (m_pAmbient);
}


inline void
World::SaveColor(const int row, const int column, const RGBColor& value) const 
{
	RGBColor result = (m_vp.IsBeyondGamutShow() ? ClampColorToRed(value) : NormalizeColor(value));
	
	if( m_vp.GetGamma() != 1.0 )
		result = result.Powc(m_vp.GetInverseGamma());

	int index = row * m_imageWidth * 3 + column * 3;
	m_imageBuffer[index++] = (int)(result.r * 255);
	m_imageBuffer[index++] = (int)(result.g * 255);
	m_imageBuffer[index]   = (int)(result.b * 255);
}


inline void
World::SaveColors( const int firstRow, const int numRows, const RGBColor* pColors) const
{
	int cursor = 0;
	RGBColor result;

	for( int r = firstRow; r < firstRow + numRows; ++r )
	{
		for( int c = 0; c < m_vp.GetHres(); ++c)
		{
			result = (m_vp.IsBeyondGamutShow() ? ClampColorToRed(pColors[cursor++]) : NormalizeColor(pColors[cursor++]));

			if( m_vp.GetGamma() != 1.0 )
				result = result.Powc(m_vp.GetInverseGamma());

			int index = r * m_imageWidth * 3 + c * 3;
			m_imageBuffer[index++] = (int)(result.r * 255);
			m_imageBuffer[index++] = (int)(result.g * 255);
			m_imageBuffer[index]   = (int)(result.b * 255);
		}
	}
}


#endif
