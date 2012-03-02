#ifndef PROJPOINT_H
#define PROJPOINT_H

#include "Point.h"
#include "Camera.h"

#include <math.h>

class ProjPoint{
 public:
  double Phi,Tau;
  Point* m_point;
  ProjPoint(Point* fPoint);
  void Update(Camera* cam);
};

#endif
