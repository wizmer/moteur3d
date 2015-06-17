#ifndef X11DISPLAY_H
#define X11DISPLAY_H

#include "opencv2/core/core.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "GL/freeglut.h"
#include "GL/gl.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Scene3D.h"
#include "Camera.h"

class X11Display 
{
  
 private :
  static X11Display* m_X11;
  double m_SizeX,m_SizeY;
  X11Display(Camera* fCam);
  double HeadX, HeadY,OldX,OldY, HeadDist,OldSize;
  

 public :
  Camera* m_Camera;
  int AugmentedReality();
  void Do();
  static X11Display* GetX11Display(Camera* fCam = NULL);
  virtual ~X11Display();
  void Update(double x1,double y1,double x2,double y2);
  void Run();
  void Flush();
};

#endif
