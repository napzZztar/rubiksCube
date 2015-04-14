#include <iostream>
#include <GL/glut.h>

using namespace std;

static GLfloat spin = 0.0;
static GLfloat spin_speed = 2.0;

float spin_x = 1;
float spin_y = 1;
float spin_z = 1;

void init();
void myDisplay();
void spinDisplay(void);

void drawColorCube(int x, int y, int z, int s){
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2i(x, y);
    glVertex2i(x+s, y);
    glVertex2i(x, y+s);
    glVertex2i(x+s, y+s);
    glEnd();

    glColor4f(0.5, 0.5, 0.0, 1.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3i(x, y, z+s);
    glVertex3i(x+s, y, z+s);
    glVertex3i(x, y+s, z+s);
    glVertex3i(x+s, y+s, z+s);
    glEnd();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
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
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
}

void myDisplay(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    glRotatef(spin, spin_x, spin_y, spin_z);
    drawColorCube(-2, -2, -2, 2);

    glColor4f(1.0, 1.0, 1.0, .5);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3i(2, 2, 2);
    glVertex3i(2, -2, 2);
    glVertex3i(-2, -2, 2);
    glVertex3i(-2, 2, 2);
    glEnd();

    glFlush();
    glutSwapBuffers();
}

void spinDisplay(void){

    spin += spin_speed;

    if (spin>360.0) {

        spin -= 360.0;
    }
    glutPostRedisplay();
}
