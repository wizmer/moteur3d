#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"
#include <math.h>
#include <iostream>

class Camera{
 private:
  Point* m_pos;
  double Phi,Tau;
  
 public:
  const static double StepRotation = 0.05;
  const static double StepTranslation = 0.1;
  Camera(double fx = 0,double fy = 0,double fz = 0,double fPhi = 0,double fTau = 0);
  void SetXYZ(Point* fPoint);
  void SetXYZ(double x,double y,double z);
  void RotateLeft(){Phi -= StepRotation;}
  void RotateRight(){Phi += StepRotation;}
  void RotateDown(){Tau -= StepRotation;}
  void RotateUp(){Tau += StepRotation;}
  /* void MoveLeft(){ double x = m_pos->GetX(); m_pos->SetX(x - StepTranslation);} */
  /* void MoveRight(){ double x = m_pos->GetX(); m_pos->SetX(x - StepTranslation);} */
  void MoveLeft(){};
  void MoveRight(){};
  void MoveBack(){
    m_pos->AddX( -cos(Tau)*sin(Phi)*StepTranslation);
    m_pos->AddY( -cos(Tau)*cos(Phi)*StepTranslation);
    m_pos->AddZ( -sin(Tau)*StepTranslation);
    //    std::cout << "tau : " << Tau << std::endl;
  };
  void MoveUp(){
    m_pos->AddX( cos(Tau)*sin(Phi)*StepTranslation);
    m_pos->AddY( cos(Tau)*cos(Phi)*StepTranslation);
    m_pos->AddZ( sin(Tau)*StepTranslation);
  };

  double GetX(){return m_pos->GetX();};
  double GetY(){return m_pos->GetY();};
  double GetZ(){return m_pos->GetZ();};
  double GetPhi(){return Phi;};
  double GetTau(){return Tau;};
};

#endif
