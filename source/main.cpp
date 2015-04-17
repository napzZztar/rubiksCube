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
static GLfloat spin_speed = 9.0;

char move;

float rate = 1.0;
float spin_x = 1;
float spin_y = 0;
float spin_z = 0;

void init();
void myDisplay();
void spinColck(void);
void initCube();
void spinColck(void);
void spinAntiClock(void);
void keyPress(void);
void setSpin(char ax, int rot);

int main(int argc, char** argv){
    initCube();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Rubik's cube");
    glutDisplayFunc(myDisplay);
    // glutIdleFunc(spinColck);
    glutKeyboardFunc(keyPress);

    init();
    glutMainLoop();
    glutSwapBuffers();

    return 0;
}

void init(){ //magic don't touch 
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {99.9};
    GLfloat light_position[] = { -0.1, 1.0, 2.0, 0.3 };
    GLfloat spot_direction[] = { 0.0, -0.8, -2.0 };
    GLfloat light_color[] = { 1.0, 0.9451, 0.6667, 1.0 }; //Tunglten 100W
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);

    glEnable(GL_LIGHTING); //lol
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL); //light with the material color
    glEnable(GL_NORMALIZE); //light intencity or reclection (need to research)

    glPushMatrix();
    glLoadIdentity(); //setup light in a clean transformation
    glScalef(0.15, 0.2667, 0.15);
    glRotatef(90, 1.0, -1.0, 1.0);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 15.0);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glPopMatrix();
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glScalef(0.15, 0.2667, 0.15); //too big??
    glColor3f(0.5,0.5,0.5);

    glBegin(GL_POLYGON); //temporary BG
    glVertex3f(8, 8, -2);
    glVertex3f(-8, 8, -2);
    glVertex3f(-8, -8, -2);
    glVertex3f(8, -8, -2);
    glEnd();

    int seq[7] = {0,6,4,3,1,2,5}; //sequence of planes

    glRotatef(20, 0.01, -0.01, 0.0001);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            if (( j==2|| j==5 || j==8 || i==5) && i!=2){
                glPushMatrix();
                glRotatef(spin, spin_x, spin_y, spin_z);
                cube[seq[i]][j].plot();
                glPopMatrix();
            }else
                cube[seq[i]][j].plot();

        }
    }

    glFlush();
    glutSwapBuffers();
}

void spinColck(void){
    if(spin_speed > 0.5){
        if(spin > 70){
            spin_speed -= rate;
            rate += 0.5;
        }
    }else
        spin_speed = 0.5;

    if(spin < 90)
        spin += spin_speed;
    else{
        spin = 90;
        glutIdleFunc(NULL);
    }

    glutPostRedisplay();
}

void spinAntiClock(void){
    if(spin_speed > 0.5){
        if(spin < -70){
            spin_speed -= rate;
            rate += 0.5;
        }
    }else
        spin_speed = 0.5;

    if(spin > -90)
        spin -= spin_speed;
    else{
        spin = -90;
        glutIdleFunc(NULL);
    }

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
    switch (key) {
        case 'R':
            setSpin('x', 1);
            break;
        case 'r':
            setSpin('x', 0);
            break;
        case 'F':
            setSpin('z', 1);
            break;
        case 'f':
            setSpin('z', 0);
            break;
        case 'B':
            setSpin('z', 1);
            break;
        case 'b':
            setSpin('z', 0);
            break;
        case 'L':
            setSpin('x', 1);
            break;
        case 'l':
            setSpin('x', 0);
            break;
        case 'D':
            setSpin('y', 1);
            break;
        case 'd':
            setSpin('y', 0);
            break;
        case 'U':
            setSpin('y', 1);
            break;
        case 'u':
            setSpin('y', 0);
    }
}

void setSpin(char ax, int rot){
    spin_x = 0;
    spin_y = 0;
    spin_z = 0;

    switch (ax) {
        case 'x':
            spin_x = 1;
            break;
        case 'y':
            spin_y = 1;
            break;
        case 'z':
            spin_z = 1;
            break;
    }

    if (rot)
        glutIdleFunc(spinColck);
    else
        glutIdleFunc(spinAntiClock);

    spin = 0.0;
    rate=1.0;
    spin_speed = 9;
}

