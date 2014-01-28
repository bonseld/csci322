#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "CuTest.h"
#include "raytrace.h"
#define DELTA 1.0e-6

void testRayMalloc(CuTest* tc) {
  ray r = rayMalloc();
  CuAssertTrue(tc, 1);
  CuAssertDblEquals(tc, 0.0, r.position.x, DELTA);
  CuAssertDblEquals(tc, 0.0, r.direction.x, DELTA);
  rayFree(r);
}

void testMakeRay(CuTest* tc) {
  ray r = makeRay(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);
  CuAssertDblEquals(tc, 1.0, r.position.x, DELTA);
  CuAssertDblEquals(tc, 4.0, r.direction.x, DELTA);
  rayFree(r);
}  

void testMakeSphere(CuTest* tc) {
  sphere s = makeSphere(1.0, 2.0, 3.0, 4.0, 0.5, 0.5, 0.5);
  CuAssertDblEquals(tc, s.center.x, 1.0, DELTA);
  CuAssertDblEquals(tc, s.radius, 4.0, DELTA);
  sphereFree(s);
}

void testWorldMalloc(CuTest* tc) {
  world w = worldMalloc();
  CuAssertTrue(tc, 1);
  CuAssertDblEquals(tc, w.eye.z, 200.0, DELTA);
  CuAssertIntEquals(tc, w.length, 0);
  worldFree(w);
}

void testAddSphere(CuTest* tc) {
  world w = worldMalloc();
  sphere s = sphereMalloc();
  addSphere(&w, s);
  CuAssertIntEquals(tc, 1, w.length);
  CuAssertDblEquals(tc, 0.0, w.objects[0].center.x, DELTA);
  addSphere(&w, s);
  CuAssertIntEquals(tc, 2, w.length);
  CuAssertDblEquals(tc, 0.0, w.objects[1].center.x, DELTA);
  sphereFree(s);
  worldFree(w);
}  
  
void testQuadratic(CuTest* tc) {
  int n;
  double s1, s2;
  quadratic(1.0, 0.0, -1.0, &n, &s1, &s2);
  CuAssertIntEquals(tc, 2, n);
  CuAssertDblEquals(tc, -1.0, s1, DELTA);
  CuAssertDblEquals(tc, 1.0, s2, DELTA);
}

void testSphereNormal(CuTest* tc) {
  sphere s = makeSphere(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
  vector pos = vectorMalloc();
  vector norm = vectorMalloc();
  assign(&pos, 1.0, 0.0, 0.0);
  sphereNormal(s, pos, &norm);
  CuAssertDblEquals(tc, norm.x, 1.0, DELTA);
  CuAssertDblEquals(tc, norm.y, 0.0, DELTA);
  CuAssertDblEquals(tc, norm.z, 0.0, DELTA);
  vectorFree(pos);
  vectorFree(norm);
  sphereFree(s);
}

void testIntersect(CuTest* tc) {
  int success;
  sphere s = makeSphere(0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0);
  ray r = makeRay(0.0, 0.0, 2.0, 0.0, 0.0, -1.0);
  vector pos = vectorMalloc();
  intersect(s, r, &success, &pos);
  CuAssertTrue(tc, success);
  CuAssertDblEquals(tc, pos.x, 0.0, DELTA);
  CuAssertDblEquals(tc, pos.y, 0.0, DELTA);
  CuAssertDblEquals(tc, pos.z, 1.0, DELTA);
  sphereFree(s);
  rayFree(r);
  vectorFree(pos);
}

void testFirstHit(CuTest* tc) {
  int success;
  world w = worldMalloc();
  ray r = rayMalloc();
  vector pos = vectorMalloc();
  sphere s1 = makeSphere(0.0, 0.0, -11.0, 1.0, 0.9, 0.9, 0.9);
  sphere s2 = sphereMalloc();
  addSphere(&w, s1);
  assign(&r.position, 0.0, 0.0, 1.0);
  assign(&r.direction, 0.0, 0.0, -1.0);
  firstHit(r, w, &success, &pos, &s2);
  CuAssertTrue(tc, success);
  CuAssertDblEquals(tc, pos.z, -10.0, DELTA);
  CuAssertDblEquals(tc, s2.center.z, s1.center.z, DELTA);
  CuAssertDblEquals(tc, s2.color.x, s1.color.x, DELTA);
  worldFree(w);
  rayFree(r);
  vectorFree(pos);
  sphereFree(s1);
  sphereFree(s2);
}

CuSuite* RaytraceSuite(void) {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, testRayMalloc);
  SUITE_ADD_TEST(suite, testMakeRay);
  SUITE_ADD_TEST(suite, testMakeSphere);
  SUITE_ADD_TEST(suite, testWorldMalloc);
  SUITE_ADD_TEST(suite, testAddSphere);
  SUITE_ADD_TEST(suite, testQuadratic);
  SUITE_ADD_TEST(suite, testSphereNormal);
  SUITE_ADD_TEST(suite, testIntersect);
  SUITE_ADD_TEST(suite, testFirstHit);
  return suite;
}

  



