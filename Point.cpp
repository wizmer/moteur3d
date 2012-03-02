#include "Point.h"

void Point::ApplyMatrices(double Rot[3][3],double Trans[3]){
  double xtmp = x, ytmp = y, ztmp = z;
  x = Rot[0][0]*xtmp + Rot[0][1]*ytmp + Rot[0][2]*ztmp;
  y = Rot[1][0]*xtmp + Rot[1][1]*ytmp + Rot[1][2]*ztmp;
  z = Rot[2][0]*xtmp + Rot[2][1]*ytmp + Rot[2][2]*ztmp;
  if(Trans){
    x += Trans[0];
    y += Trans[1];
    z += Trans[2];
  }
}

 Point::Point(Point* M):x((*M).x),y((*M).y),z((*M).z){
   //  ApplyMatrices(rot,trans);
}

Point::~Point()
{
  //In prevision of dynamical allocations.
}
