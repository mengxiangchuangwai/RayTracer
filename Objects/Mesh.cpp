//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/Mesh.h"

Mesh::Mesh(void)
    : numVertices(0)
    , numFaces(0)
{}


Mesh::Mesh(const Mesh& other)
    : vertices(other.vertices)
    , normals(other.normals)
    , vertexFaces(other.vertexFaces)
    , tu(other.tu)
    , tv(other.tv)
    , numVertices(other.numVertices)
    , numFaces(other.numFaces)
{
	if( numFaces > 0 )
	{
		faces.reserve(numFaces);
		
		for( int i = 0; i < numFaces; ++i )
			faces.push_back(other.faces[i]->Clone());
	}
}


Mesh& 
Mesh::operator=(const Mesh& rhs) 
{
    if( this == &rhs )
        return(*this);

	Clear();
    vertices        = rhs.vertices;
    normals         = rhs.normals;
    vertexFaces		= rhs.vertexFaces;
    tu              = rhs.tu;
    tv              = rhs.tv;
    numVertices		= rhs.numVertices;
    numFaces		= rhs.numFaces;

	if( numFaces > 0 )
	{
		faces.reserve(numFaces);

		for( int i = 0; i < numFaces; ++i )
			faces.push_back(rhs.faces[i]->Clone());
	}

    return(*this);
}


Mesh* 
Mesh::Clone(void) const 
{
    return (new Mesh(*this));
}


Mesh::~Mesh(void) 
{
    Clear();
}


void 
Mesh::Clear(void) 
{
	if( numFaces > 0 )
	{
		for( int i = 0; i < numFaces; ++i )
			delete faces[i];
	}

	vertices.erase(vertices.begin(), vertices.end());
    faces.erase(faces.begin(), faces.end());
    normals.erase(normals.begin(), normals.end());
    tu.erase(tu.begin(), tu.end());
    tv.erase(tv.begin(), tv.end());

	if( !vertexFaces.empty() ) 
	{
		for( int i = 0; i < numVertices; ++i )
			vertexFaces[i].erase(vertexFaces[i].begin(), vertexFaces[i].end());

		 vertexFaces.erase(vertexFaces.begin(), vertexFaces.end());
	}

	numVertices = 0;
    numFaces = 0;
}