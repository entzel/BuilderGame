/*
S- Zoom in
s- Zoom out
l/L -toggle sun
+/- increase/decreas field of view angle
e/E decrease/increase the sun's emission intensity
</> move light
 l          Toggles lighting
 */


#include "CSCIx229.h"
int ntex=0;       //  Cube faces
double asp = 1.0;	//  Aspsect ratio
int th=0;         //  Azimuth of view angle`
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double dim = 30.0;
int zh = 0;
int inc = 10;
float white[] = {1,1,1,1}; //object emmision colors
float black[] = {0,0,0,1};
int light = 20;
//light stuff

int emission  =   30;  // Emission intensity (%)
int ambient   =  60;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   5;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
float ylight  =   20;  // Elevation of light
unsigned int texture[5]; // Texture names


 /*  Draw vertex in polar coordinates
 */
static void Vertex(double th,double ph)
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
static void sphere(double x,double y,double z,double r)
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

/*
Draw a cube at x, y, z
dimensions width, height, depth
rotated th about the y axis
*/
static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th, double frontr, double frontg, double frontb,
				 double backr, double backg, double backb, double rightr, double rightg,
				 double rightb, double leftr, double leftg, double leftb) 
{      
	//Set specular color to white
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

/*Draw a tree */ 
static void tree(double x, double y, double z, double r, double l, double th){
	shininess = 10;
	float green[]   = {0.0, 0.01*diffuse, 0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,green);
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
	glBindTexture(GL_TEXTURE_2D,texture[3]);
	cube(+1, 0, +1, 0.5*(r/5), l + r/6, -.5*(r/5),      th,    .9, .4, .1, .9, .4, .1, 1, 0.5, 0.4, .8, .4, .5);
    //Undo transofrmations
    glPopMatrix();
}
static void roof(int x, int y, int z, int th, int width, int height, int depth, int roofheight)
{
glBindTexture(GL_TEXTURE_2D,texture[4]);
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
 static void sun(){
	//Translate intensity to color vectors
	 float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
     float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
     float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
     float Emission[]  = {0.0,0.0,0.01*emission,1.0};
	
	//Light position
	float Position[]  = {0, ylight,0, 1.0};
    //Draw it
	glColor3f(1,1,.8);
    sphere(Position[0],Position[1],Position[2], 3.5);
	glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT,GL_SPECULAR, white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
	glEnable(GL_NORMALIZE);
	//Enable lighting
    glEnable(GL_LIGHTING);
	//glColor sets ambient and diffuse color materials
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    //Enable light 0
    glEnable(GL_LIGHT0);
    //Set ambient, diffuse, specular components and position of light 0
    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);	 
 }
 
 //Draw a flat rectangle
 static void drawflat(int x,int y, int z, int width, int depth, 
 float red, float green, float blue)  {
//glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
  // glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   //glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,white);
   glColor3f(red, green, blue);

   glTranslated(x,y,z);
   glScaled(width, 1, depth);
   glRotated(th,0,1,0);
   
   glBegin(GL_QUADS);
   glTexCoord2f(0,0); glVertex3f(-1,0,-1);
   glTexCoord2f(200,0); glVertex3f(+1,0,-1);
   glTexCoord2f(200,200);glVertex3f(+1,0,+1);
   glTexCoord2f(0,200);glVertex3f(-1,0,+1); 
   glNormal3f(0, -1, 0);
	
	glEnd();
}

/* OpenGL calls this routine to display the scene
*/ 
void display(){
	
	//Eye position
	double Ex = -2*dim*Sin(th)*Cos(ph);
	double Ey = +2*dim        *Sin(ph);
	double Ez = +2*dim*Cos(th)*Cos(ph);
	//Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	//Set perspective
	glLoadIdentity();
	gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
		
	//Let there be light
	if(light)
		sun();
	 else{
		glDisable(GL_LIGHTING);
	}
	//Texture stuff
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
//GL_REPLACE
	glBindTexture(GL_TEXTURE_2D,texture[0]);
 	//Draw house loc tilt    dimensions  roofdim  front    back,      right,        left
	House(7, 0, 5,   100,    3,6,2.7,   2,    0,0.5,1,  0,0.5,.8,   0,0.5,0.7,   0,0.6,0.6);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
	House(-7,0, 0,    0,     3, 5, 3.4,   2,   .85,.8,0,  .9,.9,0, .7,.7,0,   0.9,.8,0);
	House(-8,0, 3,    0,     2, 2, 1.7,   3,   0.9,0,0,   .8,.1,0,    .95,2,0,     .6,0,0);
	House(0, 0, 4,  -15,     4, 2.2, 3.2, 2,   .9,.4,0,   1,.6,0,    .8,.6,0,      1, .5, .1);
	House(4, 0,-5,  20,     4, 3, 4,     3.6, 0,.4, .1,  0,.3, .3,  0,.6,0,       0,.6, .1);


	tree(16.5, 0, 0,    5, 4, 1);
	tree(19, 0, 2,    6, 5, 25);
	tree(19, 0, 0.5,    3, 3, 35);
	tree(-20, 0, -10,   8, 3, 50);
	tree(-3, 0, 5,   6, 5, 1);
	tree(-6, 0, 6,  8 , 3.5, 30);
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,texture[2]);
    //Draw flat plane
    drawflat(0,0,0, 60, 60, 0, .9, 0);   

    //  Display parameters
    glWindowPos2i(5,5);
    Print("Angle=%d,%d  Dim=%.1f Light=%.1f",th,ph,dim);
    //Print("Angle=%d,%d  Dim=%.1f Light=%s",th,ph,dim,light?"On":"Off");

	//Render the scene and make it visible
    ErrCheck("display");
    glFlush();
    glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle(){
   //Elapsed time in seconds
   //double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
  
   //Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}
/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{	 
	//Right arrow key - increase angle by 5 degrees
    if (key == GLUT_KEY_RIGHT)
		th += 5;
    //Left arrow key - decrease angle by 5 degrees
	else if (key == GLUT_KEY_LEFT)
		th -= 5;
    //Up arrow key - increase elevation by 5 degrees
	else if (key == GLUT_KEY_UP)
		ph += 5;
    //Down arrow key - decrease elevation by 5 degrees
    else if (key == GLUT_KEY_DOWN)
		ph -= 5;
    //PageUp key - increase dim
    else if (key == GLUT_KEY_PAGE_DOWN)
		dim += 0.1;
    //PageDown key - decrease dim
	else if (key == GLUT_KEY_PAGE_UP && dim>1)
		dim -= 0.1;
    //Keep angles to +/-360 degrees
    th %= 360;
    ph %= 360;
    //Update projection
    Project(45,asp,dim);
    //Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}


 /*  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{  
	//quit with esc
	if (ch == 27)
		exit(0);
	//Cycle texture
    else if (ch == 't' || ch == 'T')
		ntex = (ntex+2)%4-1;
    //Zoom in
	else if(ch == 'S')
		dim++;
	else if(ch =='s')
		dim = dim-1;
	//Reset view angle
	else if (ch == '0')
		th = ph = 0;
    //Emission level
	else if (ch=='e' && emission>0)
		emission -= 5;
	else if (ch=='E' && emission<100)
		emission += 5;
	//Change field of view angle
	else if (ch == '-' && ch>1)
		fov--;
	else if (ch == '+' && ch<179)
		fov++;
	//Shininess level
	else if (ch=='n' && shininess>-1)
		shininess -= 1;
	else if (ch=='N' && shininess<7)
		shininess += 1;
		
    //Translate shininess power to value (-1 => 0)
	shinyvec[0] = shininess<0 ? 0 : pow(2.0,shininess);
    //Reproject
    Project(45,asp,dim);
    //Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(45,asp,dim);
}


int main(int argc, char* argv[]){
	//Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Textures and Lighting");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   texture[0] = LoadTexBMP("crate.bmp");
   texture[1] = LoadTexBMP("StoneWall.bmp");
   texture[2] = LoadTexBMP("grass.bmp");
   texture[3] = LoadTexBMP("bark.bmp");
   texture[4] = LoadTexBMP("roof.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
