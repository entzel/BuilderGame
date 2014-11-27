/*
S- Zoom in
s- Zoom out
l/L -toggle sun
+/- increase/decreas field of view angle
e/E decrease/increase the sun's emission intensity
</> move light
 l          Toggles lighting
 */

#include <stdbool.h>
#include "CSCIx229.h"
double time;
int ntex=0;       //  Cube faces
double asp = 1.0;	//  Aspsect ratio
int th=0;         //  Azimuth of view angle`
int ph=10;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double dim = 30.0;
int zh = 0;


int light = 20;
//light stuffs

int emission  =   50;  // Emission intensity (%)
int ambient   =  90;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   5;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shinyvec[1];    // Shininess (value)
float ylight  =   20;  // Elevation of light
unsigned int texture[6]; // Texture names
//Mouse stuff
bool mouseLeftDown = false;
int mousex, mousey;
int winheight = 600;
int winwidth = 600;
float white2[] = {1,1,1,1}; //object emmision colors
float black2[] = {0,0,0,1};


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
    //sphere(Position[0],Position[1],Position[2], 3.5);
	glMaterialfv(GL_FRONT,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT,GL_SPECULAR, white2);
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
 
 void drawToolBar(){

  glDisable(GL_TEXTURE_2D);
   //  Save transform attributes (Matrix Mode and Enabled Modes)
   glPushAttrib(GL_TRANSFORM_BIT|GL_ENABLE_BIT);
   //  Save projection matrix and set unit transform
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   glOrtho(-asp,+asp,-1,1,-1,1);
   //  Save model view matrix and set to indentity
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glDisable(GL_LIGHTING);
   
   //house
    glColor3f(0,.8,.99);
   glBegin(GL_QUADS);
   glVertex2f(-.72,-.82);
   glVertex2f(-.72,-.93);
   glVertex2f(-.57,-0.93);
   glVertex2f(-.57,-0.82);
   glEnd();
   glColor3f(.9, .45, 0);
   glBegin(GL_POLYGON);
   glVertex2f(-.73,-.82);
   glVertex2f(-.56,-0.82);
   glVertex2f(-.645, -.765);
   glEnd();
   //underlay
   glColor3f(1,1,1);
   glBegin(GL_QUADS);
   glVertex2f(-.8,-.75);
   glVertex2f(-.8,-.95);
   glVertex2f(-.5,-0.95);
   glVertex2f(-.5,-0.75);
   glEnd();
   
   
   //background bar
   glColor3f(0.8, 0.8, 0.0);
   glBegin(GL_QUADS);
   glVertex2f(-2,-1);
   glVertex2f(+2,-1);
   glVertex2f(+2,-0.7);
   glVertex2f(-2,-0.7);
   glEnd();
	glColor3f(0, 0,0);
   glBegin(GL_QUADS);
   glVertex2f(-2,-.695);
   glVertex2f(+2,-.695);
   glVertex2f(+2,-0.7);
   glVertex2f(-2,-0.7);
   glEnd();
   //  Reset model view matrix
   glPopMatrix();
   //  Reset projection matrix
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   //  Pop transform attributes (Matrix Mode and Enabled Modes)
   glPopAttrib();
 
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
   glTexCoord2f(150,0); glVertex3f(+1,0,-1);
   glTexCoord2f(150,200);glVertex3f(+1,0,+1);
   glTexCoord2f(0,150);glVertex3f(-1,0,+1); 
   glNormal3f(0, -1, 0);
	
	glEnd();
}

void drawHouse(GLenum mode, int x, int y, int z, int th, int width, int height, int depth, int roofheight,
 double frontr, double frontg, double frontb, double backr, double backg, double backb, 
 double rightr, double rightg, double rightb, double leftr, double leftg, double leftb, unsigned int housetex, unsigned int rooftex )
{

	GLuint house = floor(time);
	if (mode == GL_SELECT)
		glLoadName(house);
	House(x, y, z, th, width, height, depth, roofheight,
	frontr, frontg, frontb, backr, backg, backb, 
	rightr, rightg, rightb, leftr, leftg, leftb, housetex, rooftex);
	if (mode == GL_SELECT)
            glPopName ();
}

void init(void){
//Erase the window and the depth buffer
	glClearColor(0.0f, 0.88f, 1.0f, 1.0f);
	//Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	glDepthRange(0.0, 1.0);  /* The default z mapping */
}

