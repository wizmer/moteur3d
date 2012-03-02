#include "WorldObject.h"

class Scene{
 private:
  static Scene* m_manager;

 public:
  static Scene* CreateScene();

  void AddWorldObject(WorldObject* obj);
  std::vector<WorldObject*> m_wobj;
};
