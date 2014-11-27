#include "CSCIx229.h"
//#include "myShapes.c"


/*Draw a tree */ 
void tree(double x, double y, double z, double r, double l, double th, unsigned int tex){

	glBindTexture(GL_TEXTURE_2D, tex);

	//Adjust tree, rotate, translate
	glPushMatrix();
	glTranslated(x,y,z);
	glRotated(th,0,1,0);
	glColor3f(.4, .9, .7);
	//Draw tree poofs	
  glDisable(GL_TEXTURE_2D); //disable for trees and things
  		
	glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1,1);
	sphere(+1, l + r/5, +1, r/5);
	sphere(+1 + r/5, l, +1, r/5);
	sphere(+1 -r/5, l, +1, r/5);
	sphere(+1, l, +1 - r/7, r/7);
	sphere(+1, l, +1 + r/7, r/7);
	//Draw tree trunk
  glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

	cube(+1, 0, +1, 0.5*(r/5), l + r/6, -.5*(r/5),      th,    .9, .4, .1, .9, .4, .1, 1, 0.5, 0.4, .8, .4, .5, tex);
    //Undo transofrmations
    glPopMatrix();
}

