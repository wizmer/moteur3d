#include "Scene2D.h"

#define print(token) cout << #token << " : " << token << endl
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
  X11Display* TheX11Display = X11Display::GetX11Display();
  vector<vector<Point2D*>*> * Vec = obj -> ProjectWorldObject(cam);
  int col = 1;
  if(Vec){
    int Npol = Vec->size();

    for(int i = 0;i<Npol;i++){
      int Npoint = (*Vec)[i] -> size();
      if((*(*Vec)[i])[0] && (*(*Vec)[i])[1] && (*(*Vec)[i])[2]){
	TheX11Display -> Update((*(*Vec)[i])[0] -> phi,(*(*Vec)[i])[0] -> tau,(*(*Vec)[i])[1] -> phi,(*(*Vec)[i])[1] -> tau);
	TheX11Display -> Update((*(*Vec)[i])[0] -> phi,(*(*Vec)[i])[0] -> tau,(*(*Vec)[i])[2] -> phi,(*(*Vec)[i])[2] -> tau);
	TheX11Display -> Update((*(*Vec)[i])[2] -> phi,(*(*Vec)[i])[2] -> tau,(*(*Vec)[i])[1] -> phi,(*(*Vec)[i])[1] -> tau);
      }
    }
  }

  cout << "second part" << endl;
  if(Vec){
    int Npol = Vec->size();
    for(int i = 0;i<Npol;i++){
      int Npoint = (*Vec)[i] -> size();
      for(int j = 0;j<Npoint;j++) if((*(*Vec)[i])[j]) delete (*(*Vec)[i])[j];
      if((*Vec)[i]) delete (*Vec)[i];
    }
    delete Vec;
  }
}

