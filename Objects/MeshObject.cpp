//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include <iostream>
#include "../Objects/MeshObject.h"
#include "../Objects/FlatMeshTriangle.h"
#include "../Objects/SmoothMeshTriangle.h"
#include "../Objects/ply.h"

MeshObject::MeshObject(Material* mp)
    : GeometricObject(mp)
	, m_pMesh(NULL)
	, m_reverseNormal(false)
{}


MeshObject::MeshObject(const MeshObject& other)
    : GeometricObject(other)
	, m_reverseNormal(other.m_reverseNormal)
{
	if( other.m_pMesh )
		m_pMesh = other.m_pMesh->Clone();
	else
		m_pMesh = NULL;
}


MeshObject& 
MeshObject::operator= (const MeshObject& rhs) 
{
    if( this == &rhs )
        return (*this);

	GeometricObject::operator= (rhs);

	if( m_pMesh )
	{
		delete m_pMesh;
		m_pMesh = NULL;	
	}

	if( rhs.m_pMesh )
		m_pMesh = rhs.m_pMesh->Clone();

	m_reverseNormal = rhs.m_reverseNormal;

	return (*this);
}


MeshObject* 
MeshObject::Clone(void) const 
{
    return (new MeshObject(*this));
}


MeshObject::~MeshObject(void) 
{
	if( m_pMesh )
	{
		delete m_pMesh;
		m_pMesh = NULL;
	}
}


void 
MeshObject::ComputeVertexNormals(void) 
{
	m_pMesh->normals.reserve(m_pMesh->numVertices);

	for( int i = 0; i < m_pMesh->numVertices; ++i ) 
	{	// for each vertex
		Normal normal;    // is zero at this point

		for( size_t j = 0; j < m_pMesh->vertexFaces[i].size(); ++j )
			normal += m_pMesh->faces[m_pMesh->vertexFaces[i][j]]->GetNormal();

		// The following code attempts to avoid (nan, nan, nan) normalised normals when all components = 0

		if( normal.x == 0.0 && normal.y == 0.0 && normal.z == 0.0 )
			normal.y = 1.0;
		else
			normal.Normalize();

		m_pMesh->normals.push_back(normal);
	}

	// erase the vertex_faces arrays because we have now finished with them

	for( int i = 0; i < m_pMesh->numVertices; ++i )
		m_pMesh->vertexFaces[i].erase(m_pMesh->vertexFaces[i].begin(), m_pMesh->vertexFaces[i].end());

	m_pMesh->vertexFaces.erase( m_pMesh->vertexFaces.begin(), m_pMesh->vertexFaces.end());

	std::cout << "finished constructing normals" << std::endl;
}


