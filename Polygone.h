#ifndef POLYGONE_H
#define POLYGONE_H

#include "Point.h"
#include <vector>

using namespace std;
class Polygone{
 public:
  vector <Point*> M;
  Point* Barycentre;
 private:
  int Couleur;

 public:
  Polygone(double,double,double,double,double,double,double,double,double);
  Polygone(Polygone* surf,double rot[3][3],double trans[3] = NULL);
  void UpdateBarycentre();
  void ApplyMatrices(double Rot[3][3], double Trans[3] = NULL);
};

#endif
