#ifndef PROJPOLYGONE_H
#define PROJPOLYGONE_H

#include "Polygone.h"
#include "ProjPoint.h"
#include "Camera.h"
#include "TMarker.h"

class ProjPolygone{
 private:
  Polygone* m_pol;
  vector<ProjPoint*> *m_projpoint;
 public:
  ProjPolygone(Polygone* fPol);
  void Dump();
  void Plot();
  void Update(Camera* cam);
};

#endif
