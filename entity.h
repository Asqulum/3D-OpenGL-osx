//
//  entity.h
//  3D
//
//  Created by Daan Vijfvinkel on 15-08-21.
//  Copyright © 2021 Daan Vijfvinkel. All rights reserved.
//

#ifndef entity_h
#define entity_h

#include <glm/glm.hpp>
#include <algorithm>
#include "terrainPiece.h"

//#include <math.h>

class entity {
public:
    entity();
    entity(float x, float y, float z, float bdboxX, float bdboxY, float bdboxZ, terrainPiece allTerrain[]);
    void doCollission(terrainPiece TP);
    void collissions();
    void move();
    void update(float time);
    
    glm::vec3 pos;
    glm::vec3 vel;
    glm::vec3 newpos;
    float orientation, pitch;
    float weight;
    bool gravity;
    
    glm::vec3 box;
    
    terrainPiece terrain[4];
    
};

#endif /* entity_h */
