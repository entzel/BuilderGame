
//draw a cube
#include "CSCIx229.h"
/*
Draw a cube at x, y, z
dimensions width, height, depth
rotated th about the y axis
*/
float white[] = {1,1,1,1}; //object emmision colors
float black[] = {0,0,0,1};
void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th, double frontr, double frontg, double frontb,
				 double backr, double backg, double backb, double rightr, double rightg,
				 double rightb, double leftr, double leftg, double leftb) 
{      
	//et specular color to white
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);

    // Save transformation
    glPushMatrix();
    //Offset
    glTranslated(x,y,z);
    glRotated(th,0,1,0);
    glScaled(dx,dy,dz);
 
	//Front
    glColor3f(frontr,frontg,frontb);
    glBegin(GL_QUADS);
    //Enable texture
	glTexCoord2f(0,0); glVertex3f(-1,0, 1);
	glTexCoord2f(1,0); glVertex3f(+1,0, 1);
	glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
	glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
	glNormal3f(0, 0, 1);
	glEnd();
    //Back
    glColor3f(backr,backg,backb);
    glBegin(GL_QUADS);
    //Enable texture
	glTexCoord2f(0,0); glVertex3f(+1,0,-1);
	glTexCoord2f(1,0);  glVertex3f(-1,0,-1);
	glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
	glTexCoord2f(0,1);glVertex3f(+1,+1,-1);
	glNormal3f(0, 0, -1);
	glEnd();
    //Right
    glColor3f(rightr,rightg,rightb);
    glBegin(GL_QUADS);
    //Enable texture
	glTexCoord2f(0,0); glVertex3f(+1,0,+1);
	glTexCoord2f(1,0); glVertex3f(+1,0,-1);
	glTexCoord2f(1,1);glVertex3f(+1,+1,-1);
	glTexCoord2f(0,1);	glVertex3f(+1,+1,+1);
	glNormal3f(+1, 0, 0);
	glEnd();
    //Left
    glColor3f(leftr, leftg, leftb);
    glBegin(GL_QUADS);
    //Enable texture
	glTexCoord2f(0,0); glVertex3f(-1,0,-1);
	glTexCoord2f(1,0); glVertex3f(-1,0,+1);
	glTexCoord2f(1,1);	glVertex3f(-1,+1,+1);
	glTexCoord2f(0,1);glVertex3f(-1,+1,-1);
	glNormal3f(-1, 0, 0);
	glEnd();
    //Top
    glColor3f(1.4,.8,.8);
    glBegin(GL_QUADS);
    //Enable texture
	glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
	glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
	glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
	glTexCoord2f(0,1);glVertex3f(-1,+1,-1);
	glNormal3f(0, +1, 0);
	glEnd();
    //Bottom
	glColor3f(0.0f,.67, 0);
	glBegin(GL_QUADS);
	//Enable texture
	glTexCoord2f(0,0); glVertex3f(-1,0,-1);
	glTexCoord2f(1,0); glVertex3f(+1,0,-1);
	glTexCoord2f(1,1);glVertex3f(+1,0,+1);
	glTexCoord2f(0,1);glVertex3f(-1,0,+1);
	glNormal3f(0, -1, 0);
	glEnd();
	
	//Undo transofrmations
    glPopMatrix();
}


/* Draw a house
 */
 static void House(int x, int y, int z, int th, int width, int height, int depth, int roofheight,
 double frontr, double frontg, double frontb, double backr, double backg, double backb, 
 double rightr, double rightg, double rightb, double leftr, double leftg, double leftb ){
	
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
	glPushMatrix();
	glScaled(width,height,depth);
	cube(x,y,z,  1, 1, 1, th, frontr, frontg, frontb, backr, backg, backb, rightr, rightg,
	rightb, leftr, leftg, leftb);
	roof(x, y, z, th, width, height, depth, roofheight);
 }
 //Draw the sun