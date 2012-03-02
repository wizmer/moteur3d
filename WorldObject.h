#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H
#include "GeomObject.h"
#include "Transformation.h"

/* double I3 = {{1,0,0}, */
/* 	       {0,1,0}, */
/* 	       {0,0,1}}; */

class WorldObject{
 public:
  vector<Polygone*> m_pol;
  WorldObject(GeomObject* obj,double **rot = NULL, double *trans = NULL, double scale = 1);
  ~WorldObject();
 private:
  Transformation* m_trans;
  GeomObject* m_obj;
  
};

#endif
