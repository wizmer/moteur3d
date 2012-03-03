#ifndef SCENE3D_H
#define SCENE3D_H
#include "WorldObject.h"
#include "Camera.h"
#include "Scene2D.h"

class Camera;

class Scene3D{
 private:
  static Scene3D* m_manager;

 public:
  static Scene3D* GetScene3D();

  void Project(Camera* cam);
  void AddWorldObject(WorldObject* obj);
  std::vector<WorldObject*> m_wobj;
};

#endif
