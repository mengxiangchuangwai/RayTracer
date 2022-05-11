//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#ifndef __MESH__
#define __MESH__


#include "../Utilities/Normal.h"
#include "../Utilities/Point3D.h"
#include "../Objects/MeshTriangle.h"

#include <vector>

class Mesh {
public:

    std::vector<Point3D>			vertices;
    std::vector<MeshTriangle*>		faces;
    std::vector<Normal>				normals;
    std::vector<std::vector<int>>	vertexFaces;	// faces shared by each vertex
    std::vector<float>				tu;				// texture coordinate
    std::vector<float>				tv;
    int numVertices;
    int numFaces;


public:

    Mesh();

    Mesh(const Mesh& other);

    Mesh& 
	operator=(const Mesh& rhs);

    Mesh* 
	Clone(void) const;

    virtual ~Mesh(void);

	void 
	Clear(void);
};


#endif // __MESH__