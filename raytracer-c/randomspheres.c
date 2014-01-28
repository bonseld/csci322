#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "raytrace.h"
#include "vectors.h"

double frand() { 
  return (float)rand()/(float)RAND_MAX;
}

int main(int argc, char * argv[] ) {
  world theworld = worldMalloc();
  int i;
  int n  = 100;
  for (i = 0; i < n; i++) {
    addSphere(theworld,
	      makeSphere((frand()-0.5)*500.0,
			 (frand()-0.5)*500.0,
			 (frand()-0.5)*500.0 - 1000.0,
			 10.0 + frand()*40.0,
			 frand(),
			 frand(),
			 frand()));
  }
  tracer("images/random.ppm", 6, theworld);
  return 0;
}
