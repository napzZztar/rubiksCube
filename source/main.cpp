#include <iostream>
#include <GL/glut.h>
#include "part.h"

using namespace std;


const float part::xNy[9][2][2] = {
    {{-1.5 , -1.5} , {-0.52 , -0.52}} ,
    {{-0.5 , -1.5} , {0.48  , -0.52}} ,
    {{0.5  , -1.5} , {1.48  , -0.52}} ,
    {{-1.5 , -0.5} , {-0.52 , 0.48 }} ,
    {{-0.5 , -0.5} , {0.48  , 0.48 }} ,
    {{0.5  , -0.5} , {1.48  , 0.48 }} ,
    {{-1.5 , 0.5}  , {-0.52 , 1.48 }} ,
    {{-0.5 , 0.5}  , {0.48  , 1.48 }} ,
    {{0.5  , 0.5}  , {1.48  , 1.48 }} ,
};

part cube[7][9];

static GLfloat spin = 0.0;
static GLfloat spin_speed = 6.0;

char move;

float rate = 0.9;
float spin_x = 1;
float spin_y = 0;
float spin_z = 0;

void init();
void myDisplay();
void spinDisplay(void);
void initCube();

int main(int argc, char** argv){
    initCube();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Rubik's cube");
    init();
    glutDisplayFunc(myDisplay);
    glutIdleFunc(spinDisplay);
    glutKeyboardFunc(keyPress);
    glutMouseFunc(mouseClick);

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    glScalef(0.15, 0.2667, 0.15);

    int seq[7] = {0,6,4,3,1,2,5};

    glRotatef(20, 0.01, -0.01, 0.01);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            if (( j==2|| j==5 || j==8 || i==5) && i!=2) {
                glPushMatrix();
                glRotatef(spin, spin_x, spin_y, spin_z);
            }

            cube[seq[i]][j].plot();

            if (( j==2|| j==5 || j==8 || i==5) && i!=2) 
                glPopMatrix();
        }
    }

    glFlush();
    glutSwapBuffers();
}

void spinDisplay(void){
    // if(spin_speed > 0.5){
    //     if(spin > 80){
    //         spin_speed -= rate;
    //         rate += 0.9;
    //     }
    // }

    if(spin < 90)
        spin += spin_speed;
    else
        spin = 90;

    glutPostRedisplay();
}

void initCube(){
    for (int i = 1; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            cube[i][j].init(i, j);
        }
    }
}

void mouseClick(int button, int state, int x, int y){
    switch (button) {
        case GLUT_LEFT_BUTTON:
            spin = 0;
            rate=0.9;
            break;
    }
}
void keyPress(unsigned char key, int x, int y){

}
