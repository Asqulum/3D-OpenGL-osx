//
//  chat.cpp
//  3D
//
//  Created by Daan Vijfvinkel on 28-08-21.
//  Copyright © 2021 Daan Vijfvinkel. All rights reserved.
//

#include "chat.h"
#include <GLUT/glut.h>
#include <iostream>

chatbox::chatbox(){
    newmessage = "";
}

int chatbox::sendchat(){
    if (newmessage == "quit" || newmessage == "exit" || newmessage == "disconnect" || newmessage == "dc"){exit(69);}
    if (newmessage == "debug"){newmessage = ""; return 1;}
    if (newmessage == "3d"){newmessage = ""; return 2;}
    if (newmessage == "help"){newmessage = "'quit': Quits game. 'debug': Toggles debug menu. '3d': Toggles third person view.";}
    if (newmessage != ""){
        chatlog.push_back(newmessage);
        chatduration.push_back(300);
        newmessage = "";
    }
    return 0;
}

void chatbox::appendchat(char input){
    if (input == 127){newmessage.pop_back();}
    else {newmessage.push_back(input);}
}

void chatbox::displaychat(int windowwidth, int windowheight, GLboolean zPressed){
    for (int i = chatlog.size()-1; i >= 0; i--){
        if (chatduration[i] == 0 && !zPressed){
            return;
        }
        else {
            ddrawText(0, - 40+windowheight-18*(chatlog.size()-i), chatlog[i].c_str(), windowwidth, windowheight, GLUT_BITMAP_HELVETICA_18);
            if (chatduration[i] > 0){chatduration[i]--;}
        }
    }
}

void chatbox::typing(int windowwidth, int windowheight){
    if (newmessage != ""){
        ddrawText(0, windowheight-40, newmessage.c_str(), windowwidth, windowheight, GLUT_BITMAP_HELVETICA_18);
    }
    
    glPushMatrix();//chatbox grey
    glColor4f(1, 1, 1, 0.2);
        glTranslatef(0, 18, 0);
        glBegin(GL_POLYGON);
            glVertex2f(0, 0);
            glVertex2f(720, 0);
            glVertex2f(720, 20);
            glVertex2f(0, 20);
        glEnd();
    glPopMatrix();//chatbox grey
    glColor4f(1, 1, 1, 1);
}
