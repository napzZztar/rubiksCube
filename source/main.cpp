#include <queue>
#include <iostream>
#include <GL/glut.h>
#include "part.h"

using namespace std;

int side[7][3] = {{0}, {6,7,8}, {2,5,8}, {0,1,2}, {0,3,6}, {6,7,8}, {0,1,2}};

part cube[7][9];

rotate tilt;
rotate mov;


static GLfloat spin_speed = 9.0;
GLfloat light_position[] = { -5.0, 3.0, -9.0, 1.0 };
GLfloat spot_direction[] = { 0.0, 0.0, -8.5 };

int cs;
int key    = '5';
float lAng = 0;

float rate   = 1.0;
float zoom = 0.9;

void init();
void myDisplay();
void initCube();
void spinColck(void);
void spinAntiClock(void);
void keyPress(void);
void keyPress(unsigned char inp, int x, int y);
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
    GLfloat mat_specular[]   = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat mat_shininess[]  = {10.0};
    GLfloat light_color[]    = { 1.0f, 1.0f, 1.0f, 0.0f }; //Tunglten 100W
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);

    glEnable(GL_LIGHTING); //lol
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL); //light with the material color
    glEnable(GL_NORMALIZE); //light intencity or reflection (need to research)
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();

    glLoadIdentity(); //setup light in a clean transformation

    gluPerspective(40, (1280.0f/720.0f), 0.1f, 100);
    glTranslatef(0, 0, -12.0);

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

    gluPerspective(40, (1280.0f/720.0f), 2.0f, 100);
    glTranslatef(0, 0, -12.0);
    glRotatef(tilt.angle, tilt.x, tilt.y, tilt.z);
    // glScalef(0.15, 0.2667, 0.15); //too big??

    lamp();
    room();

    glScalef(zoom, zoom, zoom);
    glTranslatef(0, zoom+0.5, 0);

    for (int i = 1; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            if (selectParts(i, j)){ //returns if rotating this part is necessary
                glPushMatrix();
                glRotatef(mov.angle , mov.x, mov.y, mov.z);
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
        if(mov.angle > 70){
            spin_speed -= rate;
            rate += 0.5;
        }
    }else
        spin_speed = 0.5;

    if(mov.angle < 90)
        mov.angle += spin_speed;
    else{
        mov.angle = 90;
        // key = '5';
        // cs = 0;
        glutIdleFunc(NULL);
        glutKeyboardFunc(keyPress);
    }

    glutPostRedisplay();
}

void spinAntiClock(void){
    if(spin_speed > 0.5){
        if(mov.angle < -70){
            spin_speed -= rate;
            rate += 0.5;
        }
    }else
        spin_speed = 0.5;

    if(mov.angle > -90)
        mov.angle -= spin_speed;
    else{
        mov.angle = -90;
        // cs = 0;
        // key = '5';
        glutIdleFunc(NULL);
        glutKeyboardFunc(keyPress);
    }

    glutPostRedisplay();
}

void initCube(){
    tilt.angle = 20;
    tilt.x = 1;
    tilt.y = -0.5;
    tilt.z = 0.0;

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            cube[i][j].init(i, j);
            // cube[i][j].rotate(90, 'z');
        }
    }

}

void keyPress(unsigned char inp, int x, int y){
    switch (inp) {
        case '1':
            lAng++;
            glPushMatrix();
            glRotatef(lAng, 1, 0, 0);
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
            glutPostRedisplay();
            glPopMatrix();
            break;
        case '2':
            lAng--;
            glPushMatrix();
            glRotatef(lAng, 1, 0, 0);
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);
            glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
            glutPostRedisplay();
            glPopMatrix();
            break;
        default:
            keyAction(inp);
    }
}

void setSpin(char ax, int dir){
    glutKeyboardFunc(NULL); 
    mov.x = 0;
    mov.y = 0;
    mov.z = 0;

    switch (ax) {
        case 'x':
            mov.x = 1;
            break;
        case 'y':
            mov.y = 1;
            break;
        case 'z':
            mov.z = 1;
            break;
    }

    if (dir)
        glutIdleFunc(spinColck);
    else
        glutIdleFunc(spinAntiClock);

    mov.angle = 0.0;
    rate       = 1.0;
    spin_speed = 9;
}

//int side[7][3] = {{0}, {6,7,8}, {2,5,8}, {0,1,2}, {0,3,6}, {6,7,8}, {0,1,2}};
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
            if (i== 5||((i==1||i==3)&&(j==6||j==7||j==8)) || ((i==2||i==4)&&(j==2||j==5||j==8)))
                return true;
            else
                return false;
        }else if(key == 'D' || key == 'd'){
            if (i== 6||((i==1||i==3)&&(j==0||j==1||j==2)) || ((i==2||i==4)&&(j==0||j==3||j==6)))
                return true;
            else
                return false;
        }else if(key == 'F' || key == 'f'){
            sidVal = 1;
            sideOp = 3;
        }else if(key == 'B' || key == 'b'){
            sidVal = 3;
            sideOp = 1;
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
        case '+':
            if(zoom<1.1)
                zoom += 0.01;
            glutPostRedisplay();
            break;
        case '-':
            if(zoom>0.2)
                zoom -= 0.01;
            glutPostRedisplay();
            break;

    }

    key = inp;
    if(inp == 'x' || inp == 'X' || inp == 'y' || inp == 'Y' || inp == 'z' || inp == 'Z' || inp == '+' || inp == '-')
        cs = 1;
    else
        cs = 0;
}
