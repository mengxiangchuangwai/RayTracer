//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <cmath>
#include "../Objects/Grid.h"
#include "../Utilities/Maths.h"


Grid::Grid(Material* mp)
    : Compound(mp)
{
	m_dims[0] = m_dims[1] = m_dims[2] = 0;
}


Grid::Grid(const int nx, const int ny, const int nz, Material* mp)
    : Compound(mp)
{
	m_dims[0] = nx, m_dims[1] = ny, m_dims[2] = nz;
}


Grid::Grid(const Grid& other)
    : Compound(other)
{
	m_dims[0] = other.m_dims[0];
	m_dims[1] = other.m_dims[1];
	m_dims[2] = other.m_dims[2]; 
	MakeCells();
}


Grid& Grid::operator=(const Grid& rhs) 
{
    if( this == &rhs )
        return (*this);

    Compound::operator= (rhs);
    m_dims[0] = rhs.m_dims[0];
    m_dims[1] = rhs.m_dims[1];
    m_dims[2] = rhs.m_dims[2];
	MakeCells();

    return (*this);
}


Grid* Grid::Clone(void) const 
{
    return (new Grid(*this));
}


Grid::~Grid(void)
{}


void 
Grid::MakeCells(void) 
{
	if( m_objects.empty() )
		return;

	UpdateBoundingBox();

	size_t num = m_objects.size();
	float wx = m_bbox.p1.x - m_bbox.p0.x;
	float wy = m_bbox.p1.y - m_bbox.p0.y;
	float wz = m_bbox.p1.z - m_bbox.p0.z;
	float multiplier = 2.0;
	float s = pow(wx * wy * wz / num, 0.33333f);

	if( m_dims[0] <= 0 || m_dims[1] <= 0 || m_dims[2] <= 0 ) 
	{
		m_dims[0] = multiplier * wx / s + 1;
		m_dims[1] = multiplier * wy / s + 1;
		m_dims[2] = multiplier * wz / s + 1;
	}

	m_cells.erase(m_cells.begin(), m_cells.end());
	m_cells.resize(m_dims[0] * m_dims[1] * m_dims[2]);

	BBox obb;
	int  index, imin[3], imax[3];

	for( size_t i = 0; i < num; ++i )
	{
	//  m_objects[i]->UpdateBoundingBox();
		m_objects[i]->GetBoundingBox(obb);

		imin[0] = clamp((obb.p0.x - m_bbox.p0.x) * m_dims[0] / (wx), 0, m_dims[0] - 1);
		imin[1] = clamp((obb.p0.y - m_bbox.p0.y) * m_dims[1] / (wy), 0, m_dims[1] - 1);
		imin[2] = clamp((obb.p0.z - m_bbox.p0.z) * m_dims[2] / (wz), 0, m_dims[2] - 1);
		imax[0] = clamp((obb.p1.x - m_bbox.p0.x) * m_dims[0] / (wx), 0, m_dims[0] - 1);
		imax[1] = clamp((obb.p1.y - m_bbox.p0.y) * m_dims[1] / (wy), 0, m_dims[1] - 1);
		imax[2] = clamp((obb.p1.z - m_bbox.p0.z) * m_dims[2] / (wz), 0, m_dims[2] - 1);

		for( int iz = imin[2]; iz <= imax[2]; ++iz )
		{
			for( int iy = imin[1]; iy <= imax[1]; ++iy )
				for( int ix = imin[0]; ix <= imax[0]; ++ix )
				{
					index = ix + m_dims[0] * iy + m_dims[0] * m_dims[1] * iz;
					m_cells[index].push_back(m_objects[i]);
				}
		}
    }
}


