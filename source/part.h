#include <GL/glut.h>
#include "imageloader.h"

#ifndef PART_H
#define PART_H

#define red glColor4f(1.0    , 0.0 , 0.0 , 0.0);
#define green glColor4f(0.0  , 1.0 , 0.0 , 0.0);
#define blue glColor4f(0.0   , 0.0 , 1.0 , 0.0);
#define orange glColor4f(1.0 , 0.5 , 0.0 , 0.0);
#define yellow glColor4f(1.0 , 1.0 , 0.0 , 0.0);
#define white glColor4f(1.0  , 1.0 , 1.0 , 1.0);


void room();
void lamp();
GLint loadTexture(Image *image);

class part{
    int plane; // 1 = red
               // 2 = yellow
               // 3 = orange
               // 4 = white
               // 5 = blue
               // 6 = green

    static const float xNy[9][2][2];
    static const unsigned int map[7];

    float lower_x;
    float lower_y;
    float lower_z;
    float upper_x;
    float upper_y;
    float upper_z;
    char color;

    public: 
    void print();
    void init(int p, int ps);
    void plot();
    void rotate(int ang,char axis);
    void rotatePoint(int ang, char axis, bool se);
    void mulMat();

};

struct rotate{
    float angle;
    float x;
    float y;
    float z;
};

#endif

