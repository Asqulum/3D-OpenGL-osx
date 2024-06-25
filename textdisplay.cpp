//
//  textdisplay.cpp
//  3D
//
//  Created by Daan Vijfvinkel on 29-08-21.
//  Copyright © 2021 Daan Vijfvinkel. All rights reserved.
//

#include <iostream>
#include "textdisplay.h"

void ddrawText(float x, float y, const char *string, int windowwidth, int windowheight, void *font){//2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, windowwidth, 0.0, windowheight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2i(10 + x, windowheight - 20 - y);

        const char *i;
        for (i=string; *i != '\0'; i++){
            glutBitmapCharacter(font, *i);
        }
    
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void dddrawText(float x, float y, float z, char *string, int windowwidth, int windowheight, void *font, bool center) {//3D
    char *c;
    unsigned int width = 0;
    
    if (center){
         //find width to center text
        for (c=string; *c != '\0'; c++){
            width += glutBitmapWidth(font, *c);
        }
    }
    
    //get matrices
    GLdouble model[16] = {0};
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    GLdouble proj[16] = {0};
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    GLint view[4] = {0};
    glGetIntegerv(GL_VIEWPORT,view);
    
    //these will be calculated in place
    GLdouble winx, winy, winz;
    
    //get screen position from world position
    gluProject(x, y, z, model, proj, view, &winx, &winy, &winz);
    
    //printf("%f,%f,%f\n", winx, winy, winz);
    
    //winz > 1 means that the object is behind the camera so no draw
    if (winz > 1){
        return;
    }
    
    //idk why this sequence of gl calls works, but it does
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
                //this is basically copypaste from ddrawtext
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluOrtho2D(0.0, windowwidth, 0.0, windowheight);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                    glLoadIdentity();
                    glColor3f(1.0, 1.0, 1.0);
                    if (center){
                        glRasterPos2i(winx - width/2, winy);
                    }
                    else{
                        glRasterPos2i(winx, winy);
                    }

                    const char *i;
                    for (i=string; *i != '\0'; i++){
                        glutBitmapCharacter(font, *i);
                    }
                
                glPopMatrix();
                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();
        
        
            glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
