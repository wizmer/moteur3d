#ifndef X11DISPLAY_H
#define X11DISPLAY_H

#include "opencv2/core/core.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <X11/Xlib.h>

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
  Display* m_Display;                             /* pointer to X Display structure.           */
  Window m_Win;                                   /* pointer to the newly created window.      */
  GC m_gc, m_rev_gc;
  Camera* m_Camera;
  XEvent m_event;
  long m_eventMask;
  double m_SizeX,m_SizeY;
  X11Display(Camera* fCam);
  double HeadX, HeadY,OldX,OldY, HeadDist,OldSize;
  

 public : 
  int AugmentedReality();
  void Do();
  static X11Display* GetX11Display(Camera* fCam = NULL);
  virtual ~X11Display();
  Window Create_window();
  Window GetWindow()  {return m_Win;}
  Display* GetDisplay(){return m_Display;}
  void Update(double x1,double y1,double x2,double y2);
  void Run();
  void Flush();
  void setPixel(int x,int y);
  void lineBresenham(int p1x, int p1y, int p2x, int p2y);
};

#endif
