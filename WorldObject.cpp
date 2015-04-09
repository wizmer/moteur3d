#include "WorldObject.h"

#define print(token) std::cout << #token << " : " << token << std::endl

WorldObject::WorldObject(GeomObject* obj, Transformation* fTrans):m_GeomObj(obj),m_trans(fTrans){
  m_barycentre = new Point3D();

  ComputeBarycentre();
  ComputeMaxRadius();
}


WorldObject::WorldObject(GeomObject* obj,double Tx,double Ty,double Tz):m_GeomObj(obj){
  std::cout << "construct WorldObject" << std::endl;
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

std::vector<std::vector<Point2D*>*>* WorldObject::ProjectWorldObject(Camera* cam){
  std::vector<std::vector<Point2D*>*> *Vec = new std::vector< std::vector<Point2D*>*>;
  int N = m_GeomObj -> m_pol.size();
  
  std::vector<Point2D*>** p = new std::vector<Point2D*>*[N * 3];
  int i = 0;
  int chunk = N / 10;
#pragma omp parallel shared(Vec,cam) private(i)
  {
#pragma omp for schedule(guided)
    for(i = 0;i<N;i++){
      p[i] = m_GeomObj -> m_pol[i] -> GetTauPhi(m_trans,cam);
    }
  }

  for(i = 0;i<N;i++)  Vec -> push_back(p[i]);
  delete[] p;
  return Vec;
}

void WorldObject::ComputeBarycentre(){
  std::cout << "ComputeBarycentre" << std::endl;
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
  std::cout << "ComputeMaxRadius" << std::endl;
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
