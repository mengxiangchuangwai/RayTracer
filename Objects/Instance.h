//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __INSTANCE__
#define __INSTANCE__


// This includes a bounding box, instead of computing it.
// This uses extra memory but the object to be transformed may be a grid or some other complex object
// whose bouding box is expensive to compute.

#include "../Objects/GeometricObject.h"
#include "../Utilities/Matrix.h"

class Instance: public GeometricObject {
	public:

		Instance(Material* mp = NULL);

		Instance(GeometricObject* pObject);

		Instance(const Instance& other);

		virtual Instance*
		Clone(void) const;

		virtual
		~Instance(void);

		Instance&
		operator= (const Instance& rhs);

		void
		SetObject(GeometricObject* pObject);

		void
		TransformTexture(const bool val);

		bool
		IsTransformTexture(void) const;

		virtual Material* 
		GetMaterial(void) const;

		virtual void
		UpdateBoundingBox(void);

		virtual bool
		Hit(const Ray& ray, double& tmin, ShadeContext& sr) const;

		virtual bool
		ShadowHit(const Ray& ray, double& tmin) const;

		// affine tranformation functions

		void
		Translate(const Vector3D& t);

		void
		Translate(const double dx, const double dy, const double dz);

		void
		Scale(const Vector3D& s);

		void
		Scale(const double a, const double b, const double c);

		virtual void
		RotateX(const double r);

		virtual void
		RotateY(const double r);

		virtual void
		RotateZ(const double r);

		void
		Shear(const Matrix& m);

		const Matrix&
		GetInverseMatrix(void) const;

		const Matrix&
		GetForwardMatrix(void) const;


	protected:

		GeometricObject*	m_pObject;				// object to be transformed
		mutable Material*	m_pLocalMaterial;		// material of the object
		Matrix				m_inverseMatrix;		// inverse transformation matrix
		Matrix				m_forwardMatrix; 		// transformation matrix
		bool				m_transformTexture;		// do we transform the texture?
};



inline void
Instance::TransformTexture(const bool val) 
{
	m_transformTexture = val;
}


inline bool
Instance::IsTransformTexture(void) const
{
	return (m_transformTexture);
}


inline Material*
Instance::GetMaterial(void) const 
{
	return (m_pLocalMaterial == NULL ? m_pMaterial : m_pLocalMaterial);
}


inline const Matrix&
Instance::GetInverseMatrix(void) const
{
	return (m_inverseMatrix);
}


inline const Matrix&
Instance::GetForwardMatrix(void) const
{
	return (m_forwardMatrix);
}


#endif