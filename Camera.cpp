#include "Camera.h"

Camera::Camera(double fx,double fy,double fz,double fPhi,double fTau){
  m_pos = new Point(fx,fy,fz);
  Phi = fPhi;
  Tau = fTau;
}


void Camera::SetXYZ(Point* fPoint){
  m_pos->SetX(fPoint->GetX());
  m_pos->SetY(fPoint->GetY());
  m_pos->SetZ(fPoint->GetZ());
}
void Camera::SetXYZ(double x,double y,double z){
  m_pos->SetX(x);
  m_pos->SetY(y);
  m_pos->SetZ(z);
}

