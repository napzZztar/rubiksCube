#include <GL/glut.h>
#ifndef PART_H
#define PART_H

#define red glColor4f(1.0, 0.0, 0.0, 0.0); 
#define green glColor4f(0.0, 1.0, 0.0, 0.0); 
#define blue glColor4f(0.0, 0.0, 1.0, 0.0); 
#define orange glColor4f(1.0, 0.5, 0.0, 0.0); 
#define yellow glColor4f(1.0, 1.0, 0.0, 0.0); 
#define white glColor4f(1.0, 1.0, 1.0, 1.0); 

void mouseClick(int button, int state, int x, int y);
void keyPress(unsigned char key, int x, int y);
void chess();

class part{
    int plane; // 1 = red
               // 2 = yellow
               // 3 = orange
               // 4 = white
               // 5 = blue
               // 6 = green

    static const float xNy[9][2][2];

    float lower_x;
    float lower_y;
    float upper_x;
    float upper_y;

    public: 
    void init(int p, int ps);
    void plot();

};

#endif

