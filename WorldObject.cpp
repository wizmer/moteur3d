#include "WorldObject.h"

WorldObject::WorldObject(Object* obj,double **rot, double *trans):m_obj(obj){
  for(int i = 0;i<3;i++){
    if(rot) for(int j = 0;j<3;j++) Rot[i][j] = rot[i][j];
    else {
      for(int j = 0;j<3;j++){
	if(i==j) Rot[i][j] = 1;
	else Rot[i][j] = 0;
      }
    }
    if(trans) Trans[i] = trans[i];
    else Trans[i] = 0;
  }
  int Nsurf = m_obj->m_surf.size();
  for(int i = 0;i<Nsurf;i++){
    m_surf.push_back(new Surface(m_obj->m_surf[i],Rot,Trans));
  }
}
