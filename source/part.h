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

    static const float xNy[9][2][2];

    float lower_x;
    float lower_y;
    float upper_x;
    float upper_y;

    public: 
    part(){};

    void init(int p, int ps){
        plane = p;

        lower_x = xNy[ps][0][0];
        lower_y = xNy[ps][0][1];
        upper_x = xNy[ps][1][0];
        upper_y = xNy[ps][1][1];
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

};
