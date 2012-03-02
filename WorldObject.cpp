#include "WorldObject.h"

WorldObject::WorldObject(GeomObject* obj,double **rot, double *trans, double scale):m_obj(obj){
  m_trans = new Transformation(rot,trans,scale);

  int Npol = m_obj->m_pol.size();
  for(int i = 0;i<Npol;i++){
    m_pol.push_back(new Polygone(m_obj->m_pol[i]));
  }
}

WorldObject::~WorldObject(){
  // In case of dynamical allocations within the constructor.
}
