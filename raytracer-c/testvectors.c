#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "CuTest.h"
#include "vectors.h"
#define DELTA 1.0e-6

void testVectorMalloc(CuTest* tc) {
  vector v = vectorMalloc();
  CuAssertTrue(tc, 1);
  CuAssertDblEquals(tc, 0.0, v.x, DELTA);
  CuAssertDblEquals(tc, 0.0, v.y, DELTA);
  CuAssertDblEquals(tc, 0.0, v.z, DELTA);
}

void testAssign(CuTest* tc) {
  vector v = vectorMalloc();
  assign(&v, 1.0, 2.0, 3.0);
  CuAssertDblEquals(tc, 1.0, v.x, DELTA);
  CuAssertDblEquals(tc, 2.0, v.y, DELTA);
  CuAssertDblEquals(tc, 3.0, v.z, DELTA);
  vectorFree(v);
}

void testCopy(CuTest* tc) {
  vector v1 = vectorMalloc();
  vector v2 = vectorMalloc();
  assign(&v1, 23.23, -99.32, 12334.23);
  copy(&v2, v1);
  CuAssertDblEquals(tc, v1.x, v2.x, DELTA);
  CuAssertDblEquals(tc, v1.y, v2.y, DELTA);
  CuAssertDblEquals(tc, v1.z, v2.z, DELTA);
  vectorFree(v1);
  vectorFree(v2);
}

void testAdd(CuTest* tc) {
  vector v1,v2,v3;
  v1 = vectorMalloc(); v2 = vectorMalloc(); v3 = vectorMalloc();
  assign(&v1, 1.0, 2.0, 3.0);
  assign(&v2, 10.0, 20.0, 30.0);
  add(&v3, v1, v2);
  CuAssertDblEquals(tc, 11.0, v3.x, DELTA);
  CuAssertDblEquals(tc, 22.0, v3.y, DELTA);
  CuAssertDblEquals(tc, 33.0, v3.z, DELTA);
  vectorFree(v1);  vectorFree(v2);  vectorFree(v3);
}

void testDot(CuTest* tc) {
  vector v = vectorMalloc();
  double d;
  assign(&v, 1.0, 2.0, 3.0);
  d = dot(v, v);
  CuAssertDblEquals(tc, 14.0, d, DELTA);
  vectorFree(v);
}

void testMag(CuTest* tc) {
  vector v = vectorMalloc();
  assign(&v, 0.0, 3.0, 4.0);
  CuAssertDblEquals(tc, 5.0, mag(v), DELTA);
  assign(&v, 1.0, 1.0, 1.0);
  CuAssertDblEquals(tc, sqrt(3.0), mag(v), DELTA);
  vectorFree(v);
}

void testNormalize(CuTest* tc) {
  vector v = vectorMalloc();
  assign(&v, 1.0, 1.0, 1.0);
  normalize(&v);
  CuAssertDblEquals(tc, 1.0, mag(v), DELTA);
  assign(&v, 123.0, -321.0, 1.23);
  normalize(&v);
  CuAssertDblEquals(tc, 1.0, mag(v), DELTA);
  vectorFree(v);
}

void testDistance(CuTest* tc) {
  vector v1 = vectorMalloc();
  vector v2 = vectorMalloc();
  assign(&v2, 1.0, 1.0, 1.0);
  CuAssertDblEquals(tc, sqrt(3.0), distance(v1, v2), DELTA);
  vectorFree(v1);
  vectorFree(v2);
}

CuSuite* VectorsSuite(void) {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, testVectorMalloc);
  SUITE_ADD_TEST(suite, testAssign);
  SUITE_ADD_TEST(suite, testCopy);
  SUITE_ADD_TEST(suite, testAdd);
  SUITE_ADD_TEST(suite, testDot);
  SUITE_ADD_TEST(suite, testMag);
  SUITE_ADD_TEST(suite, testNormalize);
  SUITE_ADD_TEST(suite, testDistance);
  return suite;
}

  



