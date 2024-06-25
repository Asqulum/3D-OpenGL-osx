//
//  player.h
//  3D
//
//  Created by Daan Vijfvinkel on 25-06-21.
//  Copyright © 2021 Daan Vijfvinkel. All rights reserved.
//

#ifndef player_h
#define player_h

#include <glm/glm.hpp>
#include <math.h>
#include "entity.h"
#include "terrainPiece.h"

class playable : public entity {
public:
    playable(float x, float y, float z, float ori, float pitc, float plyrheight, float bdboxX, float bdboxY, float bdboxZ, terrainPiece allTerrain[], terrainPiece testt);
    
    void doCollission(terrainPiece TP, glm::vec3 &tmppos);
    void collissions();
    void jump();
    void movefront();
    void moveback();
    void moveleft();
    void moveright();
    void update(float time);
    
    float playerheight;
    
    terrainPiece test;
    
private:
    bool grounded;
    float hmovespeed;
};

#endif /* player_h */
