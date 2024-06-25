//
//  player.cpp
//  3D
//
//  Created by Daan Vijfvinkel on 25-06-21.
//  Copyright © 2021 Daan Vijfvinkel. All rights reserved.
//

#include "player.h"
#include "textdisplay.h"
#include <iterator>
#include <iostream>

playable::playable(float x, float y, float z, float ori, float pitc, float plyrheight, float bdboxX, float bdboxY, float bdboxZ, terrainPiece allTerrain[], terrainPiece testt){
    pos.x = x; newpos.x = x;
    pos.y = y; newpos.y = y;
    pos.z = z; newpos.z = z;
    orientation = ori; pitch = pitc;
    grounded = 0;
    vel.x = 0; vel.y = 0; vel.z = 0;
    hmovespeed = 1.5;
    weight = 0.3;
    playerheight = plyrheight;
    
    box.x = bdboxX;
    box.y = bdboxY;
    box.z = bdboxZ;

    std::copy(allTerrain, allTerrain+3, terrain);
    
    test = testt;

}//entity

void playable::jump(){
    if (grounded){vel.y += 5;}
}//jump

void playable::movefront(){
    newpos.x += sin(orientation / 180.0 * M_PI) * 1.5;
    newpos.z -= cos(orientation / 180.0 * M_PI) * 1.5;
}//movefront

void playable::moveback(){
    newpos.x -= sin(orientation / 180.0 * M_PI) * 1.5;
    newpos.z += cos(orientation / 180.0 * M_PI) * 1.5;
}//moveback

void playable::moveleft(){
    newpos.x -= cos(orientation / 180.0 * M_PI) * 1.5;
    newpos.z -= sin(orientation / 180.0 * M_PI) * 1.5;
}//moveleft x = -1 -> -cos; z = 0 +sin;

void playable::moveright(){
    newpos.x += cos(orientation / 180.0 * M_PI) * 1.5;
    newpos.z += sin(orientation / 180.0 * M_PI) * 1.5;
}//moveright x = 1 -> cos; z = 0 -cos;

