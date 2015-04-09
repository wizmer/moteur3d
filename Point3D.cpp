#include "Point3D.h"

#define PI 3.1415926535897931
#define print(token) std::cout << #token << " : " << token << std::endl

void Point3D::ApplyMatrices(double Rot[3][3],double Trans[3]){
  double xtmp = x, ytmp = y, ztmp = z;
  x = Rot[0][0]*xtmp + Rot[0][1]*ytmp + Rot[0][2]*ztmp;
  y = Rot[1][0]*xtmp + Rot[1][1]*ytmp + Rot[1][2]*ztmp;
  z = Rot[2][0]*xtmp + Rot[2][1]*ytmp + Rot[2][2]*ztmp;
  if(Trans){
    x += Trans[0];
    y += Trans[1];
    z += Trans[2];
  }
}

 Point3D::Point3D(Point3D* M):x(M->x),y(M->y),z(M->z){
   //  ApplyMatrices(rot,trans);
}


Point3D::~Point3D()
{
  //In prevision of dynamical allocations.
}

Point2D* Point3D::GetTauPhi(Transformation* trans,Camera* cam){
  Point3D* GlobalPoint = (*trans -> m_trans) * (*this); 
  Point3D* CameraRefPoint = cam -> GetPointInCameraRef(GlobalPoint);

  if( CameraRefPoint -> y > 0){
    double r = sqrt(CameraRefPoint -> y * CameraRefPoint -> y + CameraRefPoint -> x * CameraRefPoint -> x);
    double rho = sqrt(CameraRefPoint -> y * CameraRefPoint -> y + CameraRefPoint -> x * CameraRefPoint -> x + CameraRefPoint -> z * CameraRefPoint -> z);
    double Phi = atan(CameraRefPoint -> x / CameraRefPoint -> y);
    double Tau = atan(CameraRefPoint -> z / CameraRefPoint -> y);
    
    delete GlobalPoint;
    delete CameraRefPoint;
    return new Point2D(Tau,Phi);
  }

  delete GlobalPoint;
  delete CameraRefPoint;

  return NULL;
}

// Point2D* Point3D::GetTauPhi(Transformation* trans,Camera* cam){
//   Point3D* GlobalPoint = (*trans -> m_trans) * (*this); 

//   double GlobalX = GlobalPoint -> GetX();
//   double GlobalY = GlobalPoint -> GetY();
//   double GlobalZ = GlobalPoint -> GetZ();
//   double Phi,Tau;

//   Phi = atan((GlobalX - cam->GetX())/(GlobalY - cam->GetY())) - cam->GetPhi();
  
//   if(pow(GlobalX - cam->GetX(),2) +pow(GlobalY - cam->GetY(),2) != 0)  Tau = atan((GlobalZ - cam->GetZ())/sqrt(pow(GlobalX - cam->GetX(),2) +pow(GlobalY - cam->GetY(),2))) - cam->GetTau();
//   //  if(pow(GlobalX - cam->GetX(),2) +pow(GlobalY - cam->GetY(),2) != 0)  Tau = atan((GlobalZ - cam->GetZ())/sqrt(pow(GlobalY - cam->GetY(),2) )) - cam->GetTau();
//   else Tau = PI;


//   if(GetY() -cam->GetY() < 0){
//     printf("bip");
//     Phi += PI;
//   }

//   while( Phi > PI) Phi -= 2*PI;
//   while( Phi < -PI) Phi += 2*PI;

//   // print(Phi);
//   // print(Tau);
//   // std::cout << std::endl;

//   return new Point2D(Tau,Phi);

// }

double Point3D::Distance(Point3D* p){
  return sqrt((p->GetX() - x)*(p->GetX() - x) + (p->GetY() - y)*(p->GetY() - y) + (p->GetZ() - z)*(p->GetZ() - z));
}

void Point3D::Print(const char* str){
  if(str) std::cout << str << " ";
  std::cout << "Point3D is : ("<< x << "," << y << "," << z << ")" << std::endl;
    
}

void Point3D::Subtract(Point3D* p){
  x -= p -> x;
  y -= p -> y;
  z -= p -> z;
}
