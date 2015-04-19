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

int side[7][3] = {{0}, {0,3,6}, {2,5,8}, {2,5,8}, {0,3,6}, {6,7,8}, {0,1,2}};

part cube[7][9];

static GLfloat spin       = 0.0;
static GLfloat spin_speed = 9.0;

int cs;
int key = '5';

float rate   = 1.0;
float spin_x = 1;
float spin_y = 0;
float spin_z = 0;

void init();
void myDisplay();
void initCube();
void spinColck(void);
void spinAntiClock(void);
void keyPress(void);
void keyAction(char inp);
void setSpin(char ax, int dir);
bool selectParts(int i, int j);

int main(int argc, char** argv){
    initCube();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
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
    GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[]  = {100.0};
    GLfloat light_color[]    = { 1.0f, 0.9451f, 0.6667f, 1.0f }; //Tunglten 100W
    GLfloat light_position[] = { 2.5, 2.5, 3.5, 1.0 };
    GLfloat spot_direction[] = { 0.0, 1.0, -5.5 };
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);

    glEnable(GL_LIGHTING); //lol
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL); //light with the material color
    glEnable(GL_NORMALIZE); //light intencity or reflection (need to research)

    glPushMatrix();

    glLoadIdentity(); //setup light in a clean transformation

    gluPerspective(40, (1280.0f/720.0f), 0.1f, 100);
    glTranslated(0, 0, -10.0);

    // glScalef(0.15, 0.2667, 0.15);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45.0f);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glPopMatrix();
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluPerspective(40, (1280.0f/720.0f), 0.1f, 100);
    glTranslated(0, 0, -10.0);
    // glScalef(0.15, 0.2667, 0.15); //too big??
    glColor4f(1.0,1.0,1.0, 1.0);


    glBegin(GL_POLYGON); //temporary BG
    glVertex3f(8  , 8  , -2.0f);
    glVertex3f(-8 , 8  , -2.0f);
    glVertex3f(-8 , -8 , -2.0f);
    glVertex3f(8  , -8 , -2.0f);
    glEnd();

    glRotatef(25, 0.01, -0.01, 0.0001);

    // glutWireCube(3.0);

    for (int i = 1; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            if (selectParts(i, j)){ //returns if rotating this part is necessary
                glPushMatrix();
                glRotatef(spin, spin_x, spin_y, spin_z);
                cube[i][j].plot();
                glPopMatrix();
            }
            else
                cube[i][j].plot();
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
        // key = '5';
        // cs = 0;
        glutIdleFunc(NULL);
        glutKeyboardFunc(keyPress);
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
        // cs = 0;
        // key = '5';
        glutIdleFunc(NULL);
        glutKeyboardFunc(keyPress);
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

void keyPress(unsigned char inp, int x, int y){
    keyAction(inp);
}

void setSpin(char ax, int dir){
    glutKeyboardFunc(NULL); spin_x = 0;
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

    if (dir)
        glutIdleFunc(spinColck);
    else
        glutIdleFunc(spinAntiClock);

    spin       = 0.0;
    rate       = 1.0;
    spin_speed = 9;
}

//int side[7][3] = {{0}, {0,1,2}, {2,5,8}, {6,7,8}, {0,3,6}, {6,7,8}, {0,1,2}};
bool selectParts(int i, int j){
    int sidVal = -1;
    int sideOp = -1;
    if (cs) { //all parts for cube spin
        return true;
    }else if(key == '5'){
        return false;
    }
    else{
        if(key == 'R' || key == 'r'){
            sidVal = 2;
            sideOp = 4;
        }else if(key == 'L' || key == 'l'){
            sidVal = 4;
            sideOp = 2;
        }else if(key == 'U' || key == 'u'){
            sidVal = 5;
            sideOp = 6;
        }else if(key == 'D' || key == 'd'){
            sidVal = 6;
            sideOp = 5;
        }else if(key == 'F' || key == 'f'){
            if((i==1 || ((j == 0|| j==1 || j==2) && (i==5 || i==6)) || ((j == 0|| j==3 || j==6) && (i==2 || i==4))) && (i != 3))
                return true;
            else
                return false;
        }else if(key == 'B' || key == 'b'){
            if((i==3 || ((j == 6|| j==7 || j==8) && (i==5 || i==6)) || ((j == 2|| j==5 || j==8) && (i==2 || i==4))) && (i != 1))
                return true;
            else 
                return false;
        }

        if((i == sidVal || side[sidVal][0] == j || side[sidVal][1] == j || side[sidVal][2] == j) && i != sideOp)
            return true;
    }

    return false;
}

void keyAction(char inp){
    switch (inp) {
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
            break;
        case 'X':
            setSpin('x', 1);
            break;
        case 'x':
            setSpin('x', 0);
            break;
        case 'Y':
            setSpin('y', 1);
            break;
        case 'y':
            setSpin('y', 0);
            break;
        case 'Z':
            setSpin('z', 1);
            break;
        case 'z':
            setSpin('z', 0);
            break;

    }

    key = inp;
    if(inp == 'x' || inp == 'X' || inp == 'y' || inp == 'Y' || inp == 'z' || inp == 'Z')
        cs = 1;
    else
        cs = 0;
}
