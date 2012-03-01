#include "Object.h"

/* double I3 = {{1,0,0}, */
/* 	       {0,1,0}, */
/* 	       {0,0,1}}; */

class WorldObject{
 public:
  vector<Surface*> m_surf;
  WorldObject(Object* obj,double **rot = NULL, double *trans = NULL);
 private:
  double Rot[3][3];
  double Trans[3];
  Object* m_obj;
};
