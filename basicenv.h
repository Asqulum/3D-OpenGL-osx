//
//  basicenv.h
//  3D
//
//  Created by Daan Vijfvinkel on 24-06-21.
//  Copyright © 2021 Daan Vijfvinkel. All rights reserved.
//

#ifndef basicenv_h
#define basicenv_h
//https://www.krishnamani.in/color-codes-for-rainbow-vibgyor-colours/
void drawbasicenv(unsigned int shader){
    float colors[7][4] = { {0.58, 0, 0.83, 1}, {0.29, 0, 0.51, 0.8}, {0, 0, 1, 0.6}, {0, 1, 0, 0.4}, {1, 1, 0, 0.2}, {1, 0.5, 0, 0.5}, {1, 0, 0, 1} };
    //float vertices[] = {-16, 0, -16,   -16, 0, 16,   16, 0, 16,   16, 0, -16};
    float vertices[] = {-16, 0, -16,   16, 0, 16,   16, 0, -16,
                        16, 0, 16,  -16, 0, -16,  -16, 0, 16};
    int colorcounter = 0;
    
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    
    //glUseProgram(shader);
    ///glUniform4fv(glGetUniformLocation(shader, "modelview_matrix"), 1, GL_MODELVIEW_MATRIX);
    
    ///glUniform4fv(glGetUniformLocation(shader, "projection_matrix"), 1, GL_PROJECTION_MATRIX);
    
    for (int i = -8; i <= 8; i++){
        for (int j = -8; j <= 8; j++){
            glPushMatrix();
                glColor4f(colors[colorcounter%7][0], colors[colorcounter%7][1], colors[colorcounter%7][2], colors[colorcounter%7][3]);
            
            glUniform4f(glGetUniformLocation(shader, "ourColor"), colors[colorcounter%7][0], colors[colorcounter%7][1], colors[colorcounter%7][2], colors[colorcounter%7][3]);
                glTranslatef(32*i, 0, 32*j);
                glBegin(GL_QUADS);
                    glVertex3f(-16, 0, -16);
                    glVertex3f(-16, 0,  16);
                    glVertex3f( 16, 0,  16);
                    glVertex3f( 16, 0, -16);
                glEnd();
                //glDrawArrays(GL_TRIANGLES, 0, 6);
            glPopMatrix();
            colorcounter++;
        }
    }
    
    /*GLfloat midY = 0;
    GLfloat midX = 0;
    GLfloat y;
    glBegin(GL_POINTS);
        glColor3f(1, 1, 1);
        for(GLfloat x = -200; x <= 200; x+=0.05) {
            y = x*x / 100 + 10;
            glVertex3f(midX + x, midY + y, -100);
        }
    glEnd();*/
    
}

#endif /* basicenv_h */
