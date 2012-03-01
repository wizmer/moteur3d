#include "WorldObject.h"

class WorldManager{
 private:
  static WorldManager* m_manager;

 public:
  static WorldManager* CreateWorldManager();

  void AddWorldObject(WorldObject* obj);
  vector<WorldObject*> m_wobj;
};
