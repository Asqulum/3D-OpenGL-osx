//
//  input.h
//  3D
//
//  Created by Daan Vijfvinkel on 24-06-21.
//  Copyright © 2021 Daan Vijfvinkel. All rights reserved.
//

#ifndef input_h
#define input_h

#include "structs.h"
#include "player.h"
#include "textdisplay.h"
#include <Carbon/Carbon.h>
#include <CoreGraphics/CGEvent.h>

int defaultx = 960;
int defaulty = 540;

int mouseX;
int mouseY;

bool windowfocussed = false;

void moveCursor(){
    CGPoint pnt;
    
    pnt.x = defaultx;
    pnt.y = defaulty;

    CGWarpMouseCursorPosition(pnt);
}

void moveCursor(int x, int y){//offset by window location, buggy with multiple screens
    CGPoint pnt;
    int windowx = glutGet(GLUT_WINDOW_X);
    int windowy = glutGet(GLUT_WINDOW_Y);
    
    pnt.x = x + windowx;
    pnt.y = y + windowy;

    CGWarpMouseCursorPosition(pnt);
}

void mouseMove (int x, int y){
    float deltaX, deltaY, potentialY;
    float factor = 0.01;
    
    CGEventRef event = CGEventCreate(NULL);
    CGPoint cursor = CGEventGetLocation(event);
    CFRelease(event);
    
    if (windowfocussed){
        if (!winfo.chatting){
            deltaX = cursor.x - defaultx;//x - winfo.windowwidth/2;
            deltaY = cursor.y - defaulty;//y - winfo.windowheight/2;
            
            player0->orientation += deltaX * factor;
            potentialY = deltaY * factor;
            if (player0->pitch + potentialY <= 89 && player0->pitch + potentialY >= -90){
                player0->pitch += potentialY;
            }
        }
        moveCursor();
    }
}

void mouseButton (int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if (windowfocussed){
            moveCursor(mouseX,mouseY);
            CGDisplayShowCursor(0);
        }
        else{
            mouseX = x; mouseY = y;
            CGDisplayHideCursor(0);
            moveCursor(winfo.windowwidth/2, winfo.windowheight/2);
        }
        windowfocussed = !windowfocussed;
    }
}

void keyboard(unsigned char key, int x, int y){
    if (windowfocussed){
        //if (key == 'q'){exit(69);}
        if (!winfo.chatting){
            switch (key) {
                case 'w':
                case 'W':
                    pinput.wPressed = true;
                    break;
                case 's':
                case 'S':
                    pinput.sPressed = true;
                    break;
                case 'a':
                case 'A':
                    pinput.aPressed = true;
                    break;
                case 'd':
                case 'D':
                    pinput.dPressed = true;
                    break;
                /*case 'c':
                    debug = !debug;
                    break;*/
                case 'z':
                case 'Z':
                    pinput.zPressed = true;
                    break;
                case ' ':
                    pinput.spacePressed = true;
                    break;
                case 8:
                    pinput.spacePressed = true;
                    break;
                case 13:
                    winfo.chatting = true;
                    pinput.wPressed = false;
                    pinput.sPressed = false;
                    pinput.aPressed = false;
                    pinput.dPressed = false;
                    pinput.spacePressed = false;
            }
        }
        else{
            if (key == 13){
                switch(chatter->sendchat()){
                    case 1:
                        debug = !debug;
                        break;
                    case 2:
                        pinput.thirdperson = !pinput.thirdperson;
                        break;
                }
                winfo.chatting = false;
            }
            else if (key == 27){
                chatter->newmessage = "";
                winfo.chatting = false;
            }
            else{
                chatter->appendchat(key);
            }
            
        }
    }
}

void keyboardup(unsigned char key, int x, int y){
    switch (key) {
        case 'w':
        case 'W':
            pinput.wPressed = false;
            break;
        case 's':
        case 'S':
            pinput.sPressed = false;
            break;
        case 'a':
        case 'A':
            pinput.aPressed = false;
            break;
        case 'd':
        case 'D':
            pinput.dPressed = false;
            break;
        case 'z':
        case 'Z':
            pinput.zPressed = false;
            break;
        case ' ':
            pinput.spacePressed = false;
            break;
    }
}

void specialkeyboard(int key, int x, int y){
    if (windowfocussed){
        switch (key) {
            case GLUT_KEY_UP:
                pinput.wPressed = true;
                break;
            case GLUT_KEY_DOWN:
                pinput.sPressed = true;
                break;
            case GLUT_KEY_LEFT:
                pinput.aPressed = true;
                break;
            case GLUT_KEY_RIGHT:
                pinput.dPressed = true;
                break;
        }
    }
}

void specialkeyboardup(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP:
            pinput.wPressed = false;
            break;
        case GLUT_KEY_DOWN:
            pinput.sPressed = false;
            break;
        case GLUT_KEY_LEFT:
            pinput.aPressed = false;
            break;
        case GLUT_KEY_RIGHT:
            pinput.dPressed = false;
            break;
    }
}

void checkkeyboard(){
    if (windowfocussed){
        if (pinput.wPressed){
            player0->movefront();
        }
        if (pinput.sPressed){
            player0->moveback();
        }
        if (pinput.aPressed){
            player0->moveleft();
        }
        if (pinput.dPressed){
            player0->moveright();
        }
        if (pinput.spacePressed){
            //player0->posY += 1.0;
            player0->jump();
        }
    }
}


#endif /* input_h */
