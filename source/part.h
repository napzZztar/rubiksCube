#include <GL/glut.h>

#define red glColor4f(1.0, 0.0, 0.0, 0.0); 
#define green glColor4f(0.0, 1.0, 0.0, 0.0); 
#define blue glColor4f(0.0, 0.0, 1.0, 0.0); 
#define orange glColor4f(1.0, 0.5, 0.0, 0.0); 
#define yellow glColor4f(1.0, 1.0, 0.0, 0.0); 
#define white glColor4f(1.0, 1.0, 1.0, 1.0); 

class part{
    int plane; // 1 = red
               // 2 = yellow
               // 3 = orange
               // 4 = white
               // 5 = blue
               // 6 = green

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
            float plane_z = 1.5; //initially for plane 1

            red;

            if (plane == 3){ //if it's the orange side
                orange;
                plane_z = -1.5;
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
        }
    }

};