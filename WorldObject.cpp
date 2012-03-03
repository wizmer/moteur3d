#include "WorldObject.h"

using namespace std;

WorldObject::WorldObject(GeomObject* obj,double **rot, double *trans, double scale):m_obj(obj){
  m_trans = new Transformation(rot,trans,scale);

  int Npol = m_obj->m_pol.size();
  for(int i = 0;i<Npol;i++){
    m_pol.push_back(new Polygone(m_obj->m_pol[i]));
  }
}

WorldObject::~WorldObject(){
  // In case of dynamical allocations within the constructor.
}

vector<vector<Point2D*>*>* WorldObject::ProjectWorldObject(Camera* cam){
  vector<vector<Point2D*>*> *Vec = new vector<vector<Point2D*>*>;
  int N = m_pol.size();
  for(int i = 0;i<N;i++){
    Vec -> push_back(m_pol[i] -> GetTauPhi(cam));
  }
  return Vec;
}

