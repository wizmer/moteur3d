#ifndef SCENE2D_H
#define SCENE2D_H

#include "WorldObject.h"
#include "Point2D.h"
#include "X11Display.h"

#include <vector>

class Scene2D{
 private:
  static Scene2D* m_manager;
  std::vector<Point2D*> m_point;

 public:
  static Scene2D* GetScene2D();

  void ProjectWorldObject(WorldObject* obj, Camera* cam);
  };

#endif
