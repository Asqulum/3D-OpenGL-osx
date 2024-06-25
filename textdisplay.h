//
//  textdisplay.h
//  3D
//
//  Created by Daan Vijfvinkel on 28-08-21.
//  Copyright © 2021 Daan Vijfvinkel. All rights reserved.
//

#ifndef textdisplay_h
#define textdisplay_h

#include <GLUT/glut.h>
#include <string.h>

void ddrawText(float x, float y, const char *string, int windowwidth, int windowheight, void *font = GLUT_BITMAP_HELVETICA_18);

void dddrawText(float x, float y, float z, char *string, int windowwidth, int windowheight, void *font = GLUT_BITMAP_HELVETICA_18, bool center = true);

#endif /* textdisplay_h */
