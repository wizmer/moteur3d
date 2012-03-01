#include "WorldManager.h"

WorldManager* WorldManager::m_manager = 0;

WorldManager* WorldManager::CreateWorldManager(){
  if(m_manager) return m_manager;
  else {
    m_manager = new WorldManager();
    return m_manager;
  }
}

void WorldManager::AddWorldObject(WorldObject* obj){
  m_wobj.push_back(obj);
}
