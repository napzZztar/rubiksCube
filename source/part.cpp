#include <iterator>
#include <cmath>
#include <iostream>
#include "part.h"
#include "imageloader.h"

using namespace std;

GLuint _textureId; //The id of the texture

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

GLint loadTexture(Image* image) {
    GLuint textureId;
    glGenTextures(1, &textureId); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
            0,                            //0 for now
            GL_RGB,                       //Format OpenGL uses for image
            image->width, image->height,  //Width and height
            0,                            //The border of the image
            GL_RGB, //GL_RGB, because pixels are stored in RGB format
            GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
            //as unsigned numbers
            image->pixels);               //The actual pixel data
    return textureId; //Returns the id of the texture
}

void DrawSquare(int x, int y){
    glBegin(GL_QUADS);
    glColor3f(0.4, 0, 0);
    glVertex3f(x  , -2, y  );
    glColor3f(0, 0.4, 0);
    glVertex3f(x  , -2, y+1);
    glColor3f(0, 0, 0.4);
    glVertex3f(x+1, -2, y+1);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(x+1, -2, y  );
    glEnd();
}

void part::plot(){
    switch (color) {
        case 'r':
            red;
            break;
        case 'y':
            yellow;
            break;
        case 'o':
            orange
                break;
        case 'w':
            white
                break;
        case 'b':
            blue;
            break;
        case 'g':
            green;
            break;
    }

    if(plane == 2 || plane == 4){
        glBegin(GL_POLYGON);
        glVertex3f(lower_x, lower_y, lower_z);
        glVertex3f(lower_x, lower_y, upper_z);
        glVertex3f(lower_x, upper_y, upper_z);
        glVertex3f(lower_x, upper_y, lower_z);
        glEnd();

        glColor3f(0.0, 0.0, 0.0);
        glLineWidth(2);
        glBegin(GL_LINE_LOOP);
        glVertex3f(lower_x, lower_y, lower_z);
        glVertex3f(lower_x, lower_y, upper_z);
        glVertex3f(lower_x, upper_y, upper_z);
        glVertex3f(lower_x, upper_y, lower_z);
        glEnd();
    }else{
        glBegin(GL_QUADS);
        glVertex3f(lower_x, upper_y, lower_z);
        glVertex3f(upper_x, upper_y, lower_z);
        glVertex3f(upper_x, lower_y, upper_z);
        glVertex3f(lower_x, lower_y, upper_z);
        glEnd();

        glColor3f(0.0, 0.0, 0.0);
        glLineWidth(2);
        glBegin(GL_LINE_LOOP);
        glVertex3f(lower_x, upper_y, lower_z);
        glVertex3f(upper_x, upper_y, lower_z);
        glVertex3f(upper_x, lower_y, upper_z);
        glVertex3f(lower_x, lower_y, upper_z);
        glEnd();
    }

}

void part::init(int p, int ps){
    plane = p;

    if(plane==1 || plane==3){
        upper_z = 1.5;
        lower_z = 1.5;
        color = 'r';

        if (plane == 3){ //if it's the orange side
            upper_z = -1.5;
            lower_z = -1.5;
            color = 'o';
        }

        lower_x = xNy[ps][0][0];
        lower_y = xNy[ps][0][1];
        upper_x = xNy[ps][1][0];
        upper_y = xNy[ps][1][1];

    }else if (plane==2 || plane==4) {
        lower_x = 1.5;
        upper_x = 1.5;
        color = 'y';
        if(plane == 4){ //white layer
            lower_x = -1.5;
            upper_x = -1.5;
            color = 'w';
        }

        lower_y = xNy[ps][0][0];
        lower_z = xNy[ps][0][1];
        upper_y = xNy[ps][1][0];
        upper_z = xNy[ps][1][1];

    }else if (plane==5 || plane==6) {
        lower_y = 1.5;
        upper_y = 1.5;
        color = 'b';

        if (plane == 6) {//green layer
            lower_y = -1.5;
            upper_y = -1.5;
            color = 'g';
        }

        lower_x = xNy[ps][0][0];
        lower_z = xNy[ps][0][1];
        upper_x = xNy[ps][1][0];
        upper_z = xNy[ps][1][1];

    }
}

void part::print(){
    cout<<lower_x<<endl;
    cout<<lower_y<<endl;
    cout<<lower_z<<endl;
    cout<<upper_x<<endl;
    cout<<upper_y<<endl;
    cout<<upper_z<<endl<<endl;
}

