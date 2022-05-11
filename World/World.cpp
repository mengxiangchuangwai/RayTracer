//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>

#include "../World/World.h"
#include "../Utilities/Constants.h"


// geometric objects

#include "../Objects/GeometricObject.h"
#include "../Objects/Plane.h"
#include "../Objects/Triangle.h"
#include "../Objects/Sphere.h"
#include "../Objects/SphereEmitter.h"
#include "../Objects/Cylinder.h"
#include "../Objects/PartialCylinder.h"
#include "../Objects/PartialCone.h"
#include "../Objects/PartialTorus.h"
#include "../Objects/PartialSphere.h"
#include "../Objects/OpenCone.h"
#include "../Objects/Cone.h"
#include "../Objects/Box.h"
#include "../Objects/Rectangle.h"
#include "../Objects/DiskEmitter.h"
#include "../Objects/Instance.h"
#include "../Objects/MeshGrid.h"
#include "../Objects/Grid.h"


// tracers

#include "../Tracers/RayCast.h"
#include "../Tracers/AreaLight.h"
#include "../Tracers/PathTrace.h"


// cameras

#include "../Cameras/Pinhole.h"
#include "../Cameras/FishEye.h"
#include "../Cameras/ThinLens.h"
#include "../Cameras/Spherical.h"
#include "../Cameras/Stereo.h"


// Samplers

#include "../Samplers/Regular.h"
#include "../Samplers/MultiJittered.h"


// lights

#include "../Lights/Directional.h"
#include "../Lights/PointLight.h"
#include "../Lights/EnvironmentLight.h"
#include "../Lights/AreaLightAdapter.h"
#include "../Lights/AmbientOccluder.h"


// materials

#include "../Materials/Matte.h"
#include "../Materials/Phong.h"
#include "../Materials/PerfectReflector.h"
#include "../Materials/GlossyReflector.h"
#include "../Materials/Emissive.h"
#include "../Materials/Transparent.h"
#include "../Materials/Dielectric.h"


// textures

#include "../Textures/ImageTexture.h"
#include "../Textures/PlaneChecker.h"
#include "../Textures/SphereChecker.h"
#include "../Textures/SphericalMap.h"
#include "../Textures/SquareMap.h"
#include "../Textures/CylindricalMap.h"
#include "../Textures/LightProbe.h"


// utilities

#include "../Utilities/RGBColor.h"
#include "../Utilities/Vector3D.h"
#include "../Utilities/Point3D.h"
#include "../Utilities/Normal.h"
#include "../Utilities/ShadeContext.h"
#include "../Utilities/Maths.h"
#include "../Utilities/Random.h"


World::World(void) 
	: m_bgcolor(BLACK)
	, m_pTracer(NULL)
	, m_pCamera(NULL)
	, m_pAmbient(new Ambient())
{}


World::~World(void) 
{
	if( m_pTracer ) 
	{
		delete m_pTracer;
		m_pTracer = NULL;
	}

	if( m_pCamera ) 
	{
		delete m_pCamera;
		m_pCamera = NULL;
	}

	if( m_pAmbient ) 
	{
		delete m_pAmbient;
		m_pAmbient = NULL;
	}

	DeleteObjects();
	DeleteLights();
}


void
World::AddObject(GeometricObject* pObject) 
{
	m_objects.push_back(pObject);
}


void
World::AddLight(Light* pLight) 
{
	for( size_t i = 0; i < m_lights.size(); ++i ) 
	{
		if( m_lights[i] == pLight ) 
		{
			pLight = pLight->Clone();
			break;
		}
	}

	m_lights.push_back(pLight);
}


void
World::SetTracer(Tracer* pTracer) 
{
	if( m_pTracer == pTracer )
		return;

	if( m_pTracer )
		delete m_pTracer;

	m_pTracer = pTracer;
}


void
World::SetCamera(Camera* pCamera) 
{
	if( m_pCamera == pCamera )
		return;

	if( m_pCamera )
		delete m_pCamera;

	m_pCamera = pCamera;
}


void
World::SetAmbientLight(Light* pAmbient) 
{
	if( m_pAmbient == pAmbient )
		return;

	if( m_pAmbient )
		delete m_pAmbient;

	m_pAmbient = pAmbient;
}


void 
World::SetupFrameBuffer(const int width, const int height) 
{
	m_imageWidth	= width;
	m_imageHeight	= height;
	m_imageBuffer.resize(width * height * 3);
}


ShadeContext
World::TestObjects(const Ray& ray) 
{
	ShadeContext	sr(this);
	double			tv;
	Normal			normal;
	Point3D			localHitPoint;
	Material*		pMaterial = NULL;
	double			tmin = kHugeValue;
	size_t 			num = m_objects.size();
	
	for( size_t i = 0; i < num; ++i ) 
	{
		sr.pMaterial = NULL;

		if( m_objects[i]->Hit(ray, tv, sr) && (tv < tmin) ) 
		{
            sr.isHit		= true;
			tmin 			= tv;
			pMaterial		= (NULL == sr.pMaterial ? m_objects[i]->GetMaterial() : sr.pMaterial);
			sr.hitPoint 	= ray.o + tv * ray.d;
			normal 			= sr.normal;
			localHitPoint	= sr.localHitPoint;
		}
	}

	if( sr.isHit ) 
	{
		sr.tval	= tmin;
		sr.normal = normal;
		sr.localHitPoint = localHitPoint;
		sr.pMaterial = pMaterial;
	}

	return(sr);
}


void
World::SaveToPPM(void) const 
{
	std::time_t tv = std::time(NULL);
	std::tm		lt = *std::localtime(&tv);
	std::stringstream ss;
	ss << "./Outputs/image_" << (lt.tm_year + 1900);
	
	if( lt.tm_mon + 1 < 10 )
		ss << 0;
	ss << (lt.tm_mon + 1);

	if( lt.tm_mday < 10 )
		ss << 0;
	ss << (lt.tm_mday);

	if( lt.tm_hour < 10 )
		ss << 0;
	ss << (lt.tm_hour);

	if( lt.tm_min < 10 )
		ss << 0;
	ss << (lt.tm_min);

	if( lt.tm_sec < 10 )
		ss << 0;
	ss << lt.tm_sec << ".ppm";

	std::ofstream ofs;
	ofs.open(ss.str().c_str(), std::ios::out | std::ios::binary);
	ofs << "P6\n" << m_imageWidth << " " << m_imageHeight << "\n255\n";

	int lineSize = m_imageWidth * 3;
	for( int i = m_imageHeight - 1; i > -1; --i )
	{
		for( int j = 0; j < lineSize; ++j )
			ofs << (unsigned char)(m_imageBuffer[j + i * lineSize]);
	}

	ofs.close();
}