bool 
Grid::ListHit(const std::list<GeometricObject*>& ls, const Ray& ray, double& tmin, ShadeContext& sr) const 
{
    bool hit = false;
    
	if( !ls.empty() ) 
	{
		Normal normal;
		Point3D localHitPoint;
		double tval;
		Material* pMaterial = NULL;
        tmin = kHugeValue;
		
		for( std::list<GeometricObject*>::const_iterator itor = ls.begin(); itor != ls.end(); ++itor ) 
		{
            const GeometricObject* pObject = *itor;
			sr.pMaterial = NULL;

            if( pObject->Hit(ray, tval, sr) && (tval < tmin) ) 
			{
                hit = true;
                tmin = tval;
				pMaterial = (NULL == sr.pMaterial ? pObject->GetMaterial() : sr.pMaterial);
                normal = sr.normal;
                localHitPoint = sr.localHitPoint;
            }
        }

		if( hit ) 
		{
			sr.normal = normal;
			sr.localHitPoint = localHitPoint;
			sr.pMaterial = m_pLocalMaterial = pMaterial;
		}
    }

    return (hit);
}


bool 
Grid::ListShadowHit(const std::list<GeometricObject*>& ls, const Ray& ray, double& tmin) const 
{  
	bool hit = false;

	if( !ls.empty() ) 
	{
		std::list<GeometricObject*>::const_iterator itor;
		double tval;
        tmin = kHugeValue;

		for( itor = ls.begin(); itor != ls.end(); ++itor ) 
		{
            GeometricObject* pObject = *itor;

            if( pObject->ShadowHit(ray, tval)  && (tval < tmin) )
			{
				hit = true;
				tmin = tval;
			}
		}
    }

	return (hit);

}


