#include "WorldObject.h"

#define print(token) cout << #token << " : " << token << endl
using namespace std;

WorldObject::WorldObject(GeomObject* obj, Transformation* fTrans):m_GeomObj(obj),m_trans(fTrans){
  m_barycentre = new Point3D();

  ComputeBarycentre();
  ComputeMaxRadius();
}


WorldObject::WorldObject(GeomObject* obj,double Tx,double Ty,double Tz):m_GeomObj(obj){
  cout << "construct WorldObject" << endl;
  m_barycentre = new Point3D();

  m_trans = new Transformation();
  m_trans -> SetTranslation(Tx,Ty,Tz);

  m_trans -> ComputeFinalTransfo();
  

  ComputeBarycentre();
  ComputeMaxRadius();
}

WorldObject::~WorldObject(){
  // In case of dynamical allocations within the constructor.
}

vector<vector<Point2D*>*>* WorldObject::ProjectWorldObject(Camera* cam){
  vector<vector<Point2D*>*> *Vec = new vector<vector<Point2D*>*>;
  int N = m_GeomObj -> m_pol.size();
  for(int i = 0;i<N;i++){
    Vec -> push_back(m_GeomObj -> m_pol[i] -> GetTauPhi(m_trans,cam));
  }
  return Vec;
}

void WorldObject::ComputeBarycentre(){
  cout << "ComputeBarycentre" << endl;
  m_barycentre -> SetXYZ(0,0,0);
  double Ntot = 0;
  int N = m_GeomObj -> m_pol.size();
  for(int i = 0;i<N;i++){
    int Npoint = (m_GeomObj -> m_pol[i] -> M).size();
    for(int j = 0;j<Npoint;j++){
      Point3D* p = m_trans -> Apply((m_GeomObj -> m_pol[i] -> M)[j]);
      m_barycentre -> AddXYZ(p);
      delete p;
      Ntot++;
    }
  }
  m_barycentre -> MultiplyXYZ(1./Ntot,1./Ntot,1./Ntot);
}

void WorldObject::ComputeMaxRadius(){
  cout << "ComputeMaxRadius" << endl;
  m_MaxRadius = 0;
  int N = m_GeomObj -> m_pol.size();
  for(int i = 0;i<N;i++){
    int Npoint = (m_GeomObj -> m_pol[i] -> M).size();
    for(int j = 0;j<Npoint;j++){
      Point3D* p = m_trans -> Apply((m_GeomObj -> m_pol[i] -> M)[j]);
      double dist = m_barycentre -> Distance(p);
      delete p;
      if(dist > m_MaxRadius) m_MaxRadius = dist;
    }
  }
}

void WorldObject::PrintTransfo(){
  m_trans -> Print();
}
