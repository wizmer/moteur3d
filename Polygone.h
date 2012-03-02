#ifndef POLYGONE_H
#define POLYGONE_H

#include "Camera.h"
#include "Point.h"
#include "ProjPoint.h"

#include <vector>


class Polygone{
 public:
  std::vector <Point*> M;
  Point* Barycentre;
 private:
  int Couleur;

 public:
  Polygone(double,double,double,double,double,double,double,double,double);
  Polygone(Polygone* surf);
  void UpdateBarycentre();
  void ApplyMatrices(double Rot[3][3], double Trans[3] = NULL);
  std::vector<ProjPoint*>* CreateProjection();
  ~Polygone();
};

#endif
