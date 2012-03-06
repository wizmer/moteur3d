#ifndef CAMERA_H
#define CAMERA_H

#include "Point3D.h"
//#include "Transformation.h"
#include "Matrix.h"

#include <math.h>
#include <iostream>

class Matrix;

class Camera{
 private:
  Matrix* m_rot;
  double m_tau,m_phi;
  Point3D* m_M;
 public:
  const static double StepPhi;
  const static double StepTau;
  const static double StepTranslation;
  Camera(double fx = 0,double fy = 0,double fz = 0,double Rx = 0,double Ry = 0, double Rz = 0);
  ~Camera();

  //  void SetXYZ(Point3D* fPoint);
  //  void SetXYZ(double x,double y,double z);
  void Print();
  void RotateLeft();
  void RotateRight();
  void RotateDown();
  void RotateUp();

  void MoveUp();
  void MoveBack();
  void MoveLeft();
  void MoveRight();
  void Moving();
  Point3D* GetPointInCameraRef(Point3D* p);

  /* void MoveLeft(){ */
  /*   m_pos -> AddX( -cos(Tau)*cos(Phi)*StepTranslation); */
  /*   m_pos -> AddY( cos(Tau)*sin(Phi)*StepTranslation); */
  /* }; */

  /* void MoveRight(){ */
  /*   m_pos -> AddX( cos(Tau)*cos(Phi)*StepTranslation); */
  /*   m_pos -> AddY( -cos(Tau)*sin(Phi)*StepTranslation); */
  /* }; */

  /* void MoveBack(){ */
  /*   m_pos->AddX( -cos(Tau)*sin(Phi)*StepTranslation); */
  /*   m_pos->AddY( -cos(Tau)*cos(Phi)*StepTranslation); */
  /*   m_pos->AddZ( -sin(Tau)*StepTranslation); */
  /*   //    std::cout << "tau : " << Tau << std::endl; */
  /* }; */
  /* void MoveUp(){ */
  /*   m_pos->AddX( cos(Tau)*sin(Phi)*StepTranslation); */
  /*   m_pos->AddY( cos(Tau)*cos(Phi)*StepTranslation); */
  /*   m_pos->AddZ( sin(Tau)*StepTranslation); */
  /* }; */

  /* double GetX(){return m_pos->GetX();}; */
  /* double GetY(){return m_pos->GetY();}; */
  /* double GetZ(){return m_pos->GetZ();}; */
  /* double GetPhi(){return Phi;}; */
  /* double GetTau(){return Tau;}; */

  void Project();
};

#endif
