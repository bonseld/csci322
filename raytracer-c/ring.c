#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "raytrace.h"
#include "vectors.h"

int main(int argc, char * argv[] ) {
  world theworld = worldMalloc();
  double angle1, angle2;
  double radius1, radius2;
  double s,c,s1,s2,c1,c2,w,h,x,y,z,pct,r,g,b;
  const double pi = 3.14159265;
  int nspheres = 128;
  int nloops = 3;
  int nspirals = 2;
  double floops = (double)nloops + 1.0/(double)nspirals;
  int i;
  sphere mySphere;

  // tilt ring by pi/6:
  s = sin(pi/6.0);
  c = cos(pi/6.0); 
 
  // build world:
  assign(theworld->backgroundColor, 0.5, 0.75, 1.0);
  assign(theworld->eye, 0.0, 0.0, 150.0);
  assign(theworld->light, 1.0, 1.0, 1.0);
  normalize(theworld->light);
  
  // make ring:
  radius1 = 500.0;
  radius2 = 100.0;
  for (i = 0; i < nspheres; i++) {
    angle1 = 2.0*pi*(double)nspirals*(double)i/(double)nspheres;
    angle2 = floops * angle1;
    s1 = sin(angle1);
    s2 = sin(angle2);
    c1 = cos(angle1);
    c2 = cos(angle2);
    w = radius1 + c2*radius2;
    h = s2*radius2;
    x = c1*w;
    y = h;
    z = s1*w;
    pct = 6.0*(double)i/(double)nspheres;
    if ((0.0 <= pct) && (pct < 1.0)) {
      r =  1.0; g = pct; b = 0.0;
    } else if ((1.0 <= pct && pct < 2.0)) {
      pct = pct - 1.0;
      r =  1.0-pct; g = 1.0; b = 0.0;
    } else if ((2.0 <= pct) && (pct < 3.0)) {
      pct = pct - 2.0;
      r =  0.0; g = 1.0; b = pct;
    } else if ((3.0 <= pct) && (pct < 4.0)) {
      pct = pct - 3.0;
      r =  0.0; g = 1.0-pct; b = 1.0;
    } else if ((4.0 <= pct) && (pct < 5.0)) {
      pct = pct - 4.0;
      r =  pct; g = 0.0; b = 1.0;
    } else {
      pct = pct - 5.0;
      r =  1.0; g = 0.0; b = 1.0-pct;
    }
    
    mySphere = makeSphere(x, c*y-s*z, s*y+c*z - 2000.0,
			  60.0,
			  r, g, b);
    addSphere(theworld, mySphere);
  }

  tracer("images/ring.ppm", 6, theworld);
  return 0;
}
