//  Copyright (C) Kevin Suffern 2000-2007.
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.
//  See the file COPYING.txt for the full license.


//  Copyright (C) XFCY(xfcy.jiuxinghechu@gmail.com) 2021-2022
//  This C++ code is for non-commercial purposes only.
//  This C++ code is licensed under the GNU General Public License Version 2.


#include "../Objects/SmoothMeshTriangle.h"

SmoothMeshTriangle::SmoothMeshTriangle(const int i0, const int i1, const int i2)
    : MeshTriangle(i0, i1, i2)
{}


SmoothMeshTriangle::SmoothMeshTriangle(const SmoothMeshTriangle& other)
    : MeshTriangle(other)
{}


SmoothMeshTriangle& SmoothMeshTriangle::operator=(const SmoothMeshTriangle& rhs) 
{
    if( this == &rhs )
        return (*this);
    
    MeshTriangle::operator=(rhs);
    return (*this);
}


SmoothMeshTriangle* SmoothMeshTriangle::Clone(void) const 
{
    return (new SmoothMeshTriangle(*this));
}


SmoothMeshTriangle::~SmoothMeshTriangle(void)
{}