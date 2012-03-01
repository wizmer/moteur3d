#ifndef OBJECT_H
#define OBJECT_H

#include "Surface.h"
#include <fstream.h>
//#include "TH3F.h"

class Object{
 public:
  Object(const char*);
  void ApplyMatrices(double Rot[3][3],double Trans[3]);
  //  virtual void Interact();
  //  void Show();
  vector<Surface*> m_surf;
 private:

};

#endif