void
World::Build(void) 
{

	/*
	int num_samples = 25;

	// view plane

	m_vp.set_hres(400);
	m_vp.set_vres(400);
	m_vp.set_pixel_size(0.5f);
	m_vp.set_samples(num_samples);


	m_pTracer = new RayCast(this);


	// camera

	Pinhole *pinhole_ptr = new Pinhole;
	pinhole_ptr->set_eye(0, 0, 500);
	pinhole_ptr->set_lookat(Point3D(0.0));
	pinhole_ptr->set_view_distance(600.0);
	pinhole_ptr->compute_uvw();
	set_camera(pinhole_ptr);


	// light

	Directional *light_ptr1 = new Directional;
	light_ptr1->set_direction(100, 100, 200);
	light_ptr1->scale_radiance(3.0);
	add_light(light_ptr1);

	// Matte material reflection coefficients - common to all materials

	float ka = 0.25;
	float kd = 0.75;


	// spheres


	Matte *matte_ptr1 = new Matte;
	matte_ptr1->set_ka(ka);
	matte_ptr1->set_kd(kd);
	matte_ptr1->set_cd(YELLOW);
	Sphere *sphere_ptr1 = new Sphere(Point3D(5, 3, 0), 30);
	sphere_ptr1->set_material(matte_ptr1);	   							// yellow
	add_object(sphere_ptr1);

	Matte *matte_ptr2 = new Matte;
	matte_ptr2->set_ka(ka);
	matte_ptr2->set_kd(kd);
	matte_ptr2->set_cd(BROWN);
	Sphere *sphere_ptr2 = new Sphere(Point3D(45, -7, -60), 20);
	sphere_ptr2->set_material(matte_ptr2);								// brown
	add_object(sphere_ptr2);


	Matte *matte_ptr3 = new Matte;
	matte_ptr3->set_ka(ka);
	matte_ptr3->set_kd(kd);
	matte_ptr3->set_cd(DARK_GREEN);
	Sphere *sphere_ptr3 = new Sphere(Point3D(40, 43, -100), 17);
	sphere_ptr3->set_material(matte_ptr3);								// dark green
	add_object(sphere_ptr3);

	Matte *matte_ptr4 = new Matte;
	matte_ptr4->set_ka(ka);
	matte_ptr4->set_kd(kd);
	matte_ptr4->set_cd(ORANGE);
	Sphere *sphere_ptr4 = new Sphere(Point3D(-20, 28, -15), 20);
	sphere_ptr4->set_material(matte_ptr4);								// orange
	add_object(sphere_ptr4);

	Matte *matte_ptr5 = new Matte;
	matte_ptr5->set_ka(ka);
	matte_ptr5->set_kd(kd);
	matte_ptr5->set_cd(GREEN);
	Sphere *sphere_ptr5 = new Sphere(Point3D(-25, -7, -35), 27);
	sphere_ptr5->set_material(matte_ptr5);								// green
	add_object(sphere_ptr5);

	Matte *matte_ptr6 = new Matte;
	matte_ptr6->set_ka(ka);
	matte_ptr6->set_kd(kd);
	matte_ptr6->set_cd(LIGHT_GREEN);
	Sphere *sphere_ptr6 = new Sphere(Point3D(20, -27, -35), 25);
	sphere_ptr6->set_material(matte_ptr6);								// light green
	add_object(sphere_ptr6);

	Matte *matte_ptr7 = new Matte;
	matte_ptr7->set_ka(ka);
	matte_ptr7->set_kd(kd);
	matte_ptr7->set_cd(GREEN);
	Sphere *sphere_ptr7 = new Sphere(Point3D(35, 18, -35), 22);
	sphere_ptr7->set_material(matte_ptr7);   							// green
	add_object(sphere_ptr7);

	Matte *matte_ptr8 = new Matte;
	matte_ptr8->set_ka(ka);
	matte_ptr8->set_kd(kd);
	matte_ptr8->set_cd(BROWN);
	Sphere *sphere_ptr8 = new Sphere(Point3D(-57, -17, -50), 15);
	sphere_ptr8->set_material(matte_ptr8);								// brown
	add_object(sphere_ptr8);

	Matte *matte_ptr9 = new Matte;
	matte_ptr9->set_ka(ka);
	matte_ptr9->set_kd(kd);
	matte_ptr9->set_cd(LIGHT_GREEN);
	Sphere *sphere_ptr9 = new Sphere(Point3D(-47, 16, -80), 23);
	sphere_ptr9->set_material(matte_ptr9);								// light green
	add_object(sphere_ptr9);

	Matte *matte_ptr10 = new Matte;
	matte_ptr10->set_ka(ka);
	matte_ptr10->set_kd(kd);
	matte_ptr10->set_cd(DARK_GREEN);
	Sphere *sphere_ptr10 = new Sphere(Point3D(-15, -32, -60), 22);
	sphere_ptr10->set_material(matte_ptr10);     						// dark green
	add_object(sphere_ptr10);

	Matte *matte_ptr11 = new Matte;
	matte_ptr11->set_ka(ka);
	matte_ptr11->set_kd(kd);
	matte_ptr11->set_cd(DARK_YELLOW);
	Sphere *sphere_ptr11 = new Sphere(Point3D(-35, -37, -80), 22);
	sphere_ptr11->set_material(matte_ptr11);							// dark yellow
	add_object(sphere_ptr11);

	Matte *matte_ptr12 = new Matte;
	matte_ptr12->set_ka(ka);
	matte_ptr12->set_kd(kd);
	matte_ptr12->set_cd(DARK_YELLOW);
	Sphere *sphere_ptr12 = new Sphere(Point3D(10, 43, -80), 22);
	sphere_ptr12->set_material(matte_ptr12);							// dark yellow
	add_object(sphere_ptr12);

	Matte *matte_ptr13 = new Matte;
	matte_ptr13->set_ka(ka);
	matte_ptr13->set_kd(kd);
	matte_ptr13->set_cd(DARK_YELLOW);
	Sphere *sphere_ptr13 = new Sphere(Point3D(30, -7, -80), 10);
	sphere_ptr13->set_material(matte_ptr13);
	add_object(sphere_ptr13);											// dark yellow (hidden)

	Matte *matte_ptr14 = new Matte;
	matte_ptr14->set_ka(ka);
	matte_ptr14->set_kd(kd);
	matte_ptr14->set_cd(DARK_GREEN);
	Sphere *sphere_ptr14 = new Sphere(Point3D(-40, 48, -110), 18);
	sphere_ptr14->set_material(matte_ptr14); 							// dark green
	add_object(sphere_ptr14);

	Matte *matte_ptr15 = new Matte;
	matte_ptr15->set_ka(ka);
	matte_ptr15->set_kd(kd);
	matte_ptr15->set_cd(BROWN);
	Sphere *sphere_ptr15 = new Sphere(Point3D(-10, 53, -120), 18);
	sphere_ptr15->set_material(matte_ptr15); 							// brown
	add_object(sphere_ptr15);

	Matte *matte_ptr16 = new Matte;
	matte_ptr16->set_ka(ka);
	matte_ptr16->set_kd(kd);
	matte_ptr16->set_cd(LIGHT_PURPLE);
	Sphere *sphere_ptr16 = new Sphere(Point3D(-55, -52, -100), 10);
	sphere_ptr16->set_material(matte_ptr16);							// light purple
	add_object(sphere_ptr16);

	Matte *matte_ptr17 = new Matte;
	matte_ptr17->set_ka(ka);
	matte_ptr17->set_kd(kd);
	matte_ptr17->set_cd(BROWN);
	Sphere *sphere_ptr17 = new Sphere(Point3D(5, -52, -100), 15);
	sphere_ptr17->set_material(matte_ptr17);							// browm
	add_object(sphere_ptr17);

	Matte *matte_ptr18 = new Matte;
	matte_ptr18->set_ka(ka);
	matte_ptr18->set_kd(kd);
	matte_ptr18->set_cd(DARK_PURPLE);
	Sphere *sphere_ptr18 = new Sphere(Point3D(-20, -57, -120), 15);
	sphere_ptr18->set_material(matte_ptr18);							// dark purple
	add_object(sphere_ptr18);

	Matte *matte_ptr19 = new Matte;
	matte_ptr19->set_ka(ka);
	matte_ptr19->set_kd(kd);
	matte_ptr19->set_cd(DARK_GREEN);
	Sphere *sphere_ptr19 = new Sphere(Point3D(55, -27, -100), 17);
	sphere_ptr19->set_material(matte_ptr19);							// dark green
	add_object(sphere_ptr19);

	Matte *matte_ptr20 = new Matte;
	matte_ptr20->set_ka(ka);
	matte_ptr20->set_kd(kd);
	matte_ptr20->set_cd(BROWN);
	Sphere *sphere_ptr20 = new Sphere(Point3D(50, -47, -120), 15);
	sphere_ptr20->set_material(matte_ptr20);							// browm
	add_object(sphere_ptr20);

	Matte *matte_ptr21 = new Matte;
	matte_ptr21->set_ka(ka);
	matte_ptr21->set_kd(kd);
	matte_ptr21->set_cd(LIGHT_PURPLE);
	Sphere *sphere_ptr21 = new Sphere(Point3D(70, -42, -150), 10);
	sphere_ptr21->set_material(matte_ptr21);							// light purple
	add_object(sphere_ptr21);

	Matte *matte_ptr22 = new Matte;
	matte_ptr22->set_ka(ka);
	matte_ptr22->set_kd(kd);
	matte_ptr22->set_cd(LIGHT_PURPLE);
	Sphere *sphere_ptr22 = new Sphere(Point3D(5, 73, -130), 12);
	sphere_ptr22->set_material(matte_ptr22);							// light purple
	add_object(sphere_ptr22);

	Matte *matte_ptr23 = new Matte;
	matte_ptr23->set_ka(ka);
	matte_ptr23->set_kd(kd);
	matte_ptr23->set_cd(DARK_PURPLE);
	Sphere *sphere_ptr23 = new Sphere(Point3D(66, 21, -130), 13);
	sphere_ptr23->set_material(matte_ptr23);							// dark purple
	add_object(sphere_ptr23);

	Matte *matte_ptr24 = new Matte;
	matte_ptr24->set_ka(ka);
	matte_ptr24->set_kd(kd);
	matte_ptr24->set_cd(LIGHT_PURPLE);
	Sphere *sphere_ptr24 = new Sphere(Point3D(72, -12, -140), 12);
	sphere_ptr24->set_material(matte_ptr24);							// light purple
	add_object(sphere_ptr24);

	Matte *matte_ptr25 = new Matte;
	matte_ptr25->set_ka(ka);
	matte_ptr25->set_kd(kd);
	matte_ptr25->set_cd(GREEN);
	Sphere *sphere_ptr25 = new Sphere(Point3D(64, 5, -160), 11);
	sphere_ptr25->set_material(matte_ptr25);					 		// green
	add_object(sphere_ptr25);

	Matte *matte_ptr26 = new Matte;
	matte_ptr26->set_ka(ka);
	matte_ptr26->set_kd(kd);
	matte_ptr26->set_cd(LIGHT_PURPLE);
	Sphere *sphere_ptr26 = new Sphere(Point3D(55, 38, -160), 12);
	sphere_ptr26->set_material(matte_ptr26);							// light purple
	add_object(sphere_ptr26);

	Matte *matte_ptr27 = new Matte;
	matte_ptr27->set_ka(ka);
	matte_ptr27->set_kd(kd);
	matte_ptr27->set_cd(LIGHT_PURPLE);
	Sphere *sphere_ptr27 = new Sphere(Point3D(-73, -2, -160), 12);
	sphere_ptr27->set_material(matte_ptr27);							// light purple
	add_object(sphere_ptr27);

	Matte *matte_ptr28 = new Matte;
	matte_ptr28->set_ka(ka);
	matte_ptr28->set_kd(kd);
	matte_ptr28->set_cd(DARK_PURPLE);
	Sphere *sphere_ptr28 = new Sphere(Point3D(30, -62, -140), 15);
	sphere_ptr28->set_material(matte_ptr28); 							// dark purple
	add_object(sphere_ptr28);

	Matte *matte_ptr29 = new Matte;
	matte_ptr29->set_ka(ka);
	matte_ptr29->set_kd(kd);
	matte_ptr29->set_cd(DARK_PURPLE);
	Sphere *sphere_ptr29 = new Sphere(Point3D(25, 63, -140), 15);
	sphere_ptr29->set_material(matte_ptr29);							// dark purple
	add_object(sphere_ptr29);

	Matte *matte_ptr30 = new Matte;
	matte_ptr30->set_ka(ka);
	matte_ptr30->set_kd(kd);
	matte_ptr30->set_cd(DARK_PURPLE);
	Sphere *sphere_ptr30 = new Sphere(Point3D(-60, 46, -140), 15);
	sphere_ptr30->set_material(matte_ptr30); 							// dark purple
	add_object(sphere_ptr30);

	Matte *matte_ptr31 = new Matte;
	matte_ptr31->set_ka(ka);
	matte_ptr31->set_kd(kd);
	matte_ptr31->set_cd(LIGHT_PURPLE);
	Sphere *sphere_ptr31 = new Sphere(Point3D(-30, 68, -130), 12);
	sphere_ptr31->set_material(matte_ptr31); 							// light purple
	add_object(sphere_ptr31);

	Matte *matte_ptr32 = new Matte;
	matte_ptr32->set_ka(ka);
	matte_ptr32->set_kd(kd);
	matte_ptr32->set_cd(GREEN);
	Sphere *sphere_ptr32 = new Sphere(Point3D(58, 56, -180), 11);
	sphere_ptr32->set_material(matte_ptr32);							//  green
	add_object(sphere_ptr32);

	Matte *matte_ptr33 = new Matte;
	matte_ptr33->set_ka(ka);
	matte_ptr33->set_kd(kd);
	matte_ptr33->set_cd(GREEN);
	Sphere *sphere_ptr33 = new Sphere(Point3D(-63, -39, -180), 11);
	sphere_ptr33->set_material(matte_ptr33);							// green
	add_object(sphere_ptr33);

	Matte *matte_ptr34 = new Matte;
	matte_ptr34->set_ka(ka);
	matte_ptr34->set_kd(kd);
	matte_ptr34->set_cd(LIGHT_PURPLE);
	Sphere *sphere_ptr34 = new Sphere(Point3D(46, 68, -200), 10);
	sphere_ptr34->set_material(matte_ptr34);							// light purple
	add_object(sphere_ptr34);

	Matte *matte_ptr35 = new Matte;
	matte_ptr35->set_ka(ka);
	matte_ptr35->set_kd(kd);
	matte_ptr35->set_cd(LIGHT_PURPLE);
	Sphere *sphere_ptr35 = new Sphere(Point3D(-3, -72, -130), 12);
	sphere_ptr35->set_material(matte_ptr35);							// light purple
	add_object(sphere_ptr35);


	// vertical plane

	Matte *matte_ptr36 = new Matte;
	matte_ptr36->set_ka(ka);
	matte_ptr36->set_kd(kd);
	matte_ptr36->set_cd(GREY);
	Plane *plane_ptr = new Plane(Point3D(0, 0, -150), Normal(0, 0, 1));
	plane_ptr->set_material(matte_ptr36);
	add_object(plane_ptr);
	*/


	/*
	int numSamples = 16;

	m_vp.SetHres(400);
	m_vp.SetVres(400);
	m_vp.SetupSampler(numSamples);

	SetTracer(new RayCast(this));
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());

	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(11, 5, 9);
	pinhole_ptr->SetViewDistance(1600.0);
	pinhole_ptr->SetLookat(0, -0.5, 0);
	pinhole_ptr->ComputeONB();
	SetCamera(pinhole_ptr);


	Directional* directional_ptr = new Directional;
	directional_ptr->SetDirection(0.75, 1, -0.15);
	directional_ptr->SetRadianceScaler(4.5);
	directional_ptr->SetShadows(true);
	AddLight(directional_ptr);

	Image* image_ptr = new Image;
	image_ptr->ReadFilePPM("./resources/BlueGlass.ppm");

	ImageTexture* texture_ptr = new ImageTexture;
	texture_ptr->SetImage(image_ptr);

	Matte* tex_matte_ptr = new Matte;
	tex_matte_ptr->SetKa(0.1);
	tex_matte_ptr->SetKd(0.75);
	tex_matte_ptr->SetDiffuseTexture(texture_ptr);

	const char* file_name = "./resources/TwoUVTriangles.ply";
	MeshGrid* grid_ptr = new MeshGrid(tex_matte_ptr);
	grid_ptr->ReadFlatTexTriangles(file_name);				// for Figure 29.22(a)
	grid_ptr->ReadSmoothTexTriangles(file_name);			// for Figure 29.22(b)
	grid_ptr->MakeCells();
	AddObject(grid_ptr);

	Matte* matte_ptr = new Matte;
	matte_ptr->SetCd(1, 0.9, 0.6);
	matte_ptr->SetKa(0.25);
	matte_ptr->SetKd(0.4);

	Plane* plane_ptr1 = new Plane(Point3D(0, -2.0, 0), Normal(0, 1, 0));
	plane_ptr1->SetMaterial(matte_ptr);
	AddObject(plane_ptr1);
	*/


	/*
	int numSamples = 16;
	
	m_vp.SetHres(900);			
	m_vp.SetVres(900); 
	m_vp.SetupSampler(numSamples);
	m_vp.SetPixelSize(1.0);
	
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());
	SetTracer(new RayCast(this));	
	
	FishEye* fisheye_ptr = new FishEye;
	fisheye_ptr->SetEye(0.0); 
	fisheye_ptr->SetLookat(0, 0, -100);
	fisheye_ptr->SetFov(360);
	fisheye_ptr->ComputeONB(); 
	SetCamera(fisheye_ptr);
	
	Image* image_ptr = new Image;
	image_ptr->ReadFilePPM("./Resources/uffizi_probe_small.ppm");   // development
//	image_ptr->ReadFilePPM("./Resources/uffizi_probe_large.ppm");   // production

	LightProbe* light_probe_ptr = new LightProbe;     	
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->SetMapping(light_probe_ptr);
	
	Matte* sv_matte_ptr = new Matte;	// ka + kd > 1
	sv_matte_ptr->SetKa(1.0);
	sv_matte_ptr->SetKd(0.85); 	
	sv_matte_ptr->SetDiffuseTexture(image_texture_ptr);
	
	Sphere* unit_sphere_ptr = new Sphere;
	unit_sphere_ptr->SetShadows(false);	
	
	Instance* sphere_ptr = new Instance(unit_sphere_ptr); 
	sphere_ptr->Scale(1000000.0);
	sphere_ptr->SetMaterial(sv_matte_ptr);
	AddObject(sphere_ptr);
	*/


	/*
	int numSamples = 32;
	
	m_vp.SetHres(600); 
	m_vp.SetVres(400);
	m_vp.SetupSampler(numSamples);
//	m_vp.SetMaxDepth(0);			// for Figure 24.6(a)
	m_vp.SetMaxDepth(3);			// for Figure 24.6(b)
	
	SetTracer(new RayCast(this));	
	SetBackgroundColor(RGBColor(0.15)); 
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());

	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->SetRadianceScaler(0.5);
	SetAmbientLight(ambient_ptr);
	
			
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(75, 40, 100); 
	pinhole_ptr->SetLookat(-10, 39, 0);  
	pinhole_ptr->SetViewDistance(360);
	pinhole_ptr->ComputeONB(); 
	SetCamera(pinhole_ptr);
	
		
	PointLight* light_ptr = new PointLight;
	light_ptr->SetLocation(150, 150, 0);  
	light_ptr->SetRadianceScaler(3.0);
	light_ptr->SetShadows(true);
	AddLight(light_ptr);
	
	// yellow-green reflective sphere
	
	PerfectReflector* reflective_ptr1 = new PerfectReflector;			
	reflective_ptr1->SetKa(0.25); 
	reflective_ptr1->SetKd(0.5);
	reflective_ptr1->SetCd(0.75, 0.75, 0);		// yellow
	reflective_ptr1->SetKs(0.15);
	reflective_ptr1->SetExponent(100.0);
	reflective_ptr1->SetKr(0.75);
	reflective_ptr1->SetCr(WHITE); 				// default color
	
	float radius = 23.0;
	Sphere* sphere_ptr1 = new Sphere(Point3D(38, radius, -25), radius); 
	sphere_ptr1->SetMaterial(reflective_ptr1);
	AddObject(sphere_ptr1);
	
	
	// orange non-reflective sphere
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->SetKa(0.45); 
	matte_ptr1->SetKd(0.75);
	matte_ptr1->SetCd(0.75, 0.25, 0);			// orange
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(-7, 10, 42), 20);
	sphere_ptr2->SetMaterial(matte_ptr1);      
	AddObject(sphere_ptr2);
	
	
	// sphere on top of box

	PerfectReflector* reflective_ptr2 = new PerfectReflector;			
	reflective_ptr2->SetKa(0.35); 
	reflective_ptr2->SetKd(0.75);
	reflective_ptr2->SetCd(BLACK); 
	reflective_ptr2->SetKs(0.0);				// default value
	reflective_ptr2->SetExponent(1.0);			// default value, but irrelevant in this case
	reflective_ptr2->SetKr(0.75);
	reflective_ptr2->SetCr(WHITE); 

	Sphere* sphere_ptr3 = new Sphere(Point3D(-30, 59, 35), 20);
	sphere_ptr3->SetMaterial(reflective_ptr2);     
	AddObject(sphere_ptr3);

	
	// cylinder
	
	PerfectReflector* reflective_ptr3 = new PerfectReflector;			
	reflective_ptr3->SetKa(0.35); 
	reflective_ptr3->SetKd(0.5);
	reflective_ptr3->SetCd(0, 0.5, 0.75);		// cyan
	reflective_ptr3->SetKs(0.2);
	reflective_ptr3->SetExponent(100.0);
	reflective_ptr3->SetKr(0.75);
	reflective_ptr3->SetCr(WHITE);
	
	double bottom 			= 0.0;
	double top 				= 85;   
	double cylinder_radius	= 22;
	Cylinder* cylinder_ptr = new Cylinder(bottom, top, cylinder_radius);
	cylinder_ptr->SetMaterial(reflective_ptr3);
	AddObject(cylinder_ptr);
	
	
	// box
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->SetKa(0.15); 
	matte_ptr2->SetKd(0.5);
	matte_ptr2->SetCd(0.75, 1.0, 0.75);			// light green
	
	Box* box_ptr = new Box(Point3D(-35, 0, -110), Point3D(-25, 60, 65));
	box_ptr->SetMaterial(matte_ptr2);
	AddObject(box_ptr);

	
	// ground plane
	
	PlaneChecker* checker_ptr = new PlaneChecker;
	checker_ptr->SetSize(20.0);		
	checker_ptr->SetOutlineWidth(2.0);
	checker_ptr->SetColor1(WHITE);
	checker_ptr->SetColor2(WHITE);
	checker_ptr->SetOutlineColor(BLACK); 
	
	Matte* sv_matte_ptr = new Matte;		
	sv_matte_ptr->SetKa(0.30);
	sv_matte_ptr->SetKd(0.9);
	sv_matte_ptr->SetDiffuseTexture(checker_ptr); 
	
	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(sv_matte_ptr);
	AddObject(plane_ptr);
	*/

	
	/*
	int numSamples = 100;
	
	m_vp.SetHres(600);	  		
	m_vp.SetVres(600);        
	m_vp.SetupSampler(numSamples);
	m_vp.SetMaxDepth(19);	
	
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());
	SetTracer(new AreaLight(this));
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(7.5, 3, 9.5);
	pinhole_ptr->SetLookat(5, 2.5, 0);
	pinhole_ptr->SetViewDistance(800);
	pinhole_ptr->ComputeONB(); 
	SetCamera(pinhole_ptr);
				
	
	// four point lights near the ceiling
	// these don't use distance attenuation

	PointLight* light_ptr1 = new PointLight;
	light_ptr1->SetLocation(10, 10, 0); 
	light_ptr1->SetRadianceScaler(2.0); 
	light_ptr1->SetShadows(true); 
    AddLight(light_ptr1);
    
    PointLight* light_ptr2 = new PointLight;
	light_ptr2->SetLocation(0, 10, 10); 
	light_ptr2->SetRadianceScaler(2.0); 
	light_ptr2->SetShadows(true); 
    AddLight(light_ptr2);
    
    PointLight* light_ptr3 = new PointLight;
	light_ptr3->SetLocation(-10, 10, 0); 
	light_ptr3->SetRadianceScaler(2.0); 
	light_ptr3->SetShadows(true); 
    AddLight(light_ptr3);
    
    PointLight* light_ptr4 = new PointLight;
	light_ptr4->SetLocation(0, 10, -10); 
	light_ptr4->SetRadianceScaler(2.0); 
	light_ptr4->SetShadows(true); 
    AddLight(light_ptr4);

		
	// sphere
	// this is the only reflective object with a direct illumination shading component
	
	PerfectReflector* reflective_ptr1 = new PerfectReflector;			
	reflective_ptr1->SetKa(0.1); 
	reflective_ptr1->SetKd(0.4); 
	reflective_ptr1->SetCd(0, 0, 1);   		// blue
	reflective_ptr1->SetKs(0.25);
	reflective_ptr1->SetExponent(100.0);
	reflective_ptr1->SetKr(0.85); 
	reflective_ptr1->SetCr(0.75, 0.75, 1);  // blue 
	
	Sphere*	sphere_ptr1 = new Sphere(Point3D(0, 0.5, 0), 4); 
	sphere_ptr1->SetMaterial(reflective_ptr1);
	AddObject(sphere_ptr1);
		
	
	// the walls, the ceiling, and the floor of the room are defined as planes
	// the shape is a cube
	
	double roomSize = 11.0;
	
	// floor  (-ve yw)
	
	Matte* matte_ptr1 = new Matte;
	matte_ptr1->SetKa(0.1);   
	matte_ptr1->SetKd(0.50);
	matte_ptr1->SetCd(0.25);				// medium grey
	
	Plane* floor_ptr = new Plane(Point3D(0, -roomSize,  0), Normal(0, 1, 0));
	floor_ptr->SetMaterial(matte_ptr1);        
	AddObject(floor_ptr);
	
	
	// ceiling  (+ve yw)
	
	Matte* matte_ptr2 = new Matte;   
	matte_ptr2->SetKa(0.35);   
	matte_ptr2->SetKd(0.50);
	matte_ptr2->SetCd(WHITE);
	
	Plane* ceiling_ptr = new Plane(Point3D(0, roomSize,  0), Normal(0, -1, 0));
	ceiling_ptr->SetMaterial(matte_ptr2);        
	AddObject(ceiling_ptr);
	
	
	// back wall  (-ve zw)
	
	Matte* matte_ptr3 = new Matte;
	matte_ptr3->SetKa(0.15); 
	matte_ptr3->SetKd(0.60);
	matte_ptr3->SetCd(0.5, 0.75, 0.75);     // cyan
	
	Plane* backWall_ptr = new Plane(Point3D(0, 0,  -roomSize), Normal(0, 0, 1));
	backWall_ptr->SetMaterial(matte_ptr3);        
	AddObject(backWall_ptr);
	
	// front wall  (+ve zw)
	
	Plane* frontWall_ptr = new Plane(Point3D(0, 0,  roomSize), Normal(0, 0, -1));
	frontWall_ptr->SetMaterial(matte_ptr3->AddRef());        
	AddObject(frontWall_ptr);
	
	// left wall  (-ve xw)
	
	Matte* matte_ptr4 = new Matte;
	matte_ptr4->SetKa(0.15); 
	matte_ptr4->SetKd(0.60);
	matte_ptr4->SetCd(0.71, 0.40, 0.20);   // orange
	
	Plane* leftWall_ptr = new Plane(Point3D(-roomSize, 0, 0), Normal(1, 0, 0));
	leftWall_ptr->SetMaterial(matte_ptr4);        
	AddObject(leftWall_ptr);
	
	// right wall  (+ve xw)
	
	Plane* rightWall_ptr = new Plane(Point3D(roomSize, 0, 0), Normal(-1, 0, 0));
	rightWall_ptr->SetMaterial(matte_ptr4->AddRef());        
	AddObject(rightWall_ptr);
	
	
	// mirrors on the walls
	// the right wall has no mirror
	
	double mirrorSize 	= 8;  	// the mirror size
	double offset 		= 1.0;  // the mirror offset from the walls
	
	// mirror reflection material for the left wall mirror
	
	PerfectReflector* reflective_ptr2 = new PerfectReflector;			
	reflective_ptr2->SetKa(0); 
	reflective_ptr2->SetKd(0);
	reflective_ptr2->SetCd(BLACK); 
	reflective_ptr2->SetKs(0);
	reflective_ptr2->SetKr(0.9);
	reflective_ptr2->SetCr(0.9, 1.0, 0.9);  // light green
	
	// glossy reflector material for the back and front mirrors
	
	float exp = 25000.0;
	GlossyReflector* glossy_reflector_ptr = new GlossyReflector;
	glossy_reflector_ptr->SetupSampler(numSamples, exp);			
	glossy_reflector_ptr->SetKa(0.0); 
	glossy_reflector_ptr->SetKd(0.0);
	glossy_reflector_ptr->SetKs(0.0);
	glossy_reflector_ptr->SetExponent(exp);
	glossy_reflector_ptr->SetCd(BLACK);
	glossy_reflector_ptr->SetKr(0.9);
	glossy_reflector_ptr->SetExponent(exp);
	glossy_reflector_ptr->SetCr(0.9, 1.0, 0.9);  // light green
	
	
	// back wall mirror  (-ve zw)

	Point3D p0;
	Vector3D a, b;
	
	p0 = Point3D(-mirrorSize, -mirrorSize, -(roomSize - offset));
	a = Vector3D(2.0 * mirrorSize, 0, 0);
	b = Vector3D(0, 2.0 * mirrorSize, 0);
	Normal n(0, 0, 1);
	RectangleX* rectangle_ptr1 = new RectangleX(p0, a, b, n);
//	rectangle_ptr1->SetMaterial(reflective_ptr2);
	rectangle_ptr1->SetMaterial(glossy_reflector_ptr); 
	AddObject(rectangle_ptr1);
	
	
	// front wall mirror  (+ve zw)
	
	p0 = Point3D(-mirrorSize, -mirrorSize, +(roomSize - offset));
	n = Normal(0, 0, -1);
	RectangleX* rectangle_ptr2 = new RectangleX(p0, a, b, n);
//	rectangle_ptr2->SetMaterial(reflective_ptr2); 
	rectangle_ptr2->SetMaterial(glossy_reflector_ptr->AddRef()); 
	AddObject(rectangle_ptr2);
	
	
	// left wall mirror  (-ve xw)
	
	p0 = Point3D(-(roomSize - offset), -mirrorSize, +mirrorSize);
	a = Point3D(0, 0, -2.0 * mirrorSize);
	n = Normal(1, 0, 0);
	RectangleX* rectangle_ptr3 = new RectangleX(p0, a, b, n);
	rectangle_ptr3->SetMaterial(reflective_ptr2); 
	AddObject(rectangle_ptr3);


	// horizontal mirror underneath the sphere
	// this has no direct illumination and a lemon color
	
	PerfectReflector* reflective_ptr3 = new PerfectReflector;			
	reflective_ptr3->SetKa(0); 
	reflective_ptr3->SetKd(0);
	reflective_ptr3->SetCd(BLACK); 
	reflective_ptr3->SetKs(0);
	reflective_ptr3->SetKr(1);
	reflective_ptr3->SetCr(1, 1, 0.5);  // lemon
	
	double yw = -4.0;   // the yw location of the mirror
	
	p0 = Point3D(-mirrorSize, yw, -mirrorSize);
	a = Vector3D(0, 0, 2.0 * mirrorSize);
	b = Vector3D(2.0 * mirrorSize, 0, 0);
	n = Normal(0, 1, 0);
	RectangleX* rectangle_ptr4 = new RectangleX(p0, a, b, n);
	rectangle_ptr4->SetMaterial(reflective_ptr3); 
	AddObject(rectangle_ptr4);
	*/

	
	/*
	int numSamples = 25;
	
	m_vp.SetHres(600);			
	m_vp.SetVres(600); 
	m_vp.SetupSampler(numSamples);
	m_vp.SetMaxDepth(1);
		
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());
	SetTracer(new AreaLight(this));	
				
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(-150, 75, 500); 
	pinhole_ptr->SetLookat(-6, 50, 0);
	pinhole_ptr->SetViewDistance(3000);	
	pinhole_ptr->ComputeONB(); 
	SetCamera(pinhole_ptr);
	
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->SetLocation(250, 500, 250); 
	light_ptr1->SetRadianceScaler(2.0);   
	light_ptr1->SetShadows(true); 
    AddLight(light_ptr1);

//	float exp = 1.0;  		// for Figure 25.30(a)
//	float exp = 10.0;  		// for Figure 25.30(b)
//	float exp = 100.0;  	// for Figure 25.30(c)
//	float exp = 1000.0;  	// for Figure 25.30(d)
//	float exp = 10000.0;  	// for Figure 25.30(e)
	float exp = 100000.0;  	// for Figure 25.30(f)
	
	GlossyReflector* glossy_ptr = new GlossyReflector;
	glossy_ptr->SetupSampler(numSamples, exp);			
	glossy_ptr->SetKa(0.0); 
	glossy_ptr->SetKd(0.0);
	glossy_ptr->SetKs(0.0);
	glossy_ptr->SetExponent(exp);
	glossy_ptr->SetCd(1.0, 1.0, 0.3);
	glossy_ptr->SetKr(0.9);
	glossy_ptr->SetExponent(exp);
	glossy_ptr->SetCr(1.0, 1.0, 0.3);  // lemon
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(-6, 55, 0), 40);
	sphere_ptr1->SetMaterial(glossy_ptr);
	AddObject(sphere_ptr1);
		
	
	//cylinder
	
	Matte* matte_ptr = new Matte;		
	matte_ptr->SetKa(0.15);
	matte_ptr->SetKd(0.75);
	matte_ptr->SetCd(0.5, 1.0, 0.5);   // green

	double bottom = -100;
	double top = 15;       
	double radius = 30;
	Instance* cylinder_ptr = new Instance(new Cylinder(bottom, top, radius));
	cylinder_ptr->Translate(-6, 0, 0);
	cylinder_ptr->SetMaterial(matte_ptr);
	AddObject(cylinder_ptr);
	
	
	Image* image_ptr = new Image;
	image_ptr->ReadFilePPM("./resources/uffizi_probe_small.ppm");  // for testing 
//	image_ptr->ReadFilePPM("./resources/uffizi_probe_large.ppm");  // for production

	
	LightProbe* light_probe_ptr = new LightProbe; 
	light_probe_ptr->SetMapType(LP_Panoramic);   		
	
	ImageTexture* image_texture_ptr = new ImageTexture(image_ptr); 
	image_texture_ptr->SetMapping(light_probe_ptr);
	
	Matte* sv_matte_ptr = new Matte;		
	sv_matte_ptr->SetKa(1);
	sv_matte_ptr->SetKd(0.85);  
	sv_matte_ptr->SetDiffuseTexture(image_texture_ptr);
	
	Sphere* unit_sphere_ptr = new Sphere;
	unit_sphere_ptr->SetShadows(false);	
	
	Instance* sphere_ptr2 = new Instance(unit_sphere_ptr); 
	sphere_ptr2->Scale(1000000.0);
	sphere_ptr2->SetMaterial(sv_matte_ptr);
	AddObject(sphere_ptr2);
	*/


	/*
	int numSamples = 200;
		
	m_vp.SetHres(300);	  		
	m_vp.SetVres(300);
	m_vp.SetupSampler(numSamples); 
	m_vp.SetMaxDepth(5);
	
	SetBackgroundColor(BLACK);
	
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());
	SetTracer(new PathTrace(this));
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(27.6, 27.4, -80.0);
	pinhole_ptr->SetLookat(27.6, 27.4, 0.0);
	pinhole_ptr->SetViewDistance(400);      
	pinhole_ptr->ComputeONB();     
	SetCamera(pinhole_ptr);
	
	
	Point3D p0;
	Vector3D a, b;
	Normal normal;
	
	// box dimensions
	
	double width 	= 55.28;   	// x direction
	double height 	= 54.88;  	// y direction
	double depth 	= 55.92;	// z direction
	
	
	// the ceiling light - doesn't need samples
	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->SetCe(1.0, 0.73, 0.4);   
	emissive_ptr->SetRadianceScaler(100);
	
	p0 = Point3D(21.3, height - 0.001, 22.7);
	a = Vector3D(0.0, 0.0, 10.5);
	b = Vector3D(13.0, 0.0, 0.0);
	normal = Normal(0.0, -1.0, 0.0);
	RectangleX* emitter = new RectangleX(p0, a, b, normal);
	emitter->SetMaterial(emissive_ptr);
	emitter->SetSampler(new MultiJittered(100));
	AreaLightAdapter* light_ptr = new AreaLightAdapter();
	light_ptr->SetEmitter(emitter);
	light_ptr->SetShadows(true);
	AddLight(light_ptr);
	AddObject(emitter->AddRef());
	
		
	// left wall
	
	Matte* matte_ptr1 = new Matte;
	matte_ptr1->SetKa(0.0);
	matte_ptr1->SetKd(0.6); 
	matte_ptr1->SetCd(0.57, 0.025, 0.025);	 // red
	matte_ptr1->SetSampler(new MultiJittered(numSamples));
	
	p0 = Point3D(width, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(-1.0, 0.0, 0.0);
	RectangleX* left_wall_ptr = new RectangleX(p0, a, b, normal);
	left_wall_ptr->SetMaterial(matte_ptr1);
	AddObject(left_wall_ptr);
	
	
	// right wall
	
	Matte* matte_ptr2 = new Matte;
	matte_ptr2->SetKa(0.0);
	matte_ptr2->SetKd(0.6); 
	matte_ptr2->SetCd(0.37, 0.59, 0.2);		// green   from Photoshop
	matte_ptr2->SetSampler(new MultiJittered(numSamples));
	
	p0 = Point3D(0.0, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(1.0, 0.0, 0.0);
	RectangleX* right_wall_ptr = new RectangleX(p0, a, b, normal);
	right_wall_ptr->SetMaterial(matte_ptr2);
	AddObject(right_wall_ptr);
	
	
	// back wall
	
	Matte* matte_ptr3 = new Matte;
	matte_ptr3->SetKa(0.0);
	matte_ptr3->SetKd(0.6); 
	matte_ptr3->SetCd(WHITE);	
	matte_ptr3->SetSampler(new MultiJittered(numSamples));
	
	p0 = Point3D(0.0, 0.0, depth);
	a = Vector3D(width, 0.0, 0.0);
	b = Vector3D(0.0, height, 0.0);
	normal = Normal(0.0, 0.0, -1.0);
	RectangleX* back_wall_ptr = new RectangleX(p0, a, b, normal);
	back_wall_ptr->SetMaterial(matte_ptr3);
	AddObject(back_wall_ptr);
	
	
	// floor
	
	p0 = Point3D(0.0, 0.0, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(width, 0.0, 0.0);
	normal = Normal(0.0, 1.0, 0.0);
	RectangleX* floor_ptr = new RectangleX(p0, a, b, normal);
	floor_ptr->SetMaterial(matte_ptr3->Clone());
	AddObject(floor_ptr);
	
	
	// ceiling
	
	p0 = Point3D(0.0, height, 0.0);
	a = Vector3D(0.0, 0.0, depth);
	b = Vector3D(width, 0.0, 0.0);
	normal = Normal(0.0, -1.0, 0.0);
	RectangleX* ceiling_ptr = new RectangleX(p0, a, b, normal);
	ceiling_ptr->SetMaterial(matte_ptr3->Clone());
	AddObject(ceiling_ptr);

	
	// the two boxes defined as 5 rectangles each
	
	// short box
	
	// top
	
	p0 = Point3D(13.0, 16.5, 6.5);
	a = Vector3D(-4.8, 0.0, 16.0);
	b = Vector3D(16.0, 0.0, 4.9);
	normal = Normal(0.0, 1.0, 0.0);
	RectangleX* short_top_ptr = new RectangleX(p0, a, b, normal);
	short_top_ptr->SetMaterial(matte_ptr3->Clone());
	AddObject(short_top_ptr);
	
	
	// side 1
	
	p0 = Point3D(13.0, 0.0, 6.5);
	a = Vector3D(-4.8, 0.0, 16.0);
	b = Vector3D(0.0, 16.5, 0.0);
	RectangleX* short_side_ptr1 = new RectangleX(p0, a, b);
	short_side_ptr1->SetMaterial(matte_ptr3->Clone());
	AddObject(short_side_ptr1);
	
	
	// side 2
	
	p0 = Point3D(8.2, 0.0, 22.5);
	a = Vector3D(15.8, 0.0, 4.7);
	RectangleX* short_side_ptr2 = new RectangleX(p0, a, b);
	short_side_ptr2->SetMaterial(matte_ptr3->Clone());
	AddObject(short_side_ptr2);
	
	
	// side 3
	
	p0 = Point3D(24.2, 0.0, 27.4);
	a = Vector3D(4.8, 0.0, -16.0);
	RectangleX* short_side_ptr3 = new RectangleX(p0, a, b);
	short_side_ptr3->SetMaterial(matte_ptr3->Clone());
	AddObject(short_side_ptr3);
	
	
	// side 4
	
	p0 = Point3D(29.0, 0.0, 11.4);
	a = Vector3D(-16.0, 0.0, -4.9);
	RectangleX* short_side_ptr4 = new RectangleX(p0, a, b);
	short_side_ptr4->SetMaterial(matte_ptr3->Clone());
	AddObject(short_side_ptr4);
	
	
	
	// tall box
	
	// top
	
	p0 = Point3D(42.3, 33.0, 24.7);
	a = Vector3D(-15.8, 0.0, 4.9);
	b = Vector3D(4.9, 0.0, 15.9);
	normal = Normal(0.0, 1.0, 0.0);
	RectangleX* tall_top_ptr = new RectangleX(p0, a, b, normal);
	tall_top_ptr->SetMaterial(matte_ptr3->Clone());
	AddObject(tall_top_ptr);
	
	
	// side 1
	
	p0 = Point3D(42.3, 0.0, 24.7);
	a = Vector3D(-15.8, 0.0, 4.9);
	b = Vector3D(0.0, 33.0, 0.0);
	RectangleX* tall_side_ptr1 = new RectangleX(p0, a, b);
	tall_side_ptr1->SetMaterial(matte_ptr3->Clone());
	AddObject(tall_side_ptr1);
	
	
	// side 2
	
	p0 = Point3D(26.5, 0.0, 29.6);
	a = Vector3D(4.9, 0.0, 15.9);
	RectangleX* tall_side_ptr2 = new RectangleX(p0, a, b);
	tall_side_ptr2->SetMaterial(matte_ptr3->Clone());
	AddObject(tall_side_ptr2);
	
	
	// side 3
	
	p0 = Point3D(31.4, 0.0, 45.5);
	a = Vector3D(15.8, 0.0, -4.9);
	RectangleX* tall_side_ptr3 = new RectangleX(p0, a, b);
	tall_side_ptr3->SetMaterial(matte_ptr3->Clone());
	AddObject(tall_side_ptr3);
	
	
	// side 4
	
	p0 = Point3D(47.2, 0.0, 40.6);
	a = Vector3D(-4.9, 0.0, -15.9);
	RectangleX* tall_side_ptr4 = new RectangleX(p0, a, b);
	tall_side_ptr4->SetMaterial(matte_ptr3->Clone());
	AddObject(tall_side_ptr4);
	*/


	int numSamples = 200;

	m_vp.SetHres(800);
	m_vp.SetVres(600);
	m_vp.SetupSampler(numSamples);

	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());
	SetTracer(new AreaLight(this));
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->SetRadianceScaler(0.0);
	SetAmbientLight(ambient_ptr);	

			
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(100, 45, 100);  
	pinhole_ptr->SetLookat(-10, 40, 0);  
	pinhole_ptr->SetViewDistance(400); 
	pinhole_ptr->SetNumWorkerThreads(30);
	pinhole_ptr->ComputeONB(); 
	SetCamera(pinhole_ptr);
	
	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->SetCe(WHITE);  
	emissive_ptr->SetRadianceScaler(1.5);   
							
	EnvironmentLight* environmentLight_ptr = new EnvironmentLight;
	environmentLight_ptr->SetMaterial(emissive_ptr);
	environmentLight_ptr->SetSampler(new MultiJittered(numSamples));
	environmentLight_ptr->SetShadows(true);
	AddLight(environmentLight_ptr);
	
	Sphere* sphere_ptr = new Sphere;		// centered on the origin
	sphere_ptr->SetRadius(1000000.0);
	sphere_ptr->SetShadows(false);
	sphere_ptr->SetMaterial(emissive_ptr->AddRef());
	sphere_ptr->ReverseNormal(true);
	AddObject(sphere_ptr);	
	
		
	float ka = 0.2;  // common ambient reflection coefficient	

		
	// large sphere

	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->SetKa(ka); 
	matte_ptr1->SetKd(0.6);
	matte_ptr1->SetCd(WHITE);
	
	Sphere* sphere_ptr1 = new Sphere(Point3D(38, 20, -24), 20); 
	sphere_ptr1->SetMaterial(matte_ptr1);
	AddObject(sphere_ptr1);
	
	
	// small sphere
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->SetKa(ka); 
	matte_ptr2->SetKd(0.5);
	matte_ptr2->SetCd(0.85);				// gray
	
	Sphere* sphere_ptr2 = new Sphere(Point3D(34, 12, 13), 12);
	sphere_ptr2->SetMaterial(matte_ptr2);
	AddObject(sphere_ptr2);
	
	
	// medium sphere
		
	Matte* matte_ptr3 = new Matte;			
	matte_ptr3->SetKa(ka); 
	matte_ptr3->SetKd(0.75);
	matte_ptr3->SetCd(0.73, 0.22, 0.0);    // orange
	
	Sphere* sphere_ptr3 = new Sphere(Point3D(-7, 15, 42), 16);
	sphere_ptr3->SetMaterial(matte_ptr3);
	AddObject(sphere_ptr3);
	
	
	// cone
	
	Matte* matte_ptr4 = new Matte;			
	matte_ptr4->SetKa(ka); 
	matte_ptr4->SetKd(0.75);
	matte_ptr4->SetCd(0.60);				// gray
			
	double bottom 	= 0.0;
	double top 		= 85.0;
	double radius	= 30.0;
	PartialCone* cone_ptr = new PartialCone(bottom, top, radius, 90, 360);
	cone_ptr->SetMaterial(matte_ptr4);
	AddObject(cone_ptr);

	
	// box
	
	Matte* matte_ptr5 = new Matte;			
	matte_ptr5->SetKa(ka); 
	matte_ptr5->SetKd(0.75);
	matte_ptr5->SetCd(0.95);				// gray
	
	Box* box_ptr = new Box(Point3D(-55, 0, -110), Point3D(-25, 60, 65));  // thicker
	box_ptr->SetMaterial(matte_ptr5);
	AddObject(box_ptr);
	
	
	// ground plane
			
	Matte* matte_ptr6 = new Matte;			
	matte_ptr6->SetKa(0.15); 
	matte_ptr6->SetKd(0.95);	
	matte_ptr6->SetCd(0.37, 0.43, 0.08);     // olive green
	
	Plane* plane_ptr = new Plane(Point3D(0, 0.01, 0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr6);
	AddObject(plane_ptr);

	
	/*
//	int numSamples = 1;   	// for Figure 17.7(a)
//	int numSamples = 16;  	// for Figure 17.7(b)
//	int numSamples = 64;  	// for Figure 17.7(c)
	int numSamples = 256;	// for Figure 17.7(d)
	
	m_vp.SetHres(400);	  		
	m_vp.SetVres(400);
	m_vp.SetupSampler(numSamples);  
	
	SetTracer(new RayCast(this));
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());

	MultiJittered* sampler_ptr = new MultiJittered(numSamples); 
	
	AmbientOccluder* occluder_ptr = new AmbientOccluder;
	occluder_ptr->SetRadianceScaler(1.0);
	occluder_ptr->SetMinAmount(0.0);
	occluder_ptr->SetSampler(sampler_ptr);
	SetAmbientLight(occluder_ptr);		
		
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(25, 20, 45);
	pinhole_ptr->SetLookat(0, 1, 0); 
	pinhole_ptr->SetViewDistance(5000);	
	pinhole_ptr->ComputeONB();     
	SetCamera(pinhole_ptr);
	
	// sphere
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->SetKa(0.75);		
	matte_ptr1->SetKd(0);
	matte_ptr1->SetCd(1, 1, 0);   // yellow
		
	Sphere* sphere_ptr = new Sphere (Point3D(0, 1, 0), 1);  
	sphere_ptr->SetMaterial(matte_ptr1);
	AddObject(sphere_ptr);	
	
	// ground plane
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->SetKa(0.75);		
	matte_ptr2->SetKd(0);
	matte_ptr2->SetCd(1);        // white
	
	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr2);
	AddObject(plane_ptr);	
	*/


	/*
	int numSamples = 256;
	
	m_vp.SetHres(400);	  		
	m_vp.SetVres(400);
	m_vp.SetupSampler(numSamples);  
	
	SetTracer(new RayCast(this));
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());
		
	MultiJittered* sampler_ptr = new MultiJittered(numSamples); 

	
	AmbientOccluder* occluder_ptr = new AmbientOccluder;
	occluder_ptr->SetRadianceScaler(1.0);
	occluder_ptr->SetMinAmount(0.0);
	occluder_ptr->SetSampler(sampler_ptr);
	SetAmbientLight(occluder_ptr);			
	
		
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(-5, 2, 10);
	pinhole_ptr->SetLookat(0.35, 0.45, 0); 
	pinhole_ptr->SetViewDistance(2000);	
	pinhole_ptr->ComputeONB();     
	SetCamera(pinhole_ptr);
	
	Directional* light_ptr = new Directional;
	light_ptr->SetDirection(0, 150, 200);
	light_ptr->SetRadianceScaler(1.5);  
	light_ptr->SetShadows(true);
	AddLight(light_ptr);						// for Figure 17.11(b)
	
	
	// cylinder
	
	Matte* matte_ptr1 = new Matte;			
	matte_ptr1->SetKa(0.85);		
	matte_ptr1->SetKd(0.6);
	matte_ptr1->SetCd(1, 0.5, 0); 
	
	
	float bottom	= 0;
	float top 		= 1;
	float radius 	= 1;
	float phi_min 	= 0;
	float phi_max 	= 180;
	
	PartialCylinder* cylinder_ptr = new PartialCylinder(	bottom, 
															top, 
															radius, 
															phi_min, 
															phi_max);
	cylinder_ptr->SetMaterial(matte_ptr1);
	AddObject(cylinder_ptr);	
	
	
	// ground plane
	
	Matte* matte_ptr2 = new Matte;			
	matte_ptr2->SetKa(0.5);		
	matte_ptr2->SetKd(0.75);
	matte_ptr2->SetCd(WHITE);   
	
	Plane* plane_ptr = new Plane(Point3D(0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr2);
	AddObject(plane_ptr);	
	*/


	/*
	int numSamples = 32;
	
	m_vp.SetHres(600);	  		
	m_vp.SetVres(600);
	m_vp.SetupSampler(numSamples);	
	m_vp.SetMaxDepth(5);			
	
	SetBackgroundColor(WHITE);
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());
	SetTracer(new RayCast(this));
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->SetRadianceScaler(0.25);
	SetAmbientLight(ambient_ptr);
	
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(0, 0, 100);  
	pinhole_ptr->SetLookat(-0.4, 0.6, 0);    
	pinhole_ptr->SetViewDistance(15000.0);
	pinhole_ptr->SetNumWorkerThreads(20);
	pinhole_ptr->ComputeONB();     
	SetCamera(pinhole_ptr);
	
	
	// transparent bunny
	
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->SetKa(0.0);
	dielectric_ptr->SetKd(0.0); 
	dielectric_ptr->SetKs(0.2);     
	dielectric_ptr->SetExponent(2000.0);
	dielectric_ptr->SetRefractionIndices(1.5, 1.0);
	dielectric_ptr->SetFilteringColors(RGBColor(0.65, 0.45, 0), WHITE);
		
	const char* file_name = "./Resources/Bunny4K.ply"; 		// 4000 triangles
//	const char* file_name = "./Resources/Bunny10K.ply"; 	// 10000 triangles
//	const char* file_name = "./Resources/Bunny16K.ply"; 	// 16000 triangles
//	const char* file_name = "./Resources/Bunny69K.ply"; 	// 69000 triangles


	MeshGrid* bunny_ptr = new MeshGrid();
//	bunny_ptr->ReverseMeshNormals();						// you must use this for the 10K model
//	bunny_ptr->ReadFlatTriangles(file_name);		
	bunny_ptr->ReadSmoothTriangles(file_name);
	bunny_ptr->SetMaterial(dielectric_ptr); 	
	bunny_ptr->MakeCells();

	Instance* big_bunny_ptr = new Instance(bunny_ptr);
	big_bunny_ptr->Scale(20.0);
	big_bunny_ptr->Translate(0, -1.5, 0.0);
	AddObject(big_bunny_ptr);
	*/

	/*
	int numSamples = 25;
	
	m_vp.SetHres(600);	  		
	m_vp.SetVres(600);
	m_vp.SetupSampler(numSamples);
	m_vp.SetMaxDepth(6);

	SetBackgroundColor(RGBColor(0.0, 0.13, 0.1));
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());
	SetTracer(new RayCast(this));
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->SetColor(0.45, 0.5, 0.45);
	ambient_ptr->SetRadianceScaler(0.25);
	SetAmbientLight(ambient_ptr);

	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(0, 0, 10);
	pinhole_ptr->SetLookat(0, 0, 1);    
	pinhole_ptr->SetViewDistance(2800.0);		
	pinhole_ptr->ComputeONB();
	pinhole_ptr->SetNumWorkerThreads(10);
	SetCamera(pinhole_ptr);
	
		
	Directional* light_ptr1 = new Directional;
	light_ptr1->SetDirection(10, 10, 10);   
	light_ptr1->SetRadianceScaler(7.0);  
	light_ptr1->SetShadows(false);
	AddLight(light_ptr1);
		
	Directional* light_ptr2 = new Directional;
	light_ptr2->SetDirection(-1, 0, 0);   
//	light_ptr2->SetRadianceScaler(7.0);  
	light_ptr2->SetRadianceScaler(13.0);  
	light_ptr2->SetShadows(false);
	AddLight(light_ptr2);
	

	// transparent unit sphere at the origin
	
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->SetRefractionIndices(2.42, 1.0);	// glass and air
	dielectric_ptr->SetFilteringColors(WHITE, WHITE);
		
	Sphere* sphere_ptr1 = new Sphere;
	sphere_ptr1->SetMaterial(dielectric_ptr);
	
	// red reflective sphere inside the transparent sphere
	// the red comes from the diffuse color
	
	// the PerfectReflector parameters below are for the reflective sphere in a diamond sphere
		
	PerfectReflector*	reflective_ptr = new PerfectReflector;
	reflective_ptr->SetKa(0.1);	
	reflective_ptr->SetKd(1.0);  
	reflective_ptr->SetCd(RED);
	reflective_ptr->SetKs(0.3);  
	reflective_ptr->SetExponent(200.0);
	reflective_ptr->SetKr(0.75);
	reflective_ptr->SetKr(1.0);
	reflective_ptr->SetCr(WHITE);
	
	double radius = 0.1;
	double distance = 0.8;   // from center of transparent sphere 
		
	Sphere* sphere_ptr2 = new Sphere(Point3D(0, 0, distance), radius);
	sphere_ptr2->SetMaterial(reflective_ptr);

	// store the spheres in a compound object
	
	Compound* spheres_ptr = new Compound;
	spheres_ptr->AddObject(sphere_ptr1);
	spheres_ptr->AddObject(sphere_ptr2);
	
	// now store compound object in an instance so that we can rotate it
	
	Instance* rotated_spheres_ptr = new Instance(spheres_ptr);
	rotated_spheres_ptr->RotateY(172.5);	// for Figure 28.29(a)
//	rotated_spheres_ptr->RotateY(173.0);  	// for Figure 28.29(b)
//	rotated_spheres_ptr->RotateY(178.0);  	// for Figure 28.29(c)
	AddObject(rotated_spheres_ptr);
	
	
	// ground plane
	
	Checker3D* checker3D_ptr = new Checker3D;
	checker3D_ptr->SetSize(50.0); 
	checker3D_ptr->SetColor1(0.5); 
	checker3D_ptr->SetColor2(1.0); 
	
	Matte* sv_matte_ptr = new Matte;		
	sv_matte_ptr->SetKa(0.25);
	sv_matte_ptr->SetKd(0.5);
	sv_matte_ptr->SetDiffuseTexture(checker3D_ptr);
		
	Plane* plane_ptr = new Plane(Point3D(0, -40.5, 0), Normal(0, 1, 0));  
	plane_ptr->SetMaterial(sv_matte_ptr);
	AddObject(plane_ptr);
	*/


	/*
	int num_samples = 16;
	
	m_vp.SetHres(600);	  		
	m_vp.SetVres(600);
	m_vp.SetupSampler(num_samples);
	m_vp.SetMaxDepth(4);
		
	SetBackgroundColor(RGBColor(0.5, 0.5, 1.0));  // light blue
	SetTracer(new RayCast(this));
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());
	
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(0, 0, 2);      
	pinhole_ptr->SetLookat(0, 0, 10);    
	pinhole_ptr->SetViewDistance(200.0);
	pinhole_ptr->SetExposureTime(0.17);  
	pinhole_ptr->ComputeONB();     
	SetCamera(pinhole_ptr);
	
	
	Directional* light_ptr1 = new Directional;
	light_ptr1->SetDirection(0, 1, 0);    // straight down
	light_ptr1->SetRadianceScaler(3.0); 
	light_ptr1->SetShadows(true);
	AddLight(light_ptr1);
	
	
	Directional* light_ptr2 = new Directional;
	light_ptr2->SetDirection(0, -1, 0);    // straight up
	light_ptr2->SetRadianceScaler(2.5); 
	light_ptr2->SetShadows(false);
	AddLight(light_ptr2);
	
	
	// transparent sphere
	
	Dielectric* dielectric_ptr = new Dielectric;
	dielectric_ptr->SetRefractionIndices(2.42, 1.0);
		
	Sphere* sphere_ptr1 = new Sphere(Point3D(0.0), 4.0);
	sphere_ptr1->SetMaterial(dielectric_ptr);
	AddObject(sphere_ptr1);	
	
	
	
	// a ring of spheres around the transparent sphere
	
	double  scaling_factor 	= 2.0;  	// used to scale the radii of the ring and spheres
	double 	sphere_radius 	= 1.75 * scaling_factor;
	double 	ring_radius 	= 10.0 * scaling_factor;
	int 	num_spheres 	= 20;
	int 	delta_theta 	= 20;

	RGBColor color1(1, 0.5, 0);          // orange
	RGBColor color2(0.0, 0.5, 0.25);	  // cyan
	
	
	// Phong material for top half of each sphere
	
	Phong* phong_ptr1 = new Phong;		
	phong_ptr1->SetKa(0.2);
	phong_ptr1->SetKd(1.0);
	phong_ptr1->SetCd(color1);
	phong_ptr1->SetExponent(100.0);
	phong_ptr1->SetKs(0.5);
	phong_ptr1->SetCs(1, 1, 0);
	
	
	// reflective material for bottom half of each sphere
	
	PerfectReflector* reflective_ptr2 = new PerfectReflector;
	reflective_ptr2->SetKa(0.2);
	reflective_ptr2->SetKd(1.0);
	reflective_ptr2->SetCd(color2);
	reflective_ptr2->SetExponent(100.0);
	reflective_ptr2->SetKs(0.5);
	reflective_ptr2->SetCs(1, 1, 0);
	reflective_ptr2->SetKr(0.2);
	
	
	for (int j = 0; j < num_spheres; j++) {
		double xc = ring_radius * sin (j * delta_theta * PI / 180.0);
		double zc = ring_radius * cos (j * delta_theta * PI / 180.0);
		Point3D center(xc, 0, zc);
		
		PartialSphere* top_half_ptr = new PartialSphere(center, sphere_radius, 0, 360, 0, 90);
		top_half_ptr->SetMaterial(j == 0 ? phong_ptr1 : phong_ptr1->AddRef());
		AddObject(top_half_ptr);
		
		PartialSphere* bottom_half_ptr = new PartialSphere(center, sphere_radius, 0, 360, 90, 180);
		bottom_half_ptr->SetMaterial(j == 0 ? reflective_ptr2 : reflective_ptr2->AddRef());
		AddObject(bottom_half_ptr);
	}
	

	// ground plane with checker
	
	Checker3D* checker3D_ptr = new Checker3D;
	checker3D_ptr->SetSize(4.2); 
	checker3D_ptr->SetColor1(WHITE);    	
	checker3D_ptr->SetColor2(0.5);
	
	Matte* sv_matte_ptr = new Matte;		
	sv_matte_ptr->SetKa(0.4);
	sv_matte_ptr->SetKd(0.6);
	sv_matte_ptr->SetDiffuseTexture(checker3D_ptr);
		
	Plane* plane_ptr = new Plane(Point3D(0, -4.5, 0), Normal(0, 1, 0)); 
	plane_ptr->SetMaterial(sv_matte_ptr);
	AddObject(plane_ptr);
	*/


	/*
	int num_samples = 25;
	
	m_vp.SetHres(600);
	m_vp.SetVres(600);
	m_vp.SetupSampler(num_samples);
	m_vp.SetMaxDepth(12);
	
	SetBackgroundColor(RGBColor(0.9, 0.9, 1));  // pale blue
	SetTracer(new RayCast(this));
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->SetRadianceScaler(0.5);
	SetAmbientLight(ambient_ptr);
	
		
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(0, 0, 3); 
	pinhole_ptr->SetLookat(0.0); 
	pinhole_ptr->SetViewDistance(450.0);		// for Figure 28.44(a)
//	pinhole_ptr->SetViewDistance(1800.0);		// for Figure 28.44(b)
	pinhole_ptr->ComputeONB();
	SetCamera(pinhole_ptr);
	
		
	PointLight* light_ptr = new PointLight;
	light_ptr->SetLocation(10, 20, 20);
	light_ptr->SetRadianceScaler(15.0);
	light_ptr->SetShadows(false);
	AddLight(light_ptr);
	
	
	// reflective sphere inside cube
		
	PerfectReflector*	reflective_ptr = new PerfectReflector;
	reflective_ptr->SetKa(0.3);	
	reflective_ptr->SetKd(0.25); 
	reflective_ptr->SetCd(0, 0.25, 1);  
	reflective_ptr->SetKr(0.65); 
	
	Sphere*	sphere_ptr1 = new Sphere(Point3D(0.0), 0.75);
	sphere_ptr1->SetMaterial(reflective_ptr); 
	AddObject(sphere_ptr1);
	
	
	// transparent cube
	
	RGBColor glass_color(0.64, 0.98, 0.88);		// light cyan
	
	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->SetExponent(2000.0); 
	glass_ptr->SetRefractionIndices(1.5, 1.0);	// glass and air
	glass_ptr->SetFilteringColors(glass_color, WHITE);
//	glass_ptr->SetShadows(false);
		
	Box* box_ptr = new Box(Point3D(-1.0), Point3D(1.0));
	box_ptr->SetMaterial(glass_ptr);
	box_ptr->SetShadows(false);
	AddObject(box_ptr);
		
	
	// plane
	
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->SetSize(4.0); 
	checker_ptr->SetColor1(1, 1, 0.4);    		// yellow
	checker_ptr->SetColor2(1, 0.5, 0);   		// orange
	
	Matte* sv_matte_ptr = new Matte;		
	sv_matte_ptr->SetKa(0.5);
	sv_matte_ptr->SetKd(0.1);
	sv_matte_ptr->SetDiffuseTexture(checker_ptr);
	
	Plane* plane_ptr = new Plane(Point3D(0, -10.1, 0), Normal(0, 1, 0)); 
	plane_ptr->SetMaterial(sv_matte_ptr);	
	AddObject(plane_ptr);
	*/


	/*
	int num_samples = 9;
	
	m_vp.SetHres(600);	  		
	m_vp.SetVres(600);
	m_vp.SetupSampler(num_samples);    
	m_vp.SetMaxDepth(6);
		
	SetTracer(new RayCast(this));
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());
	SetBackgroundColor(RGBColor(0.75));  
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->SetRadianceScaler(1.0);
	SetAmbientLight(ambient_ptr);	

	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(10, 12, 20); 
	pinhole_ptr->SetLookat(-3.75, 3, 0);     
	pinhole_ptr->SetViewDistance(1500.0);	
	pinhole_ptr->ComputeONB();  
	pinhole_ptr->SetNumWorkerThreads(20);
	SetCamera(pinhole_ptr);
	
	PointLight* light_ptr1 = new PointLight;
	light_ptr1->SetLocation(20, 25, -20);  
	light_ptr1->SetRadianceScaler(3.0);  
	light_ptr1->SetShadows(true);
	AddLight(light_ptr1);
	
	
	float c = 1.75;  // this allows us to adjust the filter color without changing the hue
	RGBColor glass_color(0.27*c, 0.49*c, 0.42*c);  

		
	Dielectric* glass_ptr = new Dielectric;
	glass_ptr->SetRefractionIndices(1.50, 1.0);		// glass and air
	glass_ptr->SetFilteringColors(glass_color, WHITE);
	
	double 	thickness 	= 0.25;
	double 	height 		= 4.0;
	double 	delta 		= 1.0;			// length change of each box
		
	int 	num_boxes 	= 10;
	double 	x_min 		= -10.0;		// where the boxes start in the x direction
	double 	gap 		= 0.5;   		// gap between the boxes
	
	for (int j = 0; j < num_boxes; j++) {
		double length = thickness + j * delta;
		Point3D p0(x_min + j * (thickness + gap), 0.0, -length);
		Point3D p1(x_min + j * (thickness + gap) + thickness, height, 0.0);
		
		Box* box_ptr = new Box(p0, p1);     
		box_ptr->SetMaterial(j == 0 ? glass_ptr : glass_ptr->AddRef());
		AddObject(box_ptr);
	}
	
	
	// plane
	
	Matte* matte_ptr = new Matte;		
	matte_ptr->SetKa(0.5);
	matte_ptr->SetKd(0.65);
	matte_ptr->SetCd(0.75);
	
	Plane* plane_ptr = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr->SetMaterial(matte_ptr);
	AddObject(plane_ptr);
	*/


	/*
	int numSamples = 16;
	SetupFrameBuffer(2 *  200 + 5, 150);
	
	m_vp.SetHres(200);                                                               	  		
	m_vp.SetVres(150);
	m_vp.SetPixelSize(0.2);  
	m_vp.SetupSampler(numSamples);
	m_vp.SetMaxDepth(5);
	
	SetTracer(new RayCast(this));
	SetBackgroundColor(WHITE);
	
	Ambient* ambient_ptr = new Ambient;
	ambient_ptr->SetRadianceScaler(0.5);
	SetAmbientLight(ambient_ptr);
	
	float vpd = 98;
	float focal_distance = 74;
	float lens_radius = 1.0;
	
	ThinLens* left_camera_ptr = new ThinLens;
	left_camera_ptr->SetSampler(new MultiJittered(numSamples));	
	left_camera_ptr->SetViewDistance(vpd);  
	left_camera_ptr->SetFocalDistance(focal_distance); 
	left_camera_ptr->SetLensRadius(lens_radius);

	ThinLens* right_camera_ptr = new ThinLens;
	right_camera_ptr->SetSampler(new MultiJittered(numSamples));	
	right_camera_ptr->SetViewDistance(vpd);   
	right_camera_ptr->SetFocalDistance(focal_distance); 
	right_camera_ptr->SetLensRadius(lens_radius);

	Stereo* stereo_ptr = new Stereo(left_camera_ptr, right_camera_ptr);
	stereo_ptr->UseParallelViewing();
//	stereo_ptr->UseTransverseViewing();
	stereo_ptr->SetPixelGap(5);
	stereo_ptr->SetEye(0, 6, 50);
	stereo_ptr->SetLookat(0, 6, 0);
	stereo_ptr->ComputeONB();
	stereo_ptr->SetStereoAngle(2.0);  // in degrees
	stereo_ptr->SetupCameras(); 
	SetCamera(stereo_ptr);

	
	// Directional light 

	Directional* light_ptr = new Directional;
	light_ptr->SetDirection(1, 1, 1);     
	light_ptr->SetRadianceScaler(7.5); 
	light_ptr->SetShadows(true);
	AddLight(light_ptr);
	
	
	// box 1
	
	Checker3D* checker_ptr1 = new Checker3D;
	checker_ptr1->SetSize(2.0);
	checker_ptr1->SetColor1(1, 1, 0.33);  		// lemon
	checker_ptr1->SetColor2(BLACK);	 
	
	Matte* sv_matte_ptr1 = new Matte;		
	sv_matte_ptr1->SetKa(0.5);
	sv_matte_ptr1->SetKd(0.35);
	sv_matte_ptr1->SetDiffuseTexture(checker_ptr1);
	
	Box* box_ptr1 = new Box(Point3D(-9, 0, -1), Point3D(-3, 12, 0));
	box_ptr1->SetMaterial(sv_matte_ptr1);
	AddObject(box_ptr1);
		
	
	// box 2
	
	Checker3D* checker_ptr2 = new Checker3D;
	checker_ptr2->SetSize(2.0);
	checker_ptr2->SetColor1(BLACK);  	
	checker_ptr2->SetColor2(0.1, 1, 0.5);	  	// green
	
	Matte* sv_matte_ptr2 = new Matte;		
	sv_matte_ptr2->SetKa(0.5);
	sv_matte_ptr2->SetKd(0.35);
	sv_matte_ptr2->SetDiffuseTexture(checker_ptr2);	
	
	Box* box_ptr2 = new Box(Point3D(-3.25, 0, -25), Point3D(4.75, 14, -24));
	box_ptr2->SetMaterial(sv_matte_ptr2);
	AddObject(box_ptr2);
	
	
	// box 3
	
	Checker3D* checker_ptr3 = new Checker3D;
	checker_ptr3->SetSize(2.0);
	checker_ptr3->SetColor1(BLACK);  	
	checker_ptr3->SetColor2(1, 0.6, 0.15);	  	// orange
	
	Matte* sv_matte_ptr3 = new Matte;		
	sv_matte_ptr3->SetKa(0.5);
	sv_matte_ptr3->SetKd(0.35);
	sv_matte_ptr3->SetDiffuseTexture(checker_ptr3);
		
	Box* box_ptr3 = new Box(Point3D(8, 0, -49), Point3D(18, 15, -48));
	box_ptr3->SetMaterial(sv_matte_ptr3);
	AddObject(box_ptr3);
	

	// ground plane
		
	Checker3D* checker_ptr = new Checker3D;
	checker_ptr->SetSize(8.0);
	checker_ptr->SetColor1(0.25);  				// gray
	checker_ptr->SetColor2(WHITE);	 
	
	Matte* sv_matte_ptr = new Matte;		
	sv_matte_ptr->SetKa(0.5);
	sv_matte_ptr->SetKd(0.35);
	sv_matte_ptr->SetDiffuseTexture(checker_ptr);	

	Plane* plane_ptr1 = new Plane(Point3D(0.0), Normal(0, 1, 0));
	plane_ptr1->SetMaterial(sv_matte_ptr);
	AddObject(plane_ptr1);
	*/


	/*
	int numSamples = 25;
	
	m_vp.SetHres(600);      
	m_vp.SetVres(600);    
	m_vp.SetupSampler(numSamples);
	m_vp.SetMaxDepth(1);	
	
	SetTracer(new RayCast(this));
	SetBackgroundColor(BLACK);
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());
	
	MultiJittered* sampler_ptr = new MultiJittered(numSamples);
		
//	Ambient* ambient_ptr = new Ambient;
//	ambient_ptr->SetRadianceScaler(1.0);
//	set_ambient_light(ambient_ptr);
		
	AmbientOccluder* occluder_ptr = new AmbientOccluder;
	occluder_ptr->SetMinAmount(0.25);		
	occluder_ptr->SetSampler(sampler_ptr);
	SetAmbientLight(occluder_ptr);

	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(-6, 5, 11);    	
	pinhole_ptr->SetLookat(-0.009 , 0.11, 0);
	pinhole_ptr->SetViewDistance(37500);  
	pinhole_ptr->SetNumWorkerThreads(30);
	pinhole_ptr->ComputeONB();     
	SetCamera(pinhole_ptr); 
	
	Directional* light_ptr = new Directional;
	light_ptr->SetDirection(0.5, 1, 0.75);
	light_ptr->SetRadianceScaler(1.0);
	light_ptr->SetShadows(true);
	AddLight(light_ptr);
	
	
	Phong* phong_ptr = new Phong;			
	phong_ptr->SetKa(0.2); 
	phong_ptr->SetKd(0.95); 
	phong_ptr->SetCd(1, 0.6, 0);   // orange
	phong_ptr->SetKs(0.5);  
	phong_ptr->SetExponent(20); 
	phong_ptr->SetCs(1, 0.6, 0);   // orange   
		
	const char* file_name = "./Resources/dragon.ply";		
	MeshGrid* dragon_ptr = new MeshGrid();
	dragon_ptr->ReadFlatTriangles(file_name);		
//	dragon_ptr->ReadSmoothTriangles(file_name);
	dragon_ptr->SetMaterial(phong_ptr); 
	dragon_ptr->MakeCells();
	AddObject(dragon_ptr);

	
	PerfectReflector*	reflective_ptr = new PerfectReflector;			
	reflective_ptr->SetKa(0.2); 
	reflective_ptr->SetKd(0.75);
	reflective_ptr->SetCd(0.5);
	reflective_ptr->SetKs(0.0);
	reflective_ptr->SetExponent(20);
	reflective_ptr->SetKr(0.5);  
	reflective_ptr->SetCr(0.8, 1.0, 0.8);    
	
	Plane* plane_ptr = new Plane(Point3D(0, 0.055, 0), Normal(0, 1, 0)); 	
	plane_ptr->SetMaterial(reflective_ptr);
	AddObject(plane_ptr);
	*/


	/*
	int num_samples = 2048;
	
	m_vp.SetHres(600);	  		
	m_vp.SetVres(400);
	m_vp.SetupSampler(num_samples); 
	m_vp.SetMaxDepth(5);
		
	SetTracer(new PathTrace(this));
	SetupFrameBuffer(m_vp.GetHres(), m_vp.GetVres());
	
	Pinhole* pinhole_ptr = new Pinhole;
	pinhole_ptr->SetEye(0, 100, 2);		
	pinhole_ptr->SetLookat(0, 0, 2);
	pinhole_ptr->SetViewDistance(5000);	
	pinhole_ptr->ComputeONB();
	pinhole_ptr->SetNumWorkerThreads(80);
	SetCamera(pinhole_ptr);

	
	// emissive sphere
	
	Emissive* emissive_ptr = new Emissive;
	emissive_ptr->SetCe(0.75, 1, 0.75);
	emissive_ptr->SetRadianceScaler(30.0);   
		
	Sphere* sphere_ptr = new Sphere(Point3D(-2, 7, 6), 1); 
	sphere_ptr->SetMaterial(emissive_ptr);
	sphere_ptr->SetSampler(new MultiJittered(num_samples));
	AddObject(sphere_ptr);
		
	
	// reflective open half cylinder
	
	PerfectReflector* reflective_ptr = new PerfectReflector;
	reflective_ptr->SetKa(0.0); 
	reflective_ptr->SetKd(0.4); 
	reflective_ptr->SetKs(0.0);      
	reflective_ptr->SetExponent(1.0);
	reflective_ptr->SetKr(0.95); 
	reflective_ptr->SetCr(1.0, 0.5, 0.25);  // orange 
	
	double y0 		= -1.0;
	double y1 		= 3.0;
	double radius 	= 3.0;
	double phi_min 	= 90.0;
	double phi_max 	= 270.0;
	
	PartialCylinder* cylinder_ptr = new PartialCylinder(y0, y1, radius, phi_min, phi_max); 
	cylinder_ptr->SetMaterial(reflective_ptr);
	AddObject(cylinder_ptr);	
	
	
	// plane

	Matte* matte_ptr = new Matte;			
	matte_ptr->SetKa(0.0);		
	matte_ptr->SetKd(0.75);
	matte_ptr->SetCd(1);
	matte_ptr->SetSampler(new MultiJittered(num_samples));
	
	Plane* plane_ptr = new Plane(Point3D(0, -1.0, 0), Normal(0, 1, 0)); 	
	plane_ptr->SetMaterial(matte_ptr);
	AddObject(plane_ptr);
	*/
}