void 
MeshObject::ReadPlyFile(const char* pFileName, const int triangleType) 
{
	if( m_pMesh )
		m_pMesh->Clear();
	else if( !(m_pMesh = new Mesh) )
		return;

	// Vertex definition

	typedef struct Vertex {
	  float x,y,z;      // space coordinates
	} Vertex;

	// Face definition. This is the same for all files but is placed here to keep all the definitions together

	typedef struct Face {
	  	unsigned char nverts;    // number of vertex indices in list
	  	int* verts;              // vertex index list
	} Face;

	// list of property information for a vertex
	// this varies depending on what you are reading from the file

	PlyProperty vert_props[] = {
	  {"x", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,x), 0, 0, 0, 0},
	  {"y", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,y), 0, 0, 0, 0},
	  {"z", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,z), 0, 0, 0, 0}
	};

	// list of property information for a face.
	// there is a single property, which is a list
	// this is the same for all files

	PlyProperty face_props[] = {
	  	{"vertex_indices", PLY_INT, PLY_INT, offsetof(Face,verts),
	   		1, PLY_UCHAR, PLY_UCHAR, offsetof(Face,nverts)}
	};

	// local variables

	int 			i,j;
  	PlyFile*		ply;
  	int 			nelems;		// number of element types: 2 in our case - vertices and faces
  	char**			elist;
	int 			file_type;
	float 			version;
	int 			nprops;		// number of properties each element has
	int 			num_elems;	// number of each type of element: number of vertices or number of faces
	PlyProperty**	plist;
	Vertex**		vlist;
	Face**			flist;
	char*			elem_name;
	int				num_comments;
	char**			comments;
	int 			num_obj_info;
	char**			obj_info;


  	// open a ply file for reading

	ply = ply_open_for_reading(pFileName, &nelems, &elist, &file_type, &version);

	if( NULL == ply )
		return;

  	// print what we found out about the file
	std::cout << pFileName << std::endl;
  	printf ("version %f\n", version);
  	printf ("type %d\n", file_type);

  	// go through each kind of element that we learned is in the file and read them
	printf("ates do for %d.\n", nelems);
  	for( i = 0; i < nelems; ++i ) 
	{	// there are only two elements in our files: vertices and faces
	    // get the description of the first element
  	    elem_name = elist[i];
	    plist = ply_get_element_description(ply, elem_name, &num_elems, &nprops);

	    // print the name of the element, for debugging

		std::cout << "element name  " << elem_name << "  num elements = " << num_elems << "  num properties =  " << nprops << std::endl;

	    // if we're on vertex elements, read in the properties

    	if( equal_strings("vertex", elem_name) ) 
		{
	      	// set up for getting vertex elements
	      	// the three properties are the vertex coordinates

			ply_get_property(ply, elem_name, &vert_props[0]);
	      	ply_get_property(ply, elem_name, &vert_props[1]);
		  	ply_get_property(ply, elem_name, &vert_props[2]);

		  	// reserve mesh elements

		  	m_pMesh->numVertices = num_elems;
		  	m_pMesh->vertices.reserve(num_elems);

		  	// grab all the vertex elements
            Vertex vertex;

		  	for (j = 0; j < num_elems; ++j ) 
			{
		        // grab an element from the file

				ply_get_element(ply, (void *)&vertex);
		  		m_pMesh->vertices.push_back(Point3D(vertex.x, vertex.y, vertex.z));
		  	}
    	}

	    // if we're on face elements, read them in

	    if( equal_strings("face", elem_name) ) 
		{
		    // set up for getting face elements

			ply_get_property(ply, elem_name, &face_props[0]);   // only one property - a list

		  	m_pMesh->numFaces = num_elems;
			m_pMesh->faces.reserve(num_elems);  // triangles will be stored in Compound::objects

			// the following code stores the face numbers that are shared by each vertex

			if( triangleType != TT_Flat )
            {
                m_pMesh->vertexFaces.reserve(m_pMesh->numVertices);
                std::vector<int> faceList;

                for( j = 0; j < m_pMesh->numVertices; ++j )
                    m_pMesh->vertexFaces.push_back(faceList); // store empty lists so that we can use the [] notation below
            }

			// grab all the face elements

			int count = 0; // the number of faces read
            Face face;

			for( j = 0; j < num_elems; ++j ) 
			{
			    // grab an element from the file

			    ply_get_element(ply, (void *)&face);

			    // construct a mesh triangle of the specified type

			    if( triangleType == TT_Flat ) 
				{
					FlatMeshTriangle* pTriangle = new FlatMeshTriangle(face.verts[0], face.verts[1], face.verts[2]);
					pTriangle->ComputeNormal(m_pMesh, m_reverseNormal);
					m_pMesh->faces.push_back(pTriangle);
				}
			    else if( triangleType == TT_Smooth ) 
				{
			    	SmoothMeshTriangle* pTriangle = new SmoothMeshTriangle(face.verts[0], face.verts[1], face.verts[2]);
					pTriangle->ComputeNormal(m_pMesh, m_reverseNormal); 	// the "flat triangle" normal is used to compute the average normal at each mesh vertex
					m_pMesh->faces.push_back(pTriangle);					// it's quicker to do it once here, than have to do it on average 6 times in compute_mesh_normals

					// the following code stores a list of all faces that share a vertex
					// it's used for computing the average normal at each vertex in order(num_vertices) time

					m_pMesh->vertexFaces[face.verts[0]].push_back(count);
					m_pMesh->vertexFaces[face.verts[1]].push_back(count);
					m_pMesh->vertexFaces[face.verts[2]].push_back(count);
					count++;
				}
			}
	    }

	    // print out the properties we got, for debugging

	    for( j = 0; j < nprops; ++j )
	    	printf("property %s\n", plist[j]->name);


        for( j = 0; j < nprops; ++j )
            free(plist[j]);

        free(plist);

	}  // end of for (i = 0; i < nelems; i++)


	// grab and print out the comments in the file

	comments = ply_get_comments(ply, &num_comments);

	for( i = 0; i < num_comments; ++i )
	    printf("comment = '%s'\n", comments[i]);

	// grab and print out the object information

	obj_info = ply_get_obj_info(ply, &num_obj_info);

	for( i = 0; i < num_obj_info; ++i )
	    printf("obj_info = '%s'\n", obj_info[i]);

    for( i = 0; i < nelems; ++i )
        free(elist[i]);

    free(elist);
	// close the ply file

	ply_close(ply);
}


