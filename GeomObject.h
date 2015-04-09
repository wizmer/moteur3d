#ifndef GEOMOBJECT_H
#define GEOMOBJECT_H

#include "Polygone.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

//#include "TH3F.h"


class GeomObject{
 public:
  GeomObject(const char*);
  void ApplyMatrices(double Rot[3][3],double Trans[3]);
  //  virtual void Interact();
  //  void Show();
  void InitTextFile(const char* NameFile);
  void InitBlender(const char* NameFile);
  std::vector<Polygone*> m_pol;

  ~GeomObject();
 private:


};

#endif
