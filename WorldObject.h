#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include "Transformation.h"
#include "GeomObject.h"
#include "Polygone.h"
#include "Point2D.h"

#include <vector>

class WorldObject{
 private:
  GeomObject* m_GeomObj;
  Transformation* m_trans;
  Point3D* m_barycentre;
  double m_MaxRadius;  

 public:
  WorldObject(GeomObject* obj, Transformation* fTrans);
  WorldObject(GeomObject* obj,double Tx,double Ty,double Tz);
  ~WorldObject();

  std::vector<std::vector<Point2D*>*>* ProjectWorldObject(Camera* cam);
  void ComputeBarycentre();
  void ComputeMaxRadius();
  void PrintTransfo();


};

#endif
