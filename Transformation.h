#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "Matrix.h"

class Transformation{
 public:
  Matrix* m_rot;
  Matrix* m_trans;
  double m_scale;
  Transformation(double **fRot = NULL,double *fTranslation = NULL, double fScale = 1);
  Transformation(double Rx,double Ry, double Rz,double Tx,double Ty,double Tz,double scale);
  void Apply(double &x,double &y,double &z);
  void SetTranslation(double Tx,double Ty,double Tz);
};

#endif
