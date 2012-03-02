#include "ProjPolygone.h"

ProjPolygone::ProjPolygone(Polygone* fPol):m_pol(fPol){
  m_projpoint = m_pol->CreateProjection();
}

void ProjPolygone::Update(Camera* cam){
  //  m_pol->Update(cam);
  int N = m_projpoint->size();
  for(int i = 0;i<N;i++){
    (*m_projpoint)[i]->Update(cam);
  }
}

void ProjPolygone::Dump(){
  int N = m_projpoint->size();
  for(int i = 0;i<N;i++){
    cout << "phi : " << (*m_projpoint)[i]->Phi << endl;
    cout << "tau : " << (*m_projpoint)[i]->Tau << endl;
  }
}

void ProjPolygone::Plot(){
  int N = m_projpoint->size();
  TMarker* mark = new TMarker();
  mark->SetMarkerStyle(20);
  for(int i = 0;i<N;i++){
    mark->DrawMarker((*m_projpoint)[i]->Phi,(*m_projpoint)[i]->Tau);
  }
}
