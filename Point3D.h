#ifndef POINT3D_H
#define POINT3D_H

#include "Point2D.h"
#include "Transformation.h"

#include <iostream> 

class Camera;
class Transformation;

class Point3D{
 public:
  double x,y,z;
 Point3D(double fx = 0,double fy = 0,double fz = 0):x(fx),y(fy),z(fz){}
  Point3D(Point3D* M);
  void ApplyMatrices(double Rot[3][3], double Trans[3] = NULL);
  ~Point3D();
  Point2D* GetTauPhi(Transformation* trans,Camera* cam);

 public:
  double Get(int i){
    if(i == 0) return x;
    if(i == 1) return y;
    if(i == 2) return z;
  }
 double GetX(){return x;}
 double GetY(){return y;}
 double GetZ(){return z;}

 void SetXYZ(double fx,double fy,double fz){x = fx; y = fy; z = fz;}
 void SetX(double fx){x = fx;}
 void SetY(double fy){y = fy;}
 void SetZ(double fz){z = fz;}

 void AddXYZ(double fx,double fy,double fz){x += fx; y += fy; z += fz;}
 void AddXYZ(Point3D* p){AddXYZ(p -> x, p -> y, p -> z);}
 void AddX(double fx){ x += fx;}
 void AddY(double fy){ y += fy;}
 void AddZ(double fz){ z += fz;}

 void MultiplyXYZ(double fx,double fy,double fz){x *= fx; y *= fy; z *= fz;}
 double Distance(Point3D* p);
};

#include "Camera.h"

#endif