void
MeshObject::ReadTexPlyFile(const char* pFileName, const int triangleType) 
{
	if( m_pMesh )
		m_pMesh->Clear();
	else if( !(m_pMesh = new Mesh) )
		return;

	// Vertex definition

	typedef struct Vertex {
	  float x,y,z;             	// space coordinates
	  float u, v;				// texture coordinates
	} Vertex;

	// Face definition. This is the same for all files but is placed here to keep all the defintions together

	typedef struct Face {
	  	unsigned char nverts;    // number of vertex indices in list
	  	int* verts;              // vertex index list
	} Face;

	// list of property information for a vertex - includes the texture coordinates

	PlyProperty vert_props[] = {
	  {"x", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,x), 0, 0, 0, 0},
	  {"y", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,y), 0, 0, 0, 0},
	  {"z", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,z), 0, 0, 0, 0},
	  {"u", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,u), 0, 0, 0, 0},
	  {"v", PLY_FLOAT, PLY_FLOAT, offsetof(Vertex,v), 0, 0, 0, 0}
	};

	// list of property information for a face. This is the same for all files
	// there is a single property, which is a list

	PlyProperty face_props[] = {
	  	{"vertex_indices", PLY_INT, PLY_INT, offsetof(Face,verts),
	   		1, PLY_UCHAR, PLY_UCHAR, offsetof(Face,nverts)}
	};

	// local variables

	int 			i,j;
  	PlyFile*		ply;
  	int 			nelems;		// number of element types: 2 in our case - vertices and faces
  	char**			elist;
	int 			file_type;
	float 			version;
	int 			nprops;		// number of properties each element has
	int 			num_elems;	// number of each type of element: number of vertices or number of faces
	PlyProperty**	plist;
	char*			elem_name;
	int				num_comments;
	char**			comments;
	int 			num_obj_info;
	char**			obj_info;


  	// open a PLY file for reading

	ply = ply_open_for_reading(pFileName, &nelems, &elist, &file_type, &version);

	if( NULL == ply )
		return;

  	// print what we found out about the file

  	printf("version %f\n", version);
  	printf("type %d\n", file_type);

  	// go through each kind of element that we learned is in the file
  	// and read them

  	for( i = 0; i < nelems; ++i ) 
	{   // there are only two elements in our files: vertices and faces
	    // get the description of the first element

	    elem_name = elist[i];
	    plist = ply_get_element_description(ply, elem_name, &num_elems, &nprops);

	    // print the name of the element, for debugging

		std::cout << "element name  " << elem_name << "  num elements = " << num_elems << "  num properties =  " << nprops << std::endl;

	    // if we're on vertex elements, read in the properties

    	if( equal_strings("vertex", elem_name) ) 
		{
	      	// set up for getting vertex elements
	      	// the five properties are the three vertex coordinates and the two texture coordinates

			ply_get_property(ply, elem_name, &vert_props[0]);
	      	ply_get_property(ply, elem_name, &vert_props[1]);
		  	ply_get_property(ply, elem_name, &vert_props[2]);
		  	ply_get_property(ply, elem_name, &vert_props[3]);
		  	ply_get_property(ply, elem_name, &vert_props[4]);

		  	// reserve mesh elements

		  	m_pMesh->numVertices = num_elems;
		  	m_pMesh->vertices.reserve(num_elems);
		  	m_pMesh->tu.reserve(num_elems);
		  	m_pMesh->tv.reserve(num_elems);

		  	// grab all the vertex elements

		  	Vertex vertex;

		  	for( j = 0; j < num_elems; ++j ) 
			{
			    // grab an element from the file

				ply_get_element(ply, (void *)&vertex);

		  		m_pMesh->vertices.push_back(Point3D(vertex.x, vertex.y, vertex.z));
		  		m_pMesh->tu.push_back(vertex.u);
		  		m_pMesh->tv.push_back(vertex.v);
		  	}
    	}

	    // if we're on face elements, read them in

	    if( equal_strings("face", elem_name) ) 
		{
		    // set up for getting face elements

			ply_get_property(ply, elem_name, &face_props[0]);   // only one property - a list

		  	m_pMesh->numFaces = num_elems;
			m_pMesh->faces.reserve(num_elems);  // triangles will be stored in Compound::objects

		  	// new code to store the face numbers that are shared by each vertex

		  	if( triangleType != TT_Flat )
            {
                m_pMesh->vertexFaces.reserve(m_pMesh->numVertices);
                std::vector<int> faceList;

                for( j = 0; j < m_pMesh->numVertices; ++j )
                    m_pMesh->vertexFaces.push_back(faceList); // store empty lists so that we can use the [] notation below
            }

			// grab all the face elements

			Face face;
			int count = 0; // the number of faces read

			for( j = 0; j < num_elems; ++j ) 
			{
			    // grab an element from the file

			    ply_get_element(ply, (void *)&face);

			    // construct a uv mesh triangle of the specified type

			     if( triangleType == TT_Flat ) 
				 {
			    	FlatMeshTriangle* pTriangle = new FlatMeshTriangle(face.verts[0], face.verts[1], face.verts[2]);
			    	pTriangle->ComputeNormal(m_pMesh, m_reverseNormal);
					m_pMesh->faces.push_back(pTriangle);
				}
			    else if( triangleType == TT_Smooth ) 
				{
			    	SmoothMeshTriangle* pTriangle = new SmoothMeshTriangle(face.verts[0], face.verts[1], face.verts[2]);
			    	pTriangle->ComputeNormal(m_pMesh, m_reverseNormal);
					m_pMesh->faces.push_back(pTriangle);

					m_pMesh->vertexFaces[face.verts[0]].push_back(count);
					m_pMesh->vertexFaces[face.verts[1]].push_back(count);
					m_pMesh->vertexFaces[face.verts[2]].push_back(count);
					count++;
				}
			}
	    }

	    // print out the properties we got, for debugging

	    for( j = 0; j < nprops; ++j )
	    	printf("property %s\n", plist[j]->name);

        for( j = 0; j < nprops; ++j )
            free(plist[j]);

        free(plist);

	}  // end of for (i = 0; i < nelems; i++)


	// grab and print out the comments in the file

	comments = ply_get_comments(ply, &num_comments);
	for( i = 0; i < num_comments; ++i )
		printf("comment = '%s'\n", comments[i]);

	// grab and print out the object information

	obj_info = ply_get_obj_info(ply, &num_obj_info);

	for( i = 0; i < num_obj_info; ++i )
	    printf("obj_info = '%s'\n", obj_info[i]);


    for( i = 0; i < nelems; ++i )
        free(elist[i]);

    free(elist);

	// close the ply file

	ply_close(ply);
}


