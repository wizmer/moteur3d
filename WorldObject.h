#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include "Transformation.h"
#include "GeomObject.h"
#include "Polygone.h"
#include "Point2D.h"

#include <vector>

class WorldObject{
 public:
  std::vector<Polygone*> m_pol;
  WorldObject(GeomObject* obj,double **rot = NULL, double *trans = NULL, double scale = 1);
  WorldObject(GeomObject* obj,double Tx,double Ty,double Tz);
  ~WorldObject();

  std::vector<std::vector<Point2D*>*>* ProjectWorldObject(Camera* cam);

 private:
  Transformation* m_trans;
  GeomObject* m_obj;
  
};

#endif
