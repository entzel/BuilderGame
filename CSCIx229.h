#ifndef CSCIx229
#define CSCIx229

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))

#ifdef __cplusplus
extern "C" {
#endif
void Vertex(double th,double ph);
void sphere(double x,double y,double z,double r);
void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th, double frontr, double frontg, double frontb,
				 double backr, double backg, double backb, double rightr, double rightg,
				 double rightb, double leftr, double leftg, double leftb,  unsigned int housetex);
void House(int x, int y, int z, int th, int width, int height, int depth, int roofheight,
double frontr, double frontg, double frontb, double backr, double backg, double backb, 
double rightr, double rightg, double rightb, double leftr, double leftg, double leftb,  
	unsigned int housetex, unsigned int rooftex);
void roof(int x, int y, int z, int th, int width, int height, int depth, int roofheight, unsigned int rooftex);
void tree(double x, double y, double z, double r, double l, double th, unsigned int tex);
void Print(const char* format , ...);
void Fatal(const char* format , ...);
unsigned int LoadTexBMP(const char* file);
void Project(double fov,double asp,double dim);
void ErrCheck(const char* where);
int  LoadOBJ(const char* file);


#ifdef __cplusplus
}
#endif

#endif
