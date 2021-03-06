#include "Camera.h"

#define print(token) std::cout << #token << "\t" << token << std::endl

const double Camera::StepPhi = 0.05;
const double Camera::StepTau = 0.05;
const double Camera::StepTranslation = 4;

Camera::Camera(double Tx,double Ty,double Tz,double Rx,double Ry,double Rz){
  m_M = new Point3D(Tx,Ty,Tz);
  m_phi = Rz;
  m_tau = Rx;
  std::cout << "new transfo" << std::endl;
  //  m_rot = new Transformation(Rx,Ry,Rz,Tx,Ty,Tz);
  m_rot = new Matrix(4);
  m_rot -> SetRotation(-m_tau,0,m_phi);
}

Camera::~Camera(){
  if(m_M) delete m_M;
  if(m_rot) delete m_rot;
}

// void Camera::SetXYZ(Point3D* fPoint){
//   SetXYZ(fPoint -> GetX(),fPoint -> GetY(),fPoint -> GetZ());
// }

// void Camera::SetXYZ(double x,double y,double z){
//   m_rot -> SetTranslation(x,y,z);
//   m_rot -> ComputeFinalTransfo();
// }

void Camera::RotateLeft(){
  m_phi -= StepPhi;
  m_rot -> SetRotation(-m_tau,0,m_phi);
}

void Camera::RotateRight(){
  m_phi += StepPhi;
  m_rot -> SetRotation(-m_tau,0,m_phi);
}

void Camera::RotateUp(){
  m_tau -= StepTau;
  m_rot -> SetRotation(-m_tau,0,m_phi);
}

void Camera::RotateDown(){
  m_tau += StepTau;
  m_rot -> SetRotation(-m_tau,0,m_phi);
}

void Camera::MoveForward(double step){
  m_M -> x += sin(m_phi) * cos(m_tau) * step;
  m_M -> y += cos(m_phi) * cos(m_tau) * step;
  m_M -> z += sin(m_tau) * step;
}

void Camera::MoveBack(double step){
  m_M -> x -= sin(m_phi) * cos(m_tau) * step;
  m_M -> y -= cos(m_phi) * cos(m_tau) * step;
  m_M -> z -= sin(m_tau) * step;
}

void Camera::MoveLeft(double step){
  m_M -> x += - cos(m_phi) * step;
  m_M -> y += sin(m_phi) * step;
}

void Camera::MoveRight(double step){
  m_M -> x -= - cos(m_phi) * step;
  m_M -> y -= sin(m_phi) * step;
}

void Camera::MoveUp(double step){
  m_M -> x -= sin(m_phi) * cos(m_tau) * step;
  m_M -> y += cos(m_phi) * cos(m_tau) * step;
  m_M -> z += cos(m_tau) * step;
}

void Camera::MoveDown(double step){
  m_M -> x += sin(m_phi) * cos(m_tau) * step;
  m_M -> y -= cos(m_phi) * cos(m_tau) * step;
  m_M -> z -= cos(m_tau) * step;
}

void Camera::Moving(){
  // For future use, is called when camera is moving
  //  m_rot -> ComputeFinalTransfo();
  //  m_rot -> m_trans -> Print("trans");
  // m_M -> Print("M");
  // m_rot  -> Print("rot");
  print(m_phi);
  print(m_tau);
}

Point3D* Camera::GetPointInCameraRef(Point3D* p){
  p -> Subtract(m_M);
  Point3D* NewPoint = (*m_rot) * (*p);
  return NewPoint;
};

void Camera::Print(){
  m_rot -> Print("Camera rot");
}
