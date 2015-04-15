#include <iostream>
#include <GL/glut.h>
#include "part.h"

using namespace std;


const float part::xNy[9][2][2] = {
    {{-1.5 , -1.5} , {-0.6 , -0.6}} ,
    {{-0.5 , -1.5} , {0.4  , -0.6}} ,
    {{0.5  , -1.5} , {1.4  , -0.6}} ,
    {{-1.5 , -0.5} , {-0.6 , 0.4 }} ,
    {{-0.5 , -0.5} , {0.4  , 0.4 }} ,
    {{0.5  , -0.5} , {1.4  , 0.4 }} ,
    {{-1.5 , 0.5}  , {-0.6 , 1.4 }} ,
    {{-0.5 , 0.5}  , {0.4  , 1.4 }} ,
    {{0.5  , 0.5}  , {1.4  , 1.4 }} ,
};

static GLfloat spin = 0.0;
static GLfloat spin_speed = 1.0;

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
    part cube[7][9];
    for (int i = 1; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            cube[i][j].init(i, j);
        }
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    glScalef(0.1, 0.1778, 0.1);
    glRotatef(spin, spin_x, spin_y, spin_z);

    int seq[7] = {0,6,4,3,1,2,5};

    for (int i = 6; i > 0; i--) {
        for (int j = 0; j < 9; j++) {
            cube[seq[i]][j].plot();
        }
    }

    glFlush();
    glutSwapBuffers();
}

void spinDisplay(void){

    if(spin != 200)
        spin++;


    glutPostRedisplay();
}
