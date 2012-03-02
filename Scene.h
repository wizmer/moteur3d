#include "WorldObject.h"

class Scene{
 private:
  static Scene* m_manager;

 public:
  static Scene* CreateScene();

  void AddWorldObject(WorldObject* obj);
  vector<WorldObject*> m_wobj;
};
