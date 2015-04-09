#include "Scene3D.h"


Scene3D* Scene3D::m_manager = 0;

Scene3D* Scene3D::GetScene3D(){
  if(m_manager) return m_manager;
  else {
    m_manager = new Scene3D();
    return m_manager;
  }
  Scene2D::GetScene2D();
}

void Scene3D::AddWorldObject(WorldObject* obj){
  m_wobj.push_back(obj);
}

void Scene3D::Project(Camera* cam){
  Scene2D* TheScene2D = Scene2D::GetScene2D();
  X11Display::GetX11Display() -> Flush();

  int N = m_wobj.size();
  for(int i = 0;i<N;i++){
    // std::cout << "///////////////" << std::endl << endl;
    // m_wobj[i] ->  PrintTransfo();
    TheScene2D -> ProjectWorldObject(m_wobj[i],cam);
  }
  cam-> Print();
}

