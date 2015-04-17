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
static GLfloat spin_speed = 5.0;

char move;

float rate = 2.0;
float spin_x = 1;
float spin_y = 0;
float spin_z = 0;

void init();
void myDisplay();
void spinDisplay(void);
void initCube();
void spinDisplay(void);
void spinDisplayRev(void);
void keyPress(void);

int main(int argc, char** argv){
    initCube();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Rubik's cube");
    init();
    glutDisplayFunc(myDisplay);
    // glutIdleFunc(spinDisplay);
    glutKeyboardFunc(keyPress);

    glutMainLoop();
    glutSwapBuffers();

    return 0;
}

void init(){
    GLfloat mat_specular[] = { 4.0, 4.0, 4.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };
    GLfloat light_position[] = { 4.0, 4.0, 4.0, 1.0 };
    GLfloat light_spot[] = { 0.0, 0.0, -1.0, 1.0 };
    glClearColor(0, 0, 0, 1);
    glShadeModel(GL_SMOOTH);
    glClearDepth(0.0f);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
    glDisable(GL_POLYGON_OFFSET_FILL);

    glLoadIdentity();
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_POSITION, light_spot);
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    glScalef(0.15, 0.2667, 0.15);

    int seq[7] = {0,6,4,3,1,2,5};

    glRotatef(20, 0.01, -0.01, 0.01);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            glPushMatrix();
            if (( j==2|| j==5 || j==8 || i==5) && i!=2)
                glRotatef(spin, spin_x, spin_y, spin_z);

            cube[seq[i]][j].plot();
            glPopMatrix();
        }
    }

    glFlush();
    glutSwapBuffers();
}

void spinDisplay(void){
    if(spin_speed > 0.5){
        if(spin > 70){
            spin_speed -= rate;
            rate += 0.5;
        }
    }else
        spin_speed = 0.5;

    if(spin < 90)
        spin += spin_speed;
    else
        spin = 90;

    glutPostRedisplay();
}

void spinDisplayRev(void){
    if(spin_speed > 0.5){
        if(spin < -70){
            spin_speed -= rate;
            rate += 0.5;
        }
    }else
        spin_speed = 0.5;

    if(spin > -90)
        spin -= spin_speed;
    else
        spin = -90;

    glutPostRedisplay();
}

void initCube(){
    for (int i = 1; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            cube[i][j].init(i, j);
        }
    }
}

void keyPress(unsigned char key, int x, int y){
    if (key == 'R') {
            spin = 0.0;
            rate=2.0;
            spin_speed = 9;
            glutIdleFunc(spinDisplay);
    }else if (key == 'r') {
            spin = 0.0;
            rate=2.0;
            spin_speed = 9;
            glutIdleFunc(spinDisplayRev);
    }

}
