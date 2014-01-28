#include <stdio.h>   /* printf */
#include <stdlib.h>  /* malloc */
#include <math.h>    /* sqrt   */
#include "vectors.h"
/*
A simple package to support vector 
operations needed for a ray tracer.

Geoffrey Matthews
2014
*/
// Added a comment
vector vectorMalloc(void) {
  struct vector v;//malloc(sizeof(struct vector));
  //if (v == NULL) {
 //   printf("ERROR in vectorMalloc.\n");
  //  exit(-1);
 // }
  v.x = 0.0; v.y = 0.0; v.z = 0.0;
  return v;
}

void vectorFree(vector v) {
  //free(v);

}

void assign(vector *target, /* out */
	    double x, double y, double z /* in */) {
  *target = (struct vector){x,y,z};
}

void copy(vector *target, /* out */
	  vector source  /* in */) {
  target->x = source.x; target->y = source.y; target->z = source.z;
}

void add(vector *target, /* out */
	 vector source1, /* in */
	 vector source2  /* in */) {
  target->x = source1.x + source2.x;
  target->y = source1.y + source2.y;
  target->z = source1.z + source2.z;
}

void subtract(vector *target, /* out */
	      vector source1, /* in */
	      vector source2  /* in */) {
  target->x = source1.x - source2.x;
  target->y = source1.y - source2.y;
  target->z = source1.z - source2.z;
}

void multiply(vector *target, /* inout */
	      double s       /* in */) {
  target->x *= s;
  target->y *= s;
  target->z *= s;
}

double dot(vector v1, vector v2) {
/* return the dot product of v1 and v2 */
  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

double mag(vector v) {
/* return the magnitude of v */
  return sqrt(dot(v, v));
}

void normalize(vector *v) {
/* set v to unit length
   does not change zero length vectors */
  double m = mag(*v);
  if (m > 0.0) {
    multiply(v, 1.0/m);
  }
}

double distance(vector p1, vector p2) {
/* return the distance between points p1 and p2 */
  vector v = vectorMalloc();
  subtract(&v, p1, p2);
  return mag(v);
}

void vectorPrint(vector *v) {
/* readable print for v */
  printf("vector(%0.2f, %0.2f, %0.2f)", v->x, v->y, v->z);
}

void vectorIntegerPrintf(FILE *file, vector color) {
/* output just the rounded values of the vector to the file */
  fprintf(file, "%d %d %d\n", (int)color.x, (int)color.y, (int)color.z);
}