bool 
Grid::Intersect(const Ray& ray, double& tval, ShadeContext& sr, bool shadowHit) const 
{
	if( m_dims[0] <= 0 || m_dims[1] <= 0 || m_dims[2] <= 0 )
		return (false);

    double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

    double x0 = m_bbox.p0.x;
    double y0 = m_bbox.p0.y;
    double z0 = m_bbox.p0.z;
    double x1 = m_bbox.p1.x;
    double y1 = m_bbox.p1.y;
    double z1 = m_bbox.p1.z;

	double tmin[3], tmax[3];

	double a = 1.0 / dx;
	if( a >= 0 ) 
	{
		tmin[0] = (x0 - ox) * a;
		tmax[0] = (x1 - ox) * a;
	}
	else 
	{
		tmin[0] = (x1 - ox) * a;
		tmax[0] = (x0 - ox) * a;
	}

	double b = 1.0 / dy;
	if( b >= 0 ) 
	{
		tmin[1] = (y0 - oy) * b;
		tmax[1] = (y1 - oy) * b;
	}
	else 
	{
		tmin[1] = (y1 - oy) * b;
		tmax[1] = (y0 - oy) * b;
	}

	double c = 1.0 / dz;
	if( c >= 0 ) 
	{
		tmin[2] = (z0 - oz) * c;
		tmax[2] = (z1 - oz) * c;
	}
	else 
	{
		tmin[2] = (z1 - oz) * c;
		tmax[2] = (z0 - oz) * c;
	}

	double t0 = min3(tmin[0], tmin[1], tmin[2]);
	double t1 = max3(tmax[0], tmax[1], tmax[2]);

	if( t0 > t1 )
		return (false);

	int ix, iy, iz;

	if( m_bbox.Inside(ray.o) ) 
	{
		ix = clamp((ox - x0) * m_dims[0] / (x1 - x0), 0, m_dims[0] - 1);
		iy = clamp((oy - y0) * m_dims[1] / (y1 - y0), 0, m_dims[1] - 1);
		iz = clamp((oz - z0) * m_dims[2] / (z1 - z0), 0, m_dims[2] - 1);
	}
	else 
	{
		Point3D pt = ray.o + t0 * ray.d;
		ix = clamp((pt.x - x0) * m_dims[0] / (x1 - x0), 0, m_dims[0] - 1);
		iy = clamp((pt.y - y0) * m_dims[1] / (y1 - y0), 0, m_dims[1] - 1);
		iz = clamp((pt.z - z0) * m_dims[2] / (z1 - z0), 0, m_dims[2] - 1);
	}

	double dt[3];
	dt[0] = (tmax[0] - tmin[0]) / m_dims[0];
	dt[1] = (tmax[1] - tmin[1]) / m_dims[1];
	dt[2] = (tmax[2] - tmin[2]) / m_dims[2];

	double tnext[3];
	int    istep[3], istop[3];

	if( dx > 0 ) 
	{
		tnext[0] = tmin[0] + (ix + 1) * dt[0];
		istep[0] = +1;
		istop[0] = m_dims[0];
	}
	else 
	{
		tnext[0] = tmin[0] + (m_dims[0] - ix) * dt[0];
		istep[0] = -1;
		istop[0] = -1;
	}

	if( dx == 0.0 ) 
	{
		tnext[0] = kHugeValue;
		istep[0] = -1;
		istop[0] = -1;
	}


	if( dy > 0 ) 
	{
		tnext[1] = tmin[1] + (iy + 1) * dt[1];
		istep[1] = +1;
		istop[1] = m_dims[1];
	}
	else 
	{
		tnext[1] = tmin[1] + (m_dims[1] - iy) * dt[1];
		istep[1] = -1;
		istop[1] = -1;
	}

	if( dy == 0.0 ) 
	{
		tnext[1] = kHugeValue;
		istep[1] = -1;
		istop[1] = -1;
	}

	if( dz > 0) 
	{
		tnext[2] = tmin[2] + (iz + 1) * dt[2];
		istep[2] = +1;
		istop[2] = m_dims[2];
	}
	else 
	{
		tnext[2] = tmin[2] + (m_dims[2] - iz) * dt[2];
		istep[2] = -1;
		istop[2] = -1;
	}

	if( dz == 0.0 ) 
	{
		tnext[2] = kHugeValue;
		istep[2] = -1;
		istop[2] = -1;
	}

	if( !shadowHit )
	{
		while( true ) 
		{
			const std::list<GeometricObject*>& objectList = m_cells[ix + m_dims[0] * iy + m_dims[0] * m_dims[1] * iz];

			if( tnext[0] < tnext[1] && tnext[0] < tnext[2] ) 
			{
				if( ListHit(objectList, ray, tval, sr) && tval < tnext[0] )
					return (true);

				tnext[0] += dt[0];
				ix += istep[0];

				if( ix == istop[0] )
					return (false);
			}
			else 
			{
				if( tnext[1] < tnext[2] ) 
				{
					if( ListHit(objectList, ray, tval, sr) && tval < tnext[1] )
						return (true);

					tnext[1] += dt[1];
					iy += istep[1];

					if( iy == istop[1] )
						return (false);
				}
				else 
				{
					if( ListHit(objectList, ray, tval, sr) && tval < tnext[2] )
						return (true);

					tnext[2] += dt[2];
					iz += istep[2];

					if( iz == istop[2] )
						return (false);
				}
			}
		}
	}
	else
	{
		while( true ) 
		{
			const std::list<GeometricObject*>& objectList = m_cells[ix + m_dims[0] * iy + m_dims[0] * m_dims[1] * iz];
			
			if( ListShadowHit(objectList, ray, tval) )
				return (true);

			if( tnext[0] < tnext[1] && tnext[0] < tnext[2] ) 
			{
				tnext[0] += dt[0];
				ix += istep[0];

				if( ix == istop[0] )
					return (false);
			}
			else 
			{
				if( tnext[1] < tnext[2] ) 
				{
					tnext[1] += dt[1];
					iy += istep[1];

					if( iy == istop[1] )
						return (false);
				}
				else 
				{
					tnext[2] += dt[2];
					iz += istep[2];

					if( iz == istop[2] )
						return (false);
				}
			}
		}
	}

	return (false);
}