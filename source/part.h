#include <GL/glut.h>

class part{
    int plane;

    float lower_x;
    float lower_y;
    float upper_x;
    float upper_y;

    public: 
    part(float x1, float y1, float x2, float y2, int p){
        plane = p;

        lower_x = x1;
        lower_y = y1;
        upper_x = x2;
        upper_y = y2;
    }

    void plot(){
        if(plane==1 || plane==3){
            glColor4f(1.0, 0.0, 0.0, 0.0);

            if (plane == 3)
                glColor4f(1.0, 0.5, 0.0, 0.0);

            glBegin(GL_POLYGON);
            glVertex3f( lower_x, lower_y, 1.5);
            glVertex3f( upper_x, lower_y, 1.5);
            glVertex3f( upper_x, upper_y, 1.5);
            glVertex3f( lower_x, upper_y, 1.5);
            glEnd();

        }else if(plane==1 || plane==3){
            glColor4f(1.0, 1.0, 1.0, 0.0);

            glBegin(GL_POLYGON);
            glVertex3f( lower_x, lower_y, 1.5);
            glVertex3f( upper_x, lower_y, 1.5);
            glVertex3f( upper_x, upper_y, 1.5);
            glVertex3f( lower_x, upper_y, 1.5);
            glEnd();
        }
    }

};
