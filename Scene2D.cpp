#include "Scene2D.h"

using namespace std;

Scene2D* Scene2D::m_manager = 0;

Scene2D* Scene2D::GetScene2D(){
  if(m_manager) return m_manager;
  else {
    m_manager = new Scene2D();
    return m_manager;
  }
}

void Scene2D::ProjectWorldObject(WorldObject* obj, Camera* cam){
  vector<vector<Point2D*>*> * Vec = obj -> ProjectWorldObject(cam);

  TMarker* mark = new TMarker();
  mark->SetMarkerStyle(20);
  
  if(Vec){
    int Npol = Vec->size();
    for(int i = 0;i<Npol;i++){
      int Npoint = (*Vec)[i] -> size();
      for(int j = 0;j<Npoint;j++){
	m_point.push_back((*(*Vec)[i])[j] );
	cout << (*(*Vec)[i])[j] << endl;
	mark->DrawMarker((*(*Vec)[i])[j]->phi,(*(*Vec)[i])[j]->tau);
      }
    }
    delete Vec;
  }
}
