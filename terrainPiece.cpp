//
//  terrainPiece.cpp
//  3D
//
//  Created by Daan Vijfvinkel on 03-09-21.
//  Copyright © 2021 Daan Vijfvinkel. All rights reserved.
//

#include <iostream>
#include "terrainPiece.h"

terrainPiece::terrainPiece(){}

terrainPiece::terrainPiece(float x, float y, float z, float xcoords[], float ycoords[], float zcoords[], float boxx, float boxy, float boxz, float sizefactor, int Id, int texn){
    pos.x = x;
    pos.y = y;
    pos.z = z;
    for (int i = 0; i < 8; i++){
        corners[i].x = xcoords[i] * sizefactor;
        corners[i].y = ycoords[i] * sizefactor;
        corners[i].z = zcoords[i] * sizefactor;
    }
    box.x = boxx * sizefactor;
    box.y = boxy * sizefactor;
    box.z = boxz * sizefactor;
    
    ID = Id;
    texnum = texn;
}
