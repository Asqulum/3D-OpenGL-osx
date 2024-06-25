//
//  structs.h
//  3D
//
//  Created by Daan Vijfvinkel on 24/05/2024.
//  Copyright © 2024 Daan Vijfvinkel. All rights reserved.
//

#ifndef structs_h
#define structs_h

bool debug = true;

struct windowinfo{
    int MAX_FPS;
    int windowwidth;
    int windowheight;
    float GUIfactor;
    bool chatting = false;
};

typedef struct windowinfo windowinfo;

windowinfo winfo;

struct playerinput{
    bool thirdperson = false;
    GLboolean wPressed = false;
    GLboolean sPressed = false;
    GLboolean aPressed = false;
    GLboolean dPressed = false;
    GLboolean zPressed = false;
    GLboolean spacePressed = false;
};

typedef struct playerinput playerinput;

playerinput pinput;

#endif /* structs_h */
