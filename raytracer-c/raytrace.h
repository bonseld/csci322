#ifndef RAYTRACE_H
#define RAYTRACE_H
#include "vectors.h"
/*
Simple raytracer.

Geoffrey Matthews
2014
*/

typedef struct ray {
  vector position;
  vector direction;
} ray;

ray rayMalloc(void);
void rayFree(ray r);
ray makeRay(double x, double y, double z,
	    double u, double v, double w);
// Changed to stack memory
typedef struct sphere {
  vector center;
  double radius;
  vector color;
} sphere;

sphere sphereMalloc(void);
void sphereFree(sphere s);
sphere makeSphere(double x, double y, double z,
		  double radius,
		  double r, double g, double b);
void sphereCopy(sphere *s1, sphere s2);

#define MAXOBJECTS 500

typedef sphere objectArray[MAXOBJECTS];
// Changed to stack memory
typedef struct world {
  vector eye;
  vector light;
  objectArray objects;
  int length;
  vector backgroundColor;
} world;

world worldMalloc(void);
void worldFree(world w);

void addSphere(world *w, /* inout */
	       sphere  s /* in */);
/* add a sphere to the world */

void quadratic(double a, double b, double c, /* in */
	       int* n,  /* out, the number of solutions */
	       double* s1, /* out, smallest solution */
	       double* s2  /* out, other solution */);
  
void sphereNormal(sphere  s,   /* in */
		  vector pos,  /* in */
		  vector *norm  /* out */);
/* find the normal to a sphere s at position pos */
  
void tracer(const char* filename, /* file to write image into */
	    int resolution,       /* in, width and height, in 100 pixels */
	    world theworld          /* in, world to render */);
/* raytrace the scene */
  
void colorAt(double x, double y, /* in */
	     world  world,       /* in */
	     vector *color        /* out */);
/* find the color at x and y in the projection plane */

void sendRay(ray myray,    /* in */
	     world theworld, /* in */
	     vector *color  /* out */);
/* find color of what ray hits in the world */

void lambert(sphere mysphere, /* in */
	     vector pos,     /* in */
	     world  theworld,   /* in */
	     vector *color    /* out */);
/* find color of pos on sphere in world, using lambert shading */

void firstHit(ray myray,      /* in */
	      world theworld,  /* in */
	      int* success,  /* out */
	      vector *pos,    /* out */
	      sphere *mysphere  /* out */);
/* find first hit of ray in world
   success is false if no hit
   sphere and position of closest hit returned otherwise */

void intersect(sphere mysphere, /* in */
	       ray myray,      /* in */
	       int* success,  /* out */
	       vector *pos     /* out */);
/* determine if ray intersects sphere
   success is false if no intersection
   pos is position of intersection otherwise */

#endif
  
