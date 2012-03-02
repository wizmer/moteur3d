#include "ProjPoint.h"

#define PI 3.14159265

ProjPoint::ProjPoint(Point* fPoint):m_point(fPoint){}

void ProjPoint::Update(Camera* cam){
  Phi = atan((m_point->GetX() - cam->GetX())/(m_point->GetY() - cam->GetY())) - cam->GetPhi();
  Tau = asin(m_point->GetZ() - cam->GetZ())/sqrt(pow(m_point->GetX() - cam->GetX(),2) +pow(m_point->GetY() - cam->GetY(),2)) - cam->GetTau();
   if(m_point->GetY() -cam->GetY() < 0) Phi += PI;
}