void room(){
    Image* image = loadBMP("../img/tile.bmp");
    _textureId = loadTexture(image);
    delete image;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    glPushMatrix();
    glTranslatef(0,0,-1.5);
    glRotatef(10, 0,1,0);

    // for (int i = -8; i <8; i++) {     //along X axis
    //     for (int j=-8; j <8; j++) {   //along Y axis
    //         if( (i+j) %2 ==0){
    //             glColor3f(0, 0, 0);
    //             DrawSquare(i,j);
    //         }else{
    //             glColor3f(0.6, 0.8, 1);
    //             glBegin(GL_QUADS);
    //             glVertex3f(i  , -2, j  );
    //             glVertex3f(i  , -2, j+1);
    //             glVertex3f(i+1, -2, j+1);
    //             glVertex3f(i+1, -2, j  );
    //             glEnd();
    //         }
    //
    //     }
    // }


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


    glBegin(GL_QUADS); //floor
    glNormal3f(0.0, 0.0f, 1.0f);
    glTexCoord2d(0, 8);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-8 , -2 , -8);
    glTexCoord2d(8, 8);
    glColor3f(0.3f, 0.3f, 0.2f);
    glVertex3f(8  , -2 , -8);
    glTexCoord2d(8, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(8  , -2 , 8);
    glTexCoord2d(0, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-8 , -2 , 8);
    glEnd();

    glColor3f(0.1765f, 0.16471f, 0.7725f);
    glBegin(GL_POLYGON); //back wall
    glColor3f(0.0565f, 0.04471f, 0.4725f);
    glVertex3f(8.0  , -2.0 , -8.0);
    glColor3f(0.1765f, 0.16471f, 0.7725f);
    glVertex3f(8.0  , 4.0  , -8.0);
    glColor3f(0.1765f, 0.16471f, 0.7725f);
    glVertex3f(-8.0 , 4.0  , -8.0);
    glColor3f(0.0765f, 0.06471f, 0.6725f);
    glVertex3f(-8.0 , -2.0 , -8.0);
    glEnd();

    glBegin(GL_POLYGON); //right wall
    glColor3f(0.0555f, 0.04371f, 0.4625f);
    glVertex3f(8.0  , -2.0 , -8.0);
    glColor3f(0.1765f, 0.16471f, 0.7725f);
    glVertex3f(8.0  , -2.0 , 8.0);
    glColor3f(0.1765f, 0.16471f, 0.7725f);
    glVertex3f(8.0  , 4.0  , 8.0);
    glColor3f(0.0765f, 0.06471f, 0.6725f);
    glVertex3f(8.0  , 4.0  , -8.0);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON); //roof
    glVertex3f(8.0  , 4.0 , 8.0);
    glVertex3f(-8.0 , 4.0 , 8.0);
    glColor3f(0.8765f, 0.86471f, 1.0f);
    glVertex3f(-8.0 , 4.0 , -8.0);
    glColor3f(0.8765f, 0.86471f, 1.0f);
    glVertex3f(8.0  , 4.0 , -8.0);
    glEnd();

    glBegin(GL_POLYGON); //laft wall
    glColor3f(0.1765f, 0.16471f, 0.7725f);
    glVertex3f(-8.0 , 4.0  , 8.0);
    glColor3f(0.1765f, 0.16471f, 0.7725f);
    glVertex3f(-8.0 , -2.0 , 8.0);
    glColor3f(0.0555f, 0.04371f, 0.4625f);
    glVertex3f(-8.0 , -2.0 , -8.0);
    glColor3f(0.1765f, 0.16471f, 0.7725f);
    glVertex3f(-8.0 , 4.0  , -8.0);
    glEnd();

    glPopMatrix();

}

void lamp(){
    glPushMatrix();
    glTranslatef(-1.5, 3.4, 0.0);
    glRotatef(265, 1.0, 0.0, 0.0);
    glColor4f(1.0,1.0,1.0, 1.0);
    glutSolidCone(0.3, 0.2, 50, 50);
    glColor4f(0.0,0.0,0.0, 1.0);
    glColor4f(1.0,1.0,1.0, 1.0);
    glutWireCone(0.36, 0.26, 15, 15);

    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    

    glPopMatrix();
}
