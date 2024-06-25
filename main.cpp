//
//  main.cpp
//  3D
//
//  Created by Daan Vijfvinkel on 22-06-21.
//  Copyright © 2021 Daan Vijfvinkel. All rights reserved.
//


#include <iostream>
#include <stdlib.h>
#include <ApplicationServices/ApplicationServices.h>

//#include <GL/glew.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>
#include <lua.hpp>
#include <glm/glm.hpp>
#include "structs.h"
#include "textureloader.h"
#include "drawing.h"
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
using namespace glm;
//include <fstream>
//#include "stb_image.h"

#define FULLSCREEN false

unsigned int testshader;

#include "terrainPiece.h"
#include "player.h"

float blockx[8] = {-8, -8,  8,  8, -8, -8,  8,  8};
float blocky[8] = {-8, -8, -8, -8,  8,  8,  8,  8};
float blockz[8] = {-8,  8,  8, -8, -8,  8,  8, -8};

int checkers, container, meadow;
terrainPiece testTerrain0, testTerrain1, testTerrain2, floor0;
terrainPiece allTerrain[4]; //also change the loops in drawing.h!


void createTerrain(){
    testTerrain0 = terrainPiece(80, 0, -80, blockx, blocky, blockz, 8, 16, 8, 2.0, 0, container);
    allTerrain[0] = testTerrain0;
    testTerrain1 = terrainPiece(-160, 20, -100, blockx, blocky, blockz, 8, 16, 8, 1.0, 1, container);
    allTerrain[1] = testTerrain1;
    testTerrain2 = terrainPiece(-80, 200, 80, blockx, blocky, blockz, 8, 16, 8, 1.0, 2, container);
    allTerrain[2] = testTerrain2;

    float floorx[8] = {-256, -256,  256,  256, -256, -256,  256,  256};
    float floory[8] = {   0,    0,    0,    0,    1,    1,    1,    1};
    float floorz[8] = {-256,  256,  256, -256, -256,  256,  256, -256};

    floor0 = terrainPiece(0,0,0, floorx, floory, floorz, 256+16, 0, 256+16, 1.0, 69, checkers);
    
    allTerrain[3] = floor0;
}


playable* player0 = new playable(0.0, 150.0, 0.0, 0.0, 0.0, 36, 12, 48, 12, allTerrain, testTerrain0);
entity* testentity = new entity(0.0, 0.0, -200, 12, 48, 12, allTerrain);

entity* allEntities[2] = {player0, testentity}; //also change the loops in drawing.h


#include "input.h"
#include "basicenv.h"

void readConfig(){
    lua_State *L = luaL_newstate();
    assert( L && "Can't create Lua State" );
    lua_gc(L, LUA_GCSTOP, 0);
    luaL_openlibs( L );
    lua_gc(L, LUA_GCRESTART, 0);
    
    luaL_dofile(L, "/Users/Daan5Vinkel/Desktop/Programmeren/3D/3Ddev/3D/cfg.lua");
    
    lua_getglobal(L, "WINDOWHEIGHT");
    int val = lua_tointeger(L, -1);
    winfo.windowheight = val;
    lua_getglobal(L, "WINDOWWIDTH");
    val = lua_tointeger(L, -1);
    winfo.windowwidth = val;
    lua_getglobal(L, "MAX_FPS");
    val = lua_tointeger(L, -1);
    winfo.MAX_FPS = val;
    
    lua_close(L);
}

void createShader(unsigned int &shaderProgram){

    std::cout << "1";
    const char *vertexShaderSource =
        "#version 120\n"
        "attribute vec3 aPos;\n"
        "uniform mat4 modelview_matrix;\n"
        "uniform mat4 projection_matrix;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "}\0";
    
    
    const char *fragmentShaderSource =
        "#version 120\n"
        "uniform vec4 ourColor;\n"
        "void main()\n"
        "{\n"
        "   gl_FragColor = ourColor;\n"
        "}\0";
    //CREATE V SHADER
    GLuint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    
    glCompileShader(vertexShader);
    std::cout << "2";
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    std::cout << "3";
    //CREATE F SHADER
    GLuint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success){
        char infoLog2[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog2);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog2 << std::endl;
    }
    std::cout << "4";//CREATE PROGRAM
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
    }
    std::cout << "5";
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    std::cout << "6";
}

