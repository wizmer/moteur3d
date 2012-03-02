#include "Polygone.h"

using namespace std;

Polygone::Polygone(Polygone* surf){
  int Nsurf = surf->M.size();
  for(int i = 0;i<Nsurf;i++){
    M.push_back(new Point(surf->M[i]));
  }
}

Polygone::Polygone(double x1,double y1,double z1,double x2,double y2,double z2,double x3,double y3,double z3){
  M.push_back(new Point(x1,y1,z1));
  M.push_back(new Point(x2,y2,z2));
  M.push_back(new Point(x3,y3,z3));
}

void Polygone::UpdateBarycentre(){
  int N = M.size();
  Barycentre->x = 0;
  Barycentre->y = 0;
  Barycentre->z = 0;
  for(int i = 0;i<N;i++){
    Barycentre->x += M[i]->x / (double)N;
    Barycentre->y += M[i]->x / (double)N;
    Barycentre->z += M[i]->x / (double)N;
  }
}

void Polygone::ApplyMatrices(double Rot[3][3], double Trans[3]){
  int N = M.size();
  for(int i = 0;i<N;i++) M[i]->ApplyMatrices(Rot,Trans);
  UpdateBarycentre();
}

Polygone::~Polygone(){
  //in prevision of dynamical allocations
}

vector<ProjPoint*>* Polygone::CreateProjection(){
  vector<ProjPoint*> *vec = new vector<ProjPoint*>;
  int N = M.size();
  for(int i = 0;i<N;i++){
    ProjPoint* p = new ProjPoint(M[i]);
    vec->push_back(p);
  }
  return vec;
}

