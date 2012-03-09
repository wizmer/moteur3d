#include "X11Display.h"

X11Display* X11Display::m_X11 = NULL;
#define PI 3.14159265358979312
using namespace std;

X11Display::X11Display(Camera* fCam):m_Camera(fCam){

  m_Display = XOpenDisplay( NULL );
  if( !m_Display ){ exit(-1); }


  int screenNumber = DefaultScreen(m_Display);
  unsigned long white = WhitePixel(m_Display,screenNumber);
  unsigned long black = BlackPixel(m_Display,screenNumber);
  m_SizeX = 800;
  m_SizeY = 600;

  m_Win = XCreateSimpleWindow(m_Display,
				   DefaultRootWindow(m_Display),
				   50, 50,   // origin
				   m_SizeX, m_SizeY, // size
				   0, black, // border
				   white );  // backgd

  XMapWindow( m_Display, m_Win );


  m_eventMask = StructureNotifyMask;
  XSelectInput( m_Display, m_Win, m_eventMask );

  do{
    XNextEvent( m_Display, &m_event );   // calls XFlush
  }while( m_event.type != MapNotify );


  m_gc = XCreateGC( m_Display, m_Win,
                     0,        // mask of values
                     NULL );   // array of values

  m_rev_gc = XCreateGC( m_Display, m_Win,
			 0,    // mask of values
                     NULL );   // array of values

  XSetForeground( m_Display, m_gc, black );
  XSetForeground( m_Display, m_rev_gc, white );
}


void X11Display::Run(){
  cout << "frite : " << m_X11 << endl;
  m_eventMask = ButtonPressMask | ButtonReleaseMask | KeyPressMask;

  XSelectInput(m_Display,m_Win,m_eventMask); // override prev
  KeySym ks;
  do{
    XNextEvent( m_Display, &m_event );   // calls XFlush()
    ks = XKeycodeToKeysym(m_Display, m_event.xkey.keycode,0);

    if(ks){
      if(strcmp(XKeysymToString(ks),"a") == 0){
	m_Camera->MoveLeft();
	Scene3D::GetScene3D() -> Project(m_Camera);
      }

      if(strcmp(XKeysymToString(ks),"d") == 0){
	m_Camera->MoveRight();
	Scene3D::GetScene3D() -> Project(m_Camera);
      }

      if(strcmp(XKeysymToString(ks),"w") == 0){
	m_Camera->MoveUp();
	Scene3D::GetScene3D() -> Project(m_Camera);
      }

      if(strcmp(XKeysymToString(ks),"s") == 0){
	m_Camera->MoveBack();
	Scene3D::GetScene3D() -> Project(m_Camera);
      }

      if(strcmp(XKeysymToString(ks),"Left") == 0){
	m_Camera->RotateLeft();
	Scene3D::GetScene3D() -> Project(m_Camera);
      }

      if(strcmp(XKeysymToString(ks),"Right") == 0){
	m_Camera->RotateRight();
	Scene3D::GetScene3D() -> Project(m_Camera);
      }

      if(strcmp(XKeysymToString(ks),"Down") == 0){
	m_Camera->RotateDown();
	Scene3D::GetScene3D() -> Project(m_Camera);
      }

      if(strcmp(XKeysymToString(ks),"Up") == 0){
	m_Camera->RotateUp();
	Scene3D::GetScene3D() -> Project(m_Camera);
      }
    }
  }while( m_event.type != ButtonRelease );

}

X11Display::~X11Display(){
  XDestroyWindow( m_Display, m_Win );
  XCloseDisplay( m_Display );
}

X11Display* X11Display::GetX11Display(Camera* fCam){
  if(m_X11) return m_X11;
  else {
    m_X11 = new X11Display(fCam);
    return m_X11;
  }
}

void X11Display::Update(double x1,double y1,double x2,double y2){
  double AngleX = 60 / 180. * PI;
  double AngleY = 60 / 180. * PI;
  double X1 = m_SizeX / AngleX * (x1 + AngleX/2.);
  double Y1 = m_SizeY / AngleY * (y1 + AngleY/2.);
  double X2 = m_SizeX / AngleX * (x2 + AngleX/2.);
  double Y2 = m_SizeY / AngleY * (y2 + AngleY/2.);
  XDrawLine(m_Display, m_Win, m_gc, X1, Y1,X2,Y2); //from-to
}


void X11Display::Flush(){
  int x, y;
  for (x=0; x<m_SizeX; x++)
    for (y=0; y<m_SizeY; y++)   XDrawPoint(m_Display, m_Win, m_rev_gc, x, y);
}
