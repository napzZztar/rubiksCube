#include <iostream>
#include <GL/glut.h>
#include "part.h"

using namespace std;


const float part::xNy[9][2][2] = {
    {{-1.5 , -1.5} , {-0.5 , -0.5}} , 
    {{-0.5 , -1.5} , {0.5  , -0.5}} , 
    {{0.5  , -1.5} , {1.5  , -0.5}} , 
    {{-1.5, -0.5}, {-0.5, 0.5}},
    {{-0.5, -0.5}, {0.5, 0.5}},
    {{0.5, -0.5}, {1.5, 0.5}},
    {{-1.5, 0.5}, {-0.5, 1.5}},
    {{-0.5, 0.5}, {0.5, 1.5}},
    {{0.5, 0.5}, {1.5, 1.5}},
};

static GLfloat spin = 0.0;
static GLfloat spin_speed = 2.0;

float spin_x = 1;
float spin_y = 1;
float spin_z = 1;

void init();
void myDisplay();
void spinDisplay(void);

int main(int argc, char** argv){


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Rubik's cube");
    init();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(spinDisplay);
    glutMainLoop();
    glutSwapBuffers();

    return 0;
}

void init(){
    glClearColor(0, 0, 0, 1);
    glShadeModel(GL_SMOOTH);
    glClearDepth(0.0f);
    glEnable(GL_DEPTH_TEST);
}

void myDisplay(void){
    part p[9];
    part q[9];
    for (int i = 0; i < 9; i++) {
        p[i].init(1, i);
    }
    for (int i = 0; i < 9; i++) {
        q[i].init(2, i);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    glScalef(0.1, 0.1778, 0.1);
    glRotatef(spin, spin_x, spin_y, spin_z);

    for (int i = 0; i < 9; i++) {
        q[i].plot();
    }
    for (int i = 0; i < 9; i++) {
        p[i].plot();
    }

    glFlush();
    glutSwapBuffers();
}

void spinDisplay(void){

    spin += spin_speed;

    if (spin>360.0) 
        spin = 0;

    glutPostRedisplay();
}
