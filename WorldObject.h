#include "GeomObject.h"

/* double I3 = {{1,0,0}, */
/* 	       {0,1,0}, */
/* 	       {0,0,1}}; */

class WorldObject{
 public:
  vector<Polygone*> m_pol;
  WorldObject(GeomObject* obj,double **rot = NULL, double *trans = NULL);
 private:
  double Rot[3][3];
  double Trans[3];
  GeomObject* m_obj;
};


