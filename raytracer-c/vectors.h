#ifndef VECTORS_H
#define VECTORS_H
/*
A simple package to support vector 
operations needed for a ray tracer.

Geoffrey Matthews
2014
*/
// Changed to stack memory
typedef struct vector{
  double x;
  double y;
  double z;
} vector;

vector vectorMalloc(void);
void vectorFree(vector v);
void assign(vector *target, /* inout */
	    double x, double y, double z /* in */);
void copy(vector *target, vector source);
void add(vector *target,  /* out */
	 vector source1, /* in */
	 vector source2  /* in */);
void subtract(vector *target,  /* out */
	      vector source1, /* in */
	      vector source2  /* in */);
void multiply(vector *target, /* inout */
	      double s       /* in */);
double dot(vector v1, vector v2);
/* return the dot product of v1 and v2 */
double mag(vector v);
/* return the magnitude of v */
void normalize(vector *v /* inout */);
/* set v to unit length
   does not change zero length vectors */
double distance(vector p1, vector p2);
/* return the distance between points p1 and p2 */
void vectorPrint(vector *v);
/* readable print for v */
void vectorIntegerPrintf(FILE *file, vector color);
/* output just the rounded values of the vector to the file */
#endif