void
World::RenderScene(void) const 
{
    if( NULL == m_pCamera )
	{
		RGBColor	result;
		Ray			ray;
		int 		hres 	= m_vp.GetHres();
		int 		vres 	= m_vp.GetVres();
		float		ps		= m_vp.GetPixelSize();
		float		zw		= 100.0;

		ray.d = Vector3D(0, 0, -1);

		for( int row = 0; row < vres; ++row )			// up
			for( int col = 0; col < hres; ++col )		// across
			{										
				ray.o = Point3D(ps * (col - hres / 2.0 + 0.5), ps * (row - vres / 2.0 + 0.5), zw);
				result = m_pTracer->TraceRay(ray);
				SaveColor(row, col, result);
			}
	}
	else	m_pCamera->RenderScene(*this);

	SaveToPPM();
}


void
World::DeleteObjects(void) 
{
	size_t num = m_objects.size();

	for( size_t i = 0; i < num; ++i )
		SAFE_DELETE(m_objects[i]);

	m_objects.erase(m_objects.begin(), m_objects.end());
}


void
World::DeleteLights(void) 
{
	size_t num = m_lights.size();

	for( size_t i = 0; i < num; ++i ) 
	{
		delete m_lights[i];
		m_lights[i] = NULL;
	}

	m_lights.erase(m_lights.begin(), m_lights.end());
}