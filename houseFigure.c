
//draw a cube
#include "CSCIx229.h"
//#include "myShapes.c"
/*
Draw a cube at x, y, z
dimensions width, height, depth
rotated th about the y axis
*/
float white[] = {1,1,1,1}; //object emmision colors
float black[] = {0,0,0,1};
float shinyvec2[1];    // Shininess (value)

 void roof(int x, int y, int z, int th, int width, int height, int depth, int roofheight, unsigned int rooftex)
{
glBindTexture(GL_TEXTURE_2D, rooftex);
	//Adjust the roof
	//glScaled(width,height,depth);
	glTranslated(x,y,z);
	glRotated(0,0,1,0);
	glRotated(th,0,1,0);
	glScaled(1.2, .95,1.2);	

	//front
	glBegin(GL_POLYGON);
	glColor3f(.8, 0.3, 0);
	glNormal3d(0, 2, 2*(roofheight-1)); 
	glTexCoord2f(0,0); glVertex3f(-1, +1, +1);
	glTexCoord2f(1,0); glVertex3f(+1, +1, +1);
	glTexCoord2f(1/2, 1); glVertex3f(0, 1*roofheight, 0);
	glEnd();
	
	//right
	glBegin(GL_POLYGON);
	glColor3f(.9, .4, 0);
	glNormal3d(2*(roofheight-1), 2, 0); 
	glTexCoord2f(0,0); glVertex3f(+1, +1, -1);
	glTexCoord2f(1,0); glVertex3f(+1, +1, +1);
	glTexCoord2f(1/2,1); glVertex3f(0, 1*roofheight, 0);
	glEnd();
	
	//back
	glBegin(GL_POLYGON);
	glColor3f(.9, .3, 0);
	glNormal3d(0, 2, -2*(roofheight-1)); 
	glTexCoord2f(0,0); glVertex3f(+1, +1, -1);
	glTexCoord2f(1,0); glVertex3f(-1, +1, -1);
	glTexCoord2f(1/2, 1); glVertex3f(0, 1*roofheight, 0);
	glEnd();
	
	//left
	glBegin(GL_POLYGON);
	glColor3f(.7, .3, 0);
	glNormal3d(-2*(roofheight-1), 2, 0); 
	glTexCoord2f(0,0); glVertex3f(-1, +1, -1);
	glTexCoord2f(1,0); glVertex3f(-1, +1, +1);
	glTexCoord2f(1/2, 1); glVertex3f(0, 1*roofheight, 0);
	glEnd();
	glPopMatrix();
}


/* Draw a house
 */
void House(int x, int y, int z, int th, int width, int height, int depth, int roofheight,
 double frontr, double frontg, double frontb, double backr, double backg, double backb, 
 double rightr, double rightg, double rightb, double leftr, double leftg, double leftb, unsigned int housetex, unsigned int rooftex ){
	
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec2);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
	glPushMatrix();
	glScaled(width,height,depth);
	//et specular color to white
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec2);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
	cube(x,y,z,  1, 1, 1, th, frontr, frontg, frontb, backr, backg, backb, rightr, rightg,
	rightb, leftr, leftg, leftb, housetex);
	roof(x, y, z, th, width, height, depth, roofheight, rooftex);
 }
 //Draw the sun