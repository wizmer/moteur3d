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
  int X1 = m_SizeX / AngleX * (x1 + AngleX/2.);
  int Y1 = m_SizeY / AngleY * (y1 + AngleY/2.);
  int X2 = m_SizeX / AngleX * (x2 + AngleX/2.);
  int Y2 = m_SizeY / AngleY * (y2 + AngleY/2.);
  //  XDrawLine(m_Display, m_Win, m_gc, X1, Y1,X2,Y2); //from-to
  lineBresenham(X1,Y1,X2,Y2);
}

void X11Display::setPixel(int x,int y){
  XSetForeground( m_Display, m_gc, 0xff0000 );
  XDrawPoint(m_Display, m_Win, m_gc, x, y);
}

void X11Display::Flush(){
  int x, y;
  for (x=0; x<m_SizeX; x++)
    for (y=0; y<m_SizeY; y++)   XDrawPoint(m_Display, m_Win, m_rev_gc, x, y);
}

/**
 * Draws a line between two points p1(p1x,p1y) and p2(p2x,p2y).
 * This function is based on the Bresenham's line algorithm and is highly 
 * optimized to be able to draw lines very quickly. There is no floating point 
 * arithmetic nor multiplications and divisions involved. Only addition, 
 * subtraction and bit shifting are used. 
 *
 * Note that you have to define your own customized setPixel(x,y) function, 
 * which essentially lights a pixel on the screen.
 */
void X11Display::lineBresenham(int p1x, int p1y, int p2x, int p2y)
{
  int F, x, y;

  if (p1x > p2x)  // Swap points if p1 is on the right of p2
    {
      swap(p1x, p2x);
      swap(p1y, p2y);
    }

  // Handle trivial cases separately for algorithm speed up.
  // Trivial case 1: m = +/-INF (Vertical line)
  if (p1x == p2x)
    {
      if (p1y > p2y)  // Swap y-coordinates if p1 is above p2
        {
	  swap(p1y, p2y);
        }

      x = p1x;
      y = p1y;
      while (y <= p2y)
        {
	  setPixel(x, y);
	  y++;
        }
      return;
    }
  // Trivial case 2: m = 0 (Horizontal line)
  else if (p1y == p2y)
    {
      x = p1x;
      y = p1y;

      while (x <= p2x)
        {
	  setPixel(x, y);
	  x++;
        }
      return;
    }


  int dy            = p2y - p1y;  // y-increment from p1 to p2
  int dx            = p2x - p1x;  // x-increment from p1 to p2
  int dy2           = (dy << 1);  // dy << 1 == 2*dy
  int dx2           = (dx << 1);
  int dy2_minus_dx2 = dy2 - dx2;  // precompute constant for speed up
  int dy2_plus_dx2  = dy2 + dx2;


  if (dy >= 0)    // m >= 0
    {
      // Case 1: 0 <= m <= 1 (Original case)
      if (dy <= dx)   
        {
	  F = dy2 - dx;    // initial F

	  x = p1x;
	  y = p1y;
	  while (x <= p2x)
            {
	      setPixel(x, y);
	      if (F <= 0)
                {
		  F += dy2;
                }
	      else
                {
		  y++;
		  F += dy2_minus_dx2;
                }
	      x++;
            }
        }
      // Case 2: 1 < m < INF (Mirror about y=x line
      // replace all dy by dx and dx by dy)
      else
        {
	  F = dx2 - dy;    // initial F

	  y = p1y;
	  x = p1x;
	  while (y <= p2y)
            {
	      setPixel(x, y);
	      if (F <= 0)
                {
		  F += dx2;
                }
	      else
                {
		  x++;
		  F -= dy2_minus_dx2;
                }
	      y++;
            }
        }
    }
  else    // m < 0
    {
      // Case 3: -1 <= m < 0 (Mirror about x-axis, replace all dy by -dy)
      if (dx >= -dy)
        {
	  F = -dy2 - dx;    // initial F

	  x = p1x;
	  y = p1y;
	  while (x <= p2x)
            {
	      setPixel(x, y);
	      if (F <= 0)
                {
		  F -= dy2;
                }
	      else
                {
		  y--;
		  F -= dy2_plus_dx2;
                }
	      x++;
            }
        }
      // Case 4: -INF < m < -1 (Mirror about x-axis and mirror 
      // about y=x line, replace all dx by -dy and dy by dx)
      else    
        {
	  F = dx2 + dy;    // initial F

	  y = p1y;
	  x = p1x;
	  while (y >= p2y)
            {
	      setPixel(x, y);
	      if (F <= 0)
                {
		  F += dx2;
                }
	      else
                {
		  x++;
		  F += dy2_plus_dx2;
                }
	      y--;
            }
        }
    }
}