void calculateNormal(float x1, float y1, float z1,
                     float x2, float y2, float z2,
                     float x3, float y3, float z3,
                     float &n1, float &n2, float &n3){
    float v1x, v1y, v1z, v2x, v2y, v2z;
    v1x = x2 -x1; v1y = y2 -y1;
    v1z = z2 -z1; v2x = x3 -x2;
    v2y = y3 -y2; v2z = z3 -z2;
    n1 = fmin(fmax((v1y*v2z) - (v2y*v1z),-1),1);
    n2 = fmin(fmax(-((v1x*v2z) - (v2x*v1z)),-1),1);
    n3 = fmin(fmax((v1x*v2y) - (v2x*v1y),-1),1);
}


//t -> longitude -> orientation,  s -> latitude -> pitch
//3d unit sphere, no regard for camera clipping
void thirdpersontranslate(float orientation, float pitch){
    float t,s,x,y,z;
    const int dist = 50;
    
    t = orientation / 180.0 * M_PI;
    s = pitch / 180.0 * M_PI;
    
    x = sin(t) * cos(s);
    y = sin(s);
    z = cos(t) * cos(s);
    
    glTranslatef(x*dist, -y*dist, -z*dist);
}

void display(){
    checkkeyboard();
    
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    //gluPerspective (120, (GLfloat)windowwidth / (GLfloat)windowheight, 1.0, 1000.0);
    gluPerspective(60, 1, 1, 30);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glRotatef(player0->pitch,       1.0, 0.0, 0.0);
    glRotatef(player0->orientation, 0.0, 1.0, 0.0);
    glTranslatef(-player0->pos.x, -player0->pos.y - player0->playerheight, -player0->pos.z);
    if (pinput.thirdperson){thirdpersontranslate(player0->orientation, player0->pitch);}
    
    draw(allEntities, allTerrain);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        glOrtho(-9.0, 9.0, -9.0, 9.0, 0.0, 30.0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
            drawGUI(player0);
            glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
    glutSwapBuffers();
}

bool up = true; //om te kloten met movement in timer function

void timer(int a = 0){
    static int lastTime;
    int thisTime = glutGet(GLUT_ELAPSED_TIME);
    float time = (thisTime - lastTime) / 250.0;
    lastTime = thisTime;
    
    player0->update(time);
    testentity->orientation++;
    testentity->move();
    testentity->update(time);
    if (up){
        allTerrain[1].pos.y += 1;
        if (allTerrain[1].pos.y >= 40){
            up = false;
        }
    }
    else{
        allTerrain[1].pos.y -= 1;
        if (allTerrain[1].pos.y <= -20){
            up = true;
        }
    }
    
    glutPostRedisplay();
    
    glutTimerFunc(1000/winfo.MAX_FPS, &timer, 0);
}

void reshape (int w, int h){
    winfo.windowwidth = w;
    winfo.windowheight = h;
    winfo.GUIfactor = (float)winfo.windowwidth /(float)winfo.windowheight;
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection
    glLoadIdentity ();
    gluPerspective (120/*90*/, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); //set the perspective (angle of sight, width, height, , depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model
}

int main(int argc, char * argv[]) {
    CGEventSourceSetLocalEventsSuppressionInterval(NULL, 0.0);
    srand(time(NULL));
    //if (!glfwInit()){std::cout << "GLFW INIT GAAT FOUT" << std::endl;}
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    readConfig();
    

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(winfo.windowwidth, winfo.windowheight);
    glutIgnoreKeyRepeat(1);
    glutCreateWindow("3D");
    createShader(testshader);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);
    
    checkers = int(loadTexture());
    container = int(loadTexture("container.bmp"));
    meadow = int(loadTexture("meadow.bmp"));
    
    createTerrain();
    
    glutKeyboardFunc(&keyboard);
    glutSpecialFunc(&specialkeyboard);
    glutKeyboardUpFunc(&keyboardup);
    glutSpecialUpFunc(&specialkeyboardup);
    glutMouseFunc(&mouseButton);
    glutPassiveMotionFunc(&mouseMove);
    
    glutDisplayFunc(&display);
    glutReshapeFunc(&reshape);
    glutTimerFunc(16, &timer, 0);
    
    glutSetWindowTitle("windowed3D");
    if (FULLSCREEN){
        glutFullScreen();
    }
    
    glutMainLoop();
    
    return 0;
}
