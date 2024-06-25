//
//  drawing.h
//  3D
//
//  Created by Daan Vijfvinkel on 24/05/2024.
//  Copyright © 2024 Daan Vijfvinkel. All rights reserved.
//

#include <iostream>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include "structs.h"
#include "textdisplay.h"
#include "player.h"
#include "chat.h"
#include "terrainPiece.h"

#ifndef drawing_h
#define drawing_h

chatbox* chatter = new chatbox();

template<typename T>
void drawbox(T ent){
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
    glBindTexture(GL_TEXTURE_2D, ent.texnum);
    
    glPushMatrix();
        glTranslatef(ent.pos.x, ent.pos.y, ent.pos.z);
        glBegin(GL_QUADS);//bottom square
            glTexCoord2f(0.0, 0.0);
            glVertex3f(ent.box.x, 0, ent.box.z);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(-ent.box.x, 0, ent.box.z);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(-ent.box.x, 0, -ent.box.z);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(ent.box.x, 0, -ent.box.z);
        glEnd();//bottom square
    
        glBegin(GL_QUADS);//top square
            glTexCoord2f(0.0, 0.0);
            glVertex3f(ent.box.x, ent.box.y, ent.box.z);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(-ent.box.x, ent.box.y, ent.box.z);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(-ent.box.x, ent.box.y, -ent.box.z);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(ent.box.x, ent.box.y, -ent.box.z);
        glEnd();
    
        glBegin(GL_QUAD_STRIP);//spokes
            glTexCoord2f(0.0, 0.0);
            glVertex3f(ent.box.x, 0, ent.box.z);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(ent.box.x, ent.box.y, ent.box.z);
            
            glTexCoord2f(1.0, 0.0);
            glVertex3f(-ent.box.x, 0, ent.box.z);
            
            glTexCoord2f(1.0, 1.0);
            glVertex3f(-ent.box.x, ent.box.y, ent.box.z);
            
            glTexCoord2f(0.0, 0.0);
            glVertex3f(-ent.box.x, 0, -ent.box.z);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-ent.box.x, ent.box.y, -ent.box.z);
            
            glTexCoord2f(1.0, 0.0);
            glVertex3f(ent.box.x, 0, -ent.box.z);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(ent.box.x, ent.box.y, -ent.box.z);
            
            glTexCoord2f(0.0, 0.0);
            glVertex3f(ent.box.x, 0, ent.box.z);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(ent.box.x, ent.box.y, ent.box.z);
        glEnd();//spokes
    glPopMatrix();
    
    glDisable(GL_TEXTURE_2D);
}

template<typename T>
void drawBBox(T ent){
    glPushMatrix();
        glTranslatef(ent.pos.x, ent.pos.y, ent.pos.z);
        glBegin(GL_LINE_LOOP);//bottom square
            glColor3f(0.52, 0.98, 0.9);
            glVertex3f(ent.box.x, 0, ent.box.z);
            glVertex3f(-ent.box.x, 0, ent.box.z);
            glVertex3f(-ent.box.x, 0, -ent.box.z);
            glVertex3f(ent.box.x, 0, -ent.box.z);
        glEnd();//bottom square
    
        glBegin(GL_LINE_LOOP);//top square
            glColor3f(0.52, 0.98, 0.9);
            glVertex3f(ent.box.x, ent.box.y, ent.box.z);
            glVertex3f(-ent.box.x, ent.box.y, ent.box.z);
            glVertex3f(-ent.box.x, ent.box.y, -ent.box.z);
            glVertex3f(ent.box.x, ent.box.y, -ent.box.z);
        glEnd();
    
        glBegin(GL_LINES);//spokes
            glColor3f(0.52, 0.98, 0.9);
            glVertex3f(ent.box.x, 0, ent.box.z);
            glVertex3f(ent.box.x, ent.box.y, ent.box.z);
    
            glVertex3f(-ent.box.x, 0, ent.box.z);
            glVertex3f(-ent.box.x, ent.box.y, ent.box.z);
    
            glVertex3f(-ent.box.x, 0, -ent.box.z);
            glVertex3f(-ent.box.x, ent.box.y, -ent.box.z);
    
            glVertex3f(ent.box.x, 0, -ent.box.z);
            glVertex3f(ent.box.x, ent.box.y, -ent.box.z);
        glEnd();//spokes
    
        glPointSize(5);
        glBegin(GL_POINTS);
            glColor3f(0.52, 0.98, 0.9);
            glVertex3f(0,0,0);
        glEnd();//mid
    glPopMatrix();
}

