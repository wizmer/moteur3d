#ifndef POINT_H
#define POINT_H

#include "Point2D.h"

#include <iostream> 

class Camera;

class Point3D{
 public:
  double x,y,z;
 Point3D(double fx,double fy,double fz):x(fx),y(fy),z(fz){}
  Point3D(Point3D* M);
  void ApplyMatrices(double Rot[3][3], double Trans[3] = NULL);
  ~Point3D();
  Point2D* Project(Camera* cam);

 public:
 double GetX(){return x;}
 double GetY(){return y;}
 double GetZ(){return z;}

 void SetX(double fx){x = fx;}
 void SetY(double fy){y = fy;}
 void SetZ(double fz){z = fz;}

 void AddX(double fx){ x += fx;}
 void AddY(double fy){ y += fy;}
 void AddZ(double fz){ z += fz;}
};

#include "Camera.h"

#endif
