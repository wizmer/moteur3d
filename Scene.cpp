#include "Scene.h"

Scene* Scene::m_manager = 0;

Scene* Scene::CreateScene(){
  if(m_manager) return m_manager;
  else {
    m_manager = new Scene();
    return m_manager;
  }
}

void Scene::AddWorldObject(WorldObject* obj){
  m_wobj.push_back(obj);
}
