#include "CSCIx229.h"



int inc = 10;
 /*  Draw vertex in polar coordinates
 */
void Vertex(double th,double ph)
{
 double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

/*
 *  Draw a sphere (version 2)
 *     at (x,y,z)
 *     radius (r)
 */
 void sphere(double x,double y,double z,double r)
{
   int th,ph;
   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  Latitude bands
   for (ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=2*inc)
      {
	           Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transformations
      glPopMatrix();
}


void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th, double frontr, double frontg, double frontb,
				 double backr, double backg, double backb, double rightr, double rightg,
				 double rightb, double leftr, double leftg, double leftb, unsigned int housetex) 
{      
	glBindTexture(GL_TEXTURE_2D,housetex);

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
