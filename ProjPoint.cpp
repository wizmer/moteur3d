#include "ProjPoint.h"

#define PI 3.1415926535897931
#define print(token) cout << #token << " : " << token << endl
using namespace std;

ProjPoint::ProjPoint(Point* fPoint):m_point(fPoint){}

void ProjPoint::Update(Camera* cam){
  // double GlobalX = 0, GlobalY = 0, GlobalZ = 0;
  // for(int i = 0;i<3;i++){
  //     GlobalX += 
  // }

  Phi = atan((m_point->GetX() - cam->GetX())/(m_point->GetY() - cam->GetY())) - cam->GetPhi();
  
  if(pow(m_point->GetX() - cam->GetX(),2) +pow(m_point->GetY() - cam->GetY(),2) != 0)  Tau = atan((m_point->GetZ() - cam->GetZ())/sqrt(pow(m_point->GetX() - cam->GetX(),2) +pow(m_point->GetY() - cam->GetY(),2))) - cam->GetTau();
  else Tau = PI;


   if(m_point->GetY() -cam->GetY() < 0) Phi += PI;

   while( Phi > PI) Phi -= 2*PI;
   while( Phi < -PI) Phi += 2*PI;

   print(Phi);
   print(Tau);
   print(cam->GetX());
   print(cam->GetY());
   print(cam->GetZ());
   cout << endl;
}
