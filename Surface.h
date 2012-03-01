#ifndef SURFACE_H
#define SURFACE_H

#include "Point.h"
#include <vector.h>

class Surface{
 public:
  vector <Point*> M;
  Point* Barycentre;
 private:
  int Couleur;

 public:
  Surface(double,double,double,double,double,double,double,double,double);
  Surface(Surface* surf,double rot[3][3],double trans[3] = NULL);
  void UpdateBarycentre();
  void ApplyMatrices(double Rot[3][3], double Trans[3] = NULL);
};

#endif
