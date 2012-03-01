#ifndef GEOMOBJECT_H
#define GEOMOBJECT_H

#include "Polygone.h"
#include <fstream>
//#include "TH3F.h"
using namespace std;

class GeomObject{
 public:
  GeomObject(const char*);
  void ApplyMatrices(double Rot[3][3],double Trans[3]);
  //  virtual void Interact();
  //  void Show();
  vector<Polygone*> m_pol;

  ~GeomObject();
 private:


};

#endif
