#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Matrix.h"
#include "Point3D.h"

class Point3D;
class Matrix;

class Transformation{
 public:
  Matrix* m_rot;
  Matrix* m_trans;
  Matrix* m_scale;
  Matrix* m_FinalTransfo;
  Transformation(double Rx = 0,double Ry = 0, double Rz = 0,double Tx = 0,double Ty = 0,double Tz = 0,double Sx = 1,double Sy = 1,double Sz = 1);
  void Apply(double &x,double &y,double &z);
  Point3D* Apply(Point3D* p);
  void SetTranslation(double Tx,double Ty,double Tz);
  void ComputeFinalTransfo();
  void Print();
};

#endif