/* OpenGL calls this routine to display the scene
*/ 
void display(){

	//Eye position
	double Ex = -2*dim*Sin(th)*Cos(ph);
	double Ey = +2*dim        *Sin(ph);
	double Ez = +2*dim*Cos(th)*Cos(ph);
	
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
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

	shininess = 10;
	float green[]   = {0.0, 0.01*diffuse, 0.0,1.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white2);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black2);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,green);
	tree(16.5, 0, 0,    5, 4, 1, texture[3]);
	tree(19, 0, 2,    6, 5, 25, texture[3]);
	tree(19, 0, 0.5,    3, 3, 35, texture[3]);
	tree(-20, 0, -10,   8, 3, 50, texture[3]);
	tree(-3, 0, 5,   6, 5, 1, texture[3]);
	tree(-6, 0, 6,  8 , 3.5, 30, texture[3]);
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,texture[2]);
    //Draw flat plane
    drawflat(0,0,0, 100, 100, 0, .95, 0);   
	
	drawToolBar();
    //  Display parameters
    glWindowPos2i(5,5);
   // Print("Angle=%d,%d  Dim=%.1f Light=%.1f",th,ph,dim);
    //Print("Angle=%d,%d  Dim=%.1f Light=%s",th,ph,dim,light?"On":"Off");
	
	drawHouse(GL_RENDER, -7,0, 0,    0,     3, 5, 3.4,   2,   .85,.8,0,  .9,.9,0, .7,.7,0,   0.9,.8,0, texture[1], texture[5]);
	
	//Render the scene and make it visible
    //ErrCheck("display");
    glFlush();
    glutSwapBuffers();
}

void processHits(GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLuint names, *ptr;

   printf("hits = %d\n", hits);
   ptr = (GLuint *) buffer;
   for (i = 0; i < hits; i++) {  /* for each hit  */
      names = *ptr;
      printf(" number of names for hit = %d\n", names); ptr++;
      printf("  z1 is %g;", (float) *ptr/0x7fffffff); ptr++;
      printf(" z2 is %g\n", (float) *ptr/0x7fffffff); ptr++;
      printf("   the name is ");
      for (j = 0; j < names; j++) {  /* for each name */
         printf("%d ", *ptr); ptr++;
      }
      printf("\n");
   }
}



#define BUFSIZE 512
void picker(int button, int state, int x, int y){
	x = mousex;
	y = mousey;
	GLuint selectBuf[BUFSIZE];
	GLint hits;
	GLint viewport[4];
	bool newobj = false;
	
	if(button == GLUT_LEFT_BUTTON){
		if(state == GLUT_DOWN){	
		glGetIntegerv(GL_VIEWPORT, viewport);
		
		glSelectBuffer(BUFSIZE, selectBuf); //Array to be used for recording object hits
		(void) glRenderMode(GL_SELECT); 	//Enter Selection Mode
		
		//Initialize the name stack
		glInitNames();  
		glPushName(0);
		//Save current transformation state.
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		
		// Create a 5x5 picking region near cursor location
		gluPickMatrix((GLdouble) mousex, (GLdouble) (viewport[3] - mousey), 5.0,
		5.0, viewport);
		drawHouse(GL_SELECT, -7,0, 0,    0,     3, 5, 3.4,   2,   .85,.8,0,  .9,.9,0, .7,.7,0,   0.9,.8,0, texture[1], texture[5]);
		
		glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
		glFlush ();
		
		hits = glRenderMode (GL_RENDER);
		processHits (hits, selectBuf);
		glutPostRedisplay();
	}
	
	if((state == GLUT_UP)&&(newobj == true)){
		glutWarpPointer(winwidth/2, winheight/2);
	}	
	}
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle(){
   //Elapsed time in seconds
   time = glutGet(GLUT_ELAPSED_TIME)/1000.0;
  
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
	else if ((key == GLUT_KEY_UP)&& (ph < 90))
		ph += 2;
    //Down arrow key - decrease elevation by 5 degrees
    else if ((key == GLUT_KEY_DOWN) &&(ph > 10))
		ph -= 2;
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
   //save window width and height
   winwidth = width;
   winheight = height;
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
	init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   
   //process mouse callbacks
	glutMouseFunc(picker);
	//glutMotionFunc(processMouseActiveMotion);
	///glutPassiveMotionFunc(processMousePassiveMotion);
//	glutEntryFunc(processMouseEntry);
   
   
   //  Load textures
   texture[0] = LoadTexBMP("crate.bmp");
   texture[1] = LoadTexBMP("StoneWall.bmp");
   texture[2] = LoadTexBMP("grass.bmp");
   texture[3] = LoadTexBMP("bark.bmp");
   texture[4] = LoadTexBMP("roof.bmp");
   texture[5] = LoadTexBMP("brick.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