void playable::doCollission(terrainPiece TP, glm::vec3 &tmppos){

    glm::vec3 posdiff = TP.pos - tmppos;

    
    //get relative position sign
    bool negX;
    bool negY;
    bool negZ;
    
    //glm::vec3 posdiff = TP.pos - tmppos;
    
    if (posdiff.x < 0){negX = true;}
    else{negX = false;}
    
    if (posdiff.y < 0){negY = true;} //player above TP
    else{negY = false;} //player below TP
    
    
    
    if (posdiff.z < 0){negZ = true;}
    else{negZ = false;}
    
    //get boundaries
    float playerxbound; float playerybound; float playerzbound;
    float tpiecexbound; float tpieceybound; float tpiecezbound;
    //x
    if (negX){
        playerxbound = tmppos.x - box.x;
        tpiecexbound = TP.pos.x + TP.box.x;
    }
    else{
        playerxbound = tmppos.x + box.x;
        tpiecexbound = TP.pos.x - TP.box.x;
    }
    //y
    if (negY){ //player above TP
        playerybound = tmppos.y;
        tpieceybound = TP.pos.y + TP.box.y;
    }
    else{ //player below TP
        playerybound = tmppos.y + box.y;
        tpieceybound = TP.pos.y;
    }
    //z
    if (negZ){
        playerzbound = tmppos.z - box.z;
        tpiecezbound = TP.pos.z + TP.pos.z;
    }
    else{
        playerzbound = tmppos.z + box.z;
        tpiecezbound = TP.pos.z - TP.pos.z;
    }

    bool inyrange = false; //is player directly above or under the TP?
    if (((negX && tmppos.x <= TP.pos.x + TP.box.x) || //in x box
        (!negX && tmppos.x >= TP.pos.x - TP.box.x))
        &&
        ((negZ && tmppos.z <= TP.pos.z + TP.box.z) || //in z box
        (!negZ && tmppos.z >= TP.pos.z - TP.box.z)))
        {inyrange = true;}
    
    bool inxrange = false; //is player directly next to TP on x-axis?
    if (((negY && tmppos.y <= TP.pos.y + TP.box.y) || //in x box
        (!negY && tmppos.y + box.y >= TP.pos.y - TP.box.y))
        &&
        ((negZ && tmppos.z + box.z <= TP.pos.z + TP.box.z) || //in z box
        (!negZ && tmppos.z - box.z >= TP.pos.z - TP.box.z)))
        {inxrange = true;}
        
        
    
    if (inyrange && !inxrange){
        if (negY){ //player above TP
            if (playerybound <= tpieceybound){ //standing on block
                tmppos.y = tpieceybound;
                vel.y = 0;
            }
        }
        else{ //player below TP
            if (playerybound >= tpieceybound){ //head in block
                tmppos.y = tpieceybound - box.y;
                if (playerybound > tpieceybound){ //bonk ur head
                    vel.y = 0;
                }
            }
        }
    }
    
    if (inxrange){
        if (negX){ //player above TP
            if (playerxbound <= tpiecexbound){ //standing on block
                tmppos.x = tpiecexbound;
            }
        }
        else{ //player below TP
            if (playerxbound >= tpiecexbound){ //head in block
                tmppos.x = tpiecexbound;
            }
        }
    }
    
    
    //printf("%i\n", TP.ID);
    //printf("%f\n", posdiff[0]);
    //printf("%f\n", posdiff[1]);
    //printf("%f\n", posdiff[2]);
    //printf("--------\n");

    /**
    bool test1 = false;
    bool test2 = false;
    if (newpos.x > pos.x && pos.x < TP.pos.x){
        test1 = true;
        //pos.z = newpos.z;
        //newpos.x = pos.x;
    }
    else if (newpos.x < pos.x && pos.x > TP.pos.x){
        test1 = true;
        //pos.z = newpos.z;
        //newpos.x = pos.x;
    }///x is buggy af, maar alleen bij bepaalde angles...
    if (newpos.z > pos.z && pos.z < TP.pos.z){
        test2 = true;
        //pos.x = newpos.x;
        //newpos.z = pos.z;
        
    }
    else if (newpos.z < pos.z && pos.z > TP.pos.z){
        test2 = true;
        //pos.x = newpos.x;
        //newpos.z = pos.z;
        
    }
    
    if (test1 && test2){
        newpos.x = pos.x;
        newpos.z = pos.z;
    }
    else if (test1){
        pos.z = newpos.z;
        newpos.x = pos.x;
    }
    else if (test2){
        pos.x = newpos.x;
        newpos.z = pos.z;
    }
    **/
    
}

void playable::collissions(){//moet eigenlijk naar entity
//uses:
//newpos, box terrain[].pos
//changes:
//pos
    glm::vec3 tmppos = newpos;
    
    //insert some logic for determining which terrainpieces to consider

    //doCollission(test, tmppos);
    for (int i = 0; i < 4; i++){
        doCollission(terrain[i], tmppos);
    }
    
    newpos = tmppos;

/**
    bool nocollissions = true;
    bool collissionX = false;
    bool collissionY = false;
    bool collissionZ = false;
    ///OBJECTEN IN POSITIEVE X WORDEN GENEGEERD ?!
    for (int i = 0; i < 4; i++){///nu wordt de vloer nog niet behandeld, later moet dit wel
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

**/
}

void playable::update(float time){
    //below 0 reset velocity and position to 0
    if (newpos.y + vel.y < 0){
        vel.y = 0;
        newpos.y = 0;
    }
    //above 0 apply gravity <- should change later
    else if (vel.y > -5 && pos.y != 0){
        vel.y -= weight;
    }
    newpos.y += vel.y;
    
    //run collissions with newpos
    collissions();
    
    //update position according to newpos
    pos.x = newpos.x;
    pos.y = newpos.y;
    pos.z = newpos.z;
    
    //reset newpos to pos
    newpos = pos;
    
    //ground player if applicable
    if (vel.y == 0){grounded = 1;}
    else{grounded = 0;}
}//update
