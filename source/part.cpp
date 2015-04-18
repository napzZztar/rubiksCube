#include <iterator>
#include "part.h"

using namespace std;

void DrawSquare(int x, int y){
    glBegin(GL_POLYGON);
    glVertex3f(x  , -2, y  );
    glVertex3f(x  , -2, y+1);
    glVertex3f(x+1, -2, y+1);
    glVertex3f(x+1, -2, y  );
    glEnd();
}

void part::plot(){
    if(plane==1 || plane==3){
        float plane_z = -1.5; //initially for plane 1
        red;

        if (plane == 3){ //if it's the orange side
            orange;
            plane_z = 1.5;
        }

        glBegin(GL_POLYGON);
        glVertex3f( lower_x, lower_y, plane_z);
        glVertex3f( upper_x, lower_y, plane_z);
        glVertex3f( upper_x, upper_y, plane_z);
        glVertex3f( lower_x, upper_y, plane_z);
        glEnd();

    }else if(plane==2 || plane==4){
        float plane_x = 1.5; //initially for plane 2 
        yellow;

        if(plane == 4){ //white layer
            white;
            plane_x = -1.5;
        }

        glBegin(GL_POLYGON);
        glVertex3f(plane_x, lower_x, lower_y);
        glVertex3f(plane_x, upper_x, lower_y);
        glVertex3f(plane_x, upper_x, upper_y);
        glVertex3f(plane_x, lower_x, upper_y);
        glEnd();
    }else if (plane==5 || plane==6) {
        float plane_y = 1.5;
        blue;

        if (plane == 6) {
            green;
            plane_y = -1.5;
        }

        glBegin(GL_POLYGON);
        glVertex3f(lower_x, plane_y, lower_y);
        glVertex3f(upper_x, plane_y, lower_y);
        glVertex3f(upper_x, plane_y, upper_y);
        glVertex3f(lower_x, plane_y, upper_y);
        glEnd();
    }
}

void part::init(int p, int ps){
    plane = p;

    lower_x = xNy[ps][0][0];
    lower_y = xNy[ps][0][1];
    upper_x = xNy[ps][1][0];
    upper_y = xNy[ps][1][1];
}

void chess(){
    glColor3f(0, 0, 0);

    for (int i = -8; i <8; i++) {     //along X axis
        for (int j=-8; j <8; j++) {   //along Y axis
            if( (i%2==0) && (j%2==0) )
                DrawSquare(i,j);
            else if( (i%2!=0) && (j%2!=0) )
                DrawSquare(i,j);
        }
    }

    glFlush();
}