void 
MeshObject::UpdateBoundingBox(void) 
{
	BBox obb;
	Point3D& p0 = m_bbox.p0;
	Point3D& p1 = m_bbox.p1;
	p0 = Point3D(kHugeValue);
	p1 = Point3D(-kHugeValue);
	size_t num = m_pMesh->faces.size();
    
	for( size_t i = 0; i < num; ++i )
	{   
        m_pMesh->faces[i]->GetBoundingBox(m_pMesh, obb);
        
		if( obb.p0.x < p0.x )
            p0.x = obb.p0.x;
      
        if( obb.p0.y < p0.y )
            p0.y = obb.p0.y;
     
        if( obb.p0.z < p0.z )
            p0.z = obb.p0.z;


		if( obb.p1.x > p1.x )
            p1.x = obb.p1.x;
       
        if( obb.p1.y > p1.y )
            p1.y = obb.p1.y;
        
        if( obb.p1.z > p1.z )
            p1.z = obb.p1.z;
    }

    p0.x -= kEpsilon;
    p0.y -= kEpsilon;
    p0.z -= kEpsilon;
    p1.x += kEpsilon;
    p1.y += kEpsilon;
    p1.z += kEpsilon;
}


bool 
MeshObject::Hit(const Ray& ray, double& tmin, ShadeContext& sr) const 
{
    Normal	normal;
    Point3D	localHitPoint;
	double	tv;
    bool	hit = false;
    int		num = m_pMesh->faces.size();
	tmin = kHugeValue;

    for( int i = 0; i < num; ++i ) 
	{
        if( m_pMesh->faces[i]->Hit(m_pMesh, ray, tv, sr) && (tv < tmin) ) 
		{
            hit = true;
            tmin = tv;
            normal = sr.normal;
            localHitPoint = sr.localHitPoint;
        }
    }

    if( hit ) 
	{
        sr.normal = normal;
        sr.localHitPoint = localHitPoint;
    }

    return (hit);
}


bool MeshObject::ShadowHit(const Ray& ray, double& tmin) const 
{
	if( !m_shadowing )
		return (false);

    int num = m_pMesh->faces.size();

    for( int i = 0; i < num; ++i ) 
	{
        if( m_pMesh->faces[i]->ShadowHit(m_pMesh, ray, tmin) )
			return (true);
    }

   return (false);
}