template<typename T>
void drawBoundingBox(T* ent){
    glPushMatrix();
        glTranslatef(ent->pos.x, ent->pos.y, ent->pos.z);
        glBegin(GL_LINE_LOOP);//bottom square
            glColor3f(0.98, 0.52, 0.9);
            glVertex3f(ent->box.x, 0, ent->box.z);
            glVertex3f(-ent->box.x, 0, ent->box.z);
            glVertex3f(-ent->box.x, 0, -ent->box.z);
            glVertex3f(ent->box.x, 0, -ent->box.z);
        glEnd();//bottom square
    
        glBegin(GL_LINE_LOOP);//top square
            glColor3f(0.98, 0.52, 0.9);
            glVertex3f(ent->box.x, ent->box.y, ent->box.z);
            glVertex3f(-ent->box.x, ent->box.y, ent->box.z);
            glVertex3f(-ent->box.x, ent->box.y, -ent->box.z);
            glVertex3f(ent->box.x, ent->box.y, -ent->box.z);
        glEnd();
    
        glBegin(GL_LINES);//spokes
            glColor3f(0.98, 0.52, 0.9);
            glVertex3f(ent->box.x, 0, ent->box.z);
            glVertex3f(ent->box.x, ent->box.y, ent->box.z);
    
            glVertex3f(-ent->box.x, 0, ent->box.z);
            glVertex3f(-ent->box.x, ent->box.y, ent->box.z);
    
            glVertex3f(-ent->box.x, 0, -ent->box.z);
            glVertex3f(-ent->box.x, ent->box.y, -ent->box.z);
    
            glVertex3f(ent->box.x, 0, -ent->box.z);
            glVertex3f(ent->box.x, ent->box.y, -ent->box.z);
        glEnd();//spokes
    
        glPointSize(5);
        glBegin(GL_POINTS);
            glColor3f(0.98, 0.52, 0.9);
            glVertex3f(0,0,0);
        glEnd();//mid
    glPopMatrix();
    
    
    glPushMatrix();
        glTranslatef(ent->newpos.x, ent->newpos.y, ent->newpos.z);
        glBegin(GL_LINE_LOOP);//bottom square
            glColor3f(0.98, 0.52, 0.9);
            glVertex3f(ent->box.x, 0, ent->box.z);
            glVertex3f(-ent->box.x, 0, ent->box.z);
            glVertex3f(-ent->box.x, 0, -ent->box.z);
            glVertex3f(ent->box.x, 0, -ent->box.z);
        glEnd();//bottom square
    
        glBegin(GL_LINE_LOOP);//top square
            glColor3f(0.98, 0.52, 0.9);
            glVertex3f(ent->box.x, ent->box.y, ent->box.z);
            glVertex3f(-ent->box.x, ent->box.y, ent->box.z);
            glVertex3f(-ent->box.x, ent->box.y, -ent->box.z);
            glVertex3f(ent->box.x, ent->box.y, -ent->box.z);
        glEnd();
    
        glBegin(GL_LINES);//spokes
            glColor3f(0.98, 0.52, 0.9);
            glVertex3f(ent->box.x, 0, ent->box.z);
            glVertex3f(ent->box.x, ent->box.y, ent->box.z);
    
            glVertex3f(-ent->box.x, 0, ent->box.z);
            glVertex3f(-ent->box.x, ent->box.y, ent->box.z);
    
            glVertex3f(-ent->box.x, 0, -ent->box.z);
            glVertex3f(-ent->box.x, ent->box.y, -ent->box.z);
    
            glVertex3f(ent->box.x, 0, -ent->box.z);
            glVertex3f(ent->box.x, ent->box.y, -ent->box.z);
        glEnd();//spokes
    glPopMatrix();
}


void drawGUI(playable* player0){
    
    glPushMatrix();//crosshair
    glLineWidth(2);
        glBegin(GL_LINES);
            glColor3f(1, 1, 1);
            glVertex3f(-0.1, 0, 0);
            glVertex3f(0.1, 0, 0);
            glVertex3f(0, 0.1*winfo.GUIfactor, 0);
            glVertex3f(0, -0.1*winfo.GUIfactor, 0);
        glEnd();
    glPopMatrix();//crosshair
    
    if (debug){
        std::string posString =  "x:" + std::to_string(player0->pos.x) + ", y:" + std::to_string(player0->pos.y) + ", z:" + std::to_string(player0->pos.z) + ", ori:" + std::to_string(player0->orientation) + ", pitch:" +  std::to_string(player0->pitch);
        char *cposString = &posString[0];
        ddrawText(0,0, cposString, winfo.windowwidth, winfo.windowheight, GLUT_BITMAP_HELVETICA_18);
        
        std::string newposString = "x:" + std::to_string(player0->newpos.x) + ", y:" + std::to_string(player0->newpos.y) + ", z:" + std::to_string(player0->newpos.z) + ", vely:" + std::to_string(player0->vel.y);
        char *cnewposString = &newposString[0];
        ddrawText(0, 18, cnewposString, winfo.windowwidth, winfo.windowheight, GLUT_BITMAP_HELVETICA_18);
    }
    if (winfo.chatting){chatter->typing(winfo.windowwidth, winfo.windowheight);}
    chatter->displaychat(winfo.windowwidth, winfo.windowheight, pinput.zPressed);
}

void drawray(entity *ply){
    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(ply->pos.x, ply->pos.y, ply->pos.z);
            glBegin(GL_LINES);
                glVertex3f(0, 0, 0); //players position
                glVertex3f(sin(ply->orientation / 180.0 * M_PI) * 50, 0, -cos(ply->orientation / 180.0 * M_PI) * 50);
            glEnd();
    glPopMatrix();
}


///TODO find dynamic way to loop through allEntities/allTerrain
void draw(entity* allEntities[], terrainPiece allTerrain[]){
    //drawbasicenv(testshader);
    
    //for (int i = 0; i < sizeof(allTerrain)/sizeof(*allTerrain); i++){
    for (int i = 0; i < 4; i++){
        drawbox(allTerrain[i]);
    }
    
    if (debug){
        dddrawText(allTerrain[1].pos.x,allTerrain[1].pos.y+20,allTerrain[1].pos.z, "Waypoint Marker", winfo.windowwidth, winfo.windowheight, GLUT_BITMAP_HELVETICA_18);
        
        //for (int i = 0; i < sizeof(allEntities)/sizeof(*allEntities); i++){
        for (int i = 0; i < 2; i++){
            drawray(allEntities[i]);
            drawBoundingBox(allEntities[i]);
        }

        //for (int i = 0; i < sizeof(allTerrain)/sizeof(*allTerrain); i++){
        for (int i = 0; i < 4; i++){
            drawBBox(allTerrain[i]);
        }
    }
}

#endif /* drawing_h */
