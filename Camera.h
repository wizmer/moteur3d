#ifndef CAMERA_H
#define CAMERA_H

#include "Point.h"

class Camera{
 private:
  Point* m_pos;
  double Phi,Tau;
  
 public:
  Camera(double fx = 0,double fy = 0,double fz = 0,double fPhi = 0,double fTau = 0);
  void SetXYZ(Point* fPoint);
  void SetXYZ(double x,double y,double z);
  inline double GetX(){return m_pos->GetX();};
  inline double GetY(){return m_pos->GetY();};
  inline double GetZ(){return m_pos->GetZ();};
  inline double GetPhi(){return Phi;};
  inline double GetTau(){return Tau;};
};

#endif
