//
//  terrainPiece.hpp
//  3D
//
//  Created by Daan Vijfvinkel on 03-09-21.
//  Copyright © 2021 Daan Vijfvinkel. All rights reserved.
//

#ifndef terrainPiece_h
#define terrainPiece_h

#include <glm/glm.hpp>

class terrainPiece {
public:
    terrainPiece();
    terrainPiece(float x, float y, float z, float xcoords[], float ycoords[], float zcoords[], float boxx, float boxy, float boxz, float sizefactor, int Id, int texn);

    glm::vec3 pos;
    glm::vec3 corners[8];
    glm::vec3 box; //x width, y height, z width
    
    int ID;
    int texnum;
};

#endif /* terrainPiece_h */
