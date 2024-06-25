//
//  entity.cpp
//  3D
//
//  Created by Daan Vijfvinkel on 15-08-21.
//  Copyright © 2021 Daan Vijfvinkel. All rights reserved.
//

#include "entity.h"

entity::entity(){}

entity::entity(float x, float y, float z, float bdboxX, float bdboxY, float bdboxZ, terrainPiece allTerrain[]){
    pos.x = x; newpos.x = x;
    pos.y = y; newpos.y = y;
    pos.z = z; newpos.z = z;
    box.x = bdboxX;
    box.y = bdboxY;
    box.z = bdboxZ;
    gravity = 1;
    std::copy(allTerrain, allTerrain+3, terrain);
}//entity

void entity::doCollission(terrainPiece TP){ //unused, overridden by player docollision
    if (newpos.z > pos.z && pos.z < TP.pos.z){
        pos.x = newpos.x;
        newpos.z = pos.z;
    }
    else if (newpos.z < pos.z && pos.z > TP.pos.z){
        pos.x = newpos.x;
        newpos.z = pos.z;
    }
    if (newpos.x > pos.x && pos.x < TP.pos.x){
        pos.z = newpos.z;
        newpos.x = pos.x;
    }
    else if (newpos.x < pos.x && pos.x > TP.pos.x){
        pos.z = newpos.z;
        newpos.x = pos.x;
    }///x is buggy af, maar alleen bij bepaalde angles...
}

void entity::collissions(){
    bool nocollissions = true;
    bool collissionX = false;
    bool collissionY = false;
    bool collissionZ = false;
    for (int i = 0; i < 3; i++){
        collissionX = newpos.x + box.x >= terrain[i].pos.x + terrain[i].corners[0].x && terrain[i].pos.x + terrain[i].corners[2].x >= newpos.x - box.x;
        collissionY = newpos.y + box.y >= terrain[i].pos.x + terrain[i].corners[5].y && terrain[i].pos.y + terrain[i].corners[5].y >= newpos.y;///WERKT NIET AAA
        collissionZ = newpos.z + box.z >= terrain[i].pos.z + terrain[i].corners[0].z && terrain[i].pos.z + terrain[i].corners[2].z >= newpos.z - box.z;
        
        if (collissionX && collissionY && collissionZ){
            doCollission(terrain[i]);
            nocollissions = false;
        }
        
        if (collissionY){
            //std::cout << i << std::endl;
        }
        
        collissionX = false;
        collissionY = false;
        collissionZ = false;
    }
    
    if (nocollissions){
        pos.x = newpos.x;
        pos.y = newpos.y;
        pos.z = newpos.z;
    }

}

void entity::move(){
    newpos.x += sin(orientation / 180.0 * M_PI) * 1.5;
    newpos.z -= cos(orientation / 180.0 * M_PI) * 1.5;
}

void entity::update(float time){
    if (newpos.y + vel.y < 0){
        vel.y = 0;
        newpos.y = 0;
    }
    else if (vel.y > -5 && pos.y != 0){
        vel.y -= weight;
    }
    newpos.y += vel.y;
    
    collissions();
}//update
