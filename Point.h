#ifndef POINT_H
#define POINT_H

#include <iostream> 
//#include "global.h"

class Point{
 public:
  double x,y,z;
 Point(double fx,double fy,double fz):x(fx),y(fy),z(fz){}
  Point(Point* M,double rot[3][3],double trans[3] = NULL);
  void ApplyMatrices(double Rot[3][3], double Trans[3] = NULL);
};

#endif
