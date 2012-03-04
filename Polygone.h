#ifndef POLYGONE_H
#define POLYGONE_H

#include "Camera.h"
#include "Point3D.h"
#include "Point2D.h"
#include "Transformation.h"

#include <vector>
#include <iostream>

class Polygone{
 public:
  std::vector <Point3D*> M;
  Point3D* Barycentre;
 private:
  int Couleur;

 public:
  Polygone(double,double,double,double,double,double,double,double,double);
  Polygone(Polygone* surf);
  void UpdateBarycentre();
  void ApplyMatrices(double Rot[3][3], double Trans[3] = NULL);
  std::vector<Point2D*>* GetTauPhi(Transformation* trans,Camera* cam);
  ~Polygone();
};

#endif
