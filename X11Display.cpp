#include "X11Display.h"

using namespace cv;

X11Display* X11Display::m_X11 = NULL;
#define PI 3.14159265358979312


Mat image;

bool backprojMode = false;
bool selectObject = false;
int trackObject = 0;
bool showHist = true;
Point origin;
Rect selection;
int vmin = 10, vmax = 256, smin = 30;

void onMouse( int event, int x, int y, int, void* )
{
    if( selectObject )
    {
        selection.x = MIN(x, origin.x);
        selection.y = MIN(y, origin.y);
        selection.width = std::abs(x - origin.x);
        selection.height = std::abs(y - origin.y);

        selection &= Rect(0, 0, image.cols, image.rows);
    }

    switch( event )
    {
    case CV_EVENT_LBUTTONDOWN:
        origin = Point(x,y);
        selection = Rect(x,y,0,0);
        selectObject = true;
        break;
    case CV_EVENT_LBUTTONUP:
        selectObject = false;
        if( selection.width > 0 && selection.height > 0 )
            trackObject = -1;
        break;
    }
}

void help()
{
    std::cout << "\nThis is a demo that shows mean-shift based tracking\n"
			"You select a color objects such as your face and it tracks it.\n"
			"This reads from video camera (0 by default, or the camera number the user enters\n"
			"Usage: \n"
            "	./camshiftdemo [camera number]\n";

    std::cout << "\n\nHot keys: \n"
			"\tESC - quit the program\n"
			"\tc - stop the tracking\n"
			"\tb - switch to/from backprojection view\n"
			"\th - show/hide object histogram\n"
			"\tp - pause video\n"
            "To initialize tracking, select the object with mouse\n";
}

const char* keys = 
{
	"{1|  | 0 | camera number}"
};



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

int X11Display::AugmentedReality(){
    help();

    double Xmin = 99999;
    double Ymin = 99999;
    double Xmax = 0;
    double Ymax = 0;
    double CurrentR;

    double ScaleX = 0.02, ScaleY = 0.02, ScaleDist = 0.1;
    VideoCapture cap;
    Rect trackWindow;
    RotatedRect trackBox;
    int hsize = 16;
    float hranges[] = {0,180};
    const float* phranges = hranges;
    //	CommandLineParser parser(argc, argv, keys);
    CommandLineParser parser(1, NULL, keys);
    int camNum = parser.get<int>("1");     
	
    cap.open(camNum);

    if( !cap.isOpened() )
        {
            help();
            std::cout << "***Could not initialize capturing...***\n";
            std::cout << "Current parameter's value: \n";
            parser.printParams();
            return -1;
        }

    namedWindow( "Histogram", 0 );
    namedWindow( "CamShift Demo", 0 );
    setMouseCallback( "CamShift Demo", onMouse, 0 );
    createTrackbar( "Vmin", "CamShift Demo", &vmin, 256, 0 );
    createTrackbar( "Vmax", "CamShift Demo", &vmax, 256, 0 );
    createTrackbar( "Smin", "CamShift Demo", &smin, 256, 0 );

    Mat frame, hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;
    bool paused = false;

    OldX = 200;
    OldY = 200;
    OldSize = 200;

    for(;;)
        {
            if( !paused )
                {
                    cap >> frame;
                    if( frame.empty() )
                        break;
                }

            frame.copyTo(image);
        
            if( !paused )
                {
                    cvtColor(image, hsv, CV_BGR2HSV);

                    std::cout << "trackObject : " << trackObject << std::endl;
                    if( trackObject )
                        {
                            int _vmin = vmin, _vmax = vmax;

                            inRange(hsv, Scalar(0, smin, MIN(_vmin,_vmax)),
                                    Scalar(180, 256, MAX(_vmin, _vmax)), mask);
                            int ch[] = {0, 0};
                            hue.create(hsv.size(), hsv.depth());
                            mixChannels(&hsv, 1, &hue, 1, ch, 1);

                            if( trackObject < 0 )
                                {
                                    Mat roi(hue, selection), maskroi(mask, selection);
                                    calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
                                    normalize(hist, hist, 0, 255, CV_MINMAX);
                    
                                    trackWindow = selection;
                                    trackObject = 1;

                                    histimg = Scalar::all(0);
                                    int binW = histimg.cols / hsize;
                                    Mat buf(1, hsize, CV_8UC3);
                                    for( int i = 0; i < hsize; i++ )
                                        buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180./hsize), 255, 255);
                                    cvtColor(buf, buf, CV_HSV2BGR);
                        
                                    for( int i = 0; i < hsize; i++ )
                                        {
                                            int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);
                                            rectangle( histimg, Point(i*binW,histimg.rows),
                                                       Point((i+1)*binW,histimg.rows - val),
                                                       Scalar(buf.at<Vec3b>(i)), -1, 8 );
                                        }
                                }

                            calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
                            backproj &= mask;
                            RotatedRect trackBox = CamShift(backproj, trackWindow,
                                                            TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));
                            if( trackWindow.area() <= 1 )
                                {
                                    int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5)/6;
                                    trackWindow = Rect(trackWindow.x - r, trackWindow.y - r,
                                                       trackWindow.x + r, trackWindow.y + r) &
                                        Rect(0, 0, cols, rows);
                                }

                            if( backprojMode )
                                cvtColor( backproj, image, CV_GRAY2BGR );
                            ellipse( image, trackBox, Scalar(0,0,255), 3, CV_AA );
                            //		std::cout << trackWindow.x << "\t" << trackWindow.y << std::endl;
                            if(trackWindow.x > Xmax) Xmax = trackWindow.x;
                            if(trackWindow.x < Xmin) Xmin = trackWindow.x;
                            if(trackWindow.y > Ymax) Ymax = trackWindow.y;
                            if(trackWindow.y < Ymin) Ymin = trackWindow.y;

                            HeadX = (trackWindow.x - OldX) * ScaleX;
                            HeadY = (trackWindow.y - OldY) * ScaleY;
                            double Size = sqrt(trackWindow.width*trackWindow.width + trackWindow.height*trackWindow.height);
                            HeadDist = (Size - OldSize) * ScaleDist;

                            OldX = trackWindow.x;
                            OldY = trackWindow.y;
                            OldSize = Size;
		
                            std::cout << "trackWindow.width : " << trackWindow.width << std::endl;
                            std::cout << "trackWindow.height : " << trackWindow.height << std::endl;
                            std::cout << "r : " << CurrentR << std::endl;
                            std::cout << "("<< Xmin << "," << Xmax << ")  -  (" << Ymin << "," << Ymax << ")" << std::endl;
                        }
                }
            else if( trackObject < 0 )
                paused = false;

            if( selectObject && selection.width > 0 && selection.height > 0 )
                {
                    Mat roi(image, selection);
                    bitwise_not(roi, roi);
                }

            imshow( "CamShift Demo", image );
            imshow( "Histogram", histimg );

            std::cout << "HeadX : " << HeadX << std::endl;
            std::cout << "HeadY : " << HeadY << std::endl;
            m_Camera->MoveLeft(HeadX);
            m_Camera->MoveUp(HeadY);
            //	m_Camera->MoveForward(HeadDist);
            Do();

            Scene3D::GetScene3D() -> Project(m_Camera);
            char c = (char)waitKey(10);
            if( c == 27 )
                break;
            switch(c)
                {
                case 'b':
                    backprojMode = !backprojMode;
                    break;
                case 'c':
                    trackObject = 0;
                    histimg = Scalar::all(0);
                    break;
                case 'h':
                    showHist = !showHist;
                    if( !showHist )
                        destroyWindow( "Histogram" );
                    else
                        namedWindow( "Histogram", 1 );
                    break;
                case 'p':
                    paused = !paused;
                    break;
                default:
                    ;
                }
        }

    return 0;
}

int Check(Display* a,XEvent* b,char *c){
  return 1;
}

void X11Display::Do(){
  KeySym ks;

  //  XNextEvent( m_Display, &m_event );   // calls XFlush()
  if(XCheckIfEvent( m_Display, &m_event,Check,"" )){

    ks = XKeycodeToKeysym(m_Display, m_event.xkey.keycode,0);

    if(ks){
      std::cout << "ks : " << XKeysymToString(ks) << std::endl;
      if(strcmp(XKeysymToString(ks),"a") == 0){
	m_Camera->MoveLeft();
      }

      if(strcmp(XKeysymToString(ks),"d") == 0){
	m_Camera->MoveRight();
      }

      if(strcmp(XKeysymToString(ks),"w") == 0){
	m_Camera->MoveForward();
      }

      if(strcmp(XKeysymToString(ks),"s") == 0){
	m_Camera->MoveBack();
      }

      if(strcmp(XKeysymToString(ks),"Left") == 0){
	m_Camera->RotateLeft();
      }

      if(strcmp(XKeysymToString(ks),"Right") == 0){
	m_Camera->RotateRight();
      }

      if(strcmp(XKeysymToString(ks),"Down") == 0){
	m_Camera->RotateDown();
      }

      if(strcmp(XKeysymToString(ks),"Up") == 0){
	m_Camera->RotateUp();
      }
    }
  }
}

void X11Display::Run(){
  std::cout << "frite : " << m_X11 << std::endl;
  m_eventMask = ButtonPressMask | ButtonReleaseMask | KeyPressMask;

  XSelectInput(m_Display,m_Win,m_eventMask); // override prev

  AugmentedReality();

  // do{
  //   std::cout << "Do!!" << std::endl;
  //   std::cout << "waite" << std::endl;
  //   XNextEvent( m_Display, &m_event );   // calls XFlush()
  //   ks = XKeycodeToKeysym(m_Display, m_event.xkey.keycode,0);
  //   std::cout << "here" << std::endl;
  //   if(ks){
  //     if(strcmp(XKeysymToString(ks),"a") == 0){
  // 	m_Camera->MoveLeft();
  // 	Scene3D::GetScene3D() -> Project(m_Camera);
  //     }

  //     if(strcmp(XKeysymToString(ks),"d") == 0){
  // 	m_Camera->MoveRight();
  // 	Scene3D::GetScene3D() -> Project(m_Camera);
  //     }

  //     if(strcmp(XKeysymToString(ks),"w") == 0){
  // 	m_Camera->MoveForward();
  // 	Scene3D::GetScene3D() -> Project(m_Camera);
  //     }

  //     if(strcmp(XKeysymToString(ks),"s") == 0){
  // 	m_Camera->MoveBack();
  // 	Scene3D::GetScene3D() -> Project(m_Camera);
  //     }

  //     if(strcmp(XKeysymToString(ks),"Left") == 0){
  // 	m_Camera->RotateLeft();
  // 	Scene3D::GetScene3D() -> Project(m_Camera);
  //     }

  //     if(strcmp(XKeysymToString(ks),"Right") == 0){
  // 	m_Camera->RotateRight();
  // 	Scene3D::GetScene3D() -> Project(m_Camera);
  //     }

  //     if(strcmp(XKeysymToString(ks),"Down") == 0){
  // 	m_Camera->RotateDown();
  // 	Scene3D::GetScene3D() -> Project(m_Camera);
  //     }

  //     if(strcmp(XKeysymToString(ks),"Up") == 0){
  // 	m_Camera->RotateUp();
  // 	Scene3D::GetScene3D() -> Project(m_Camera);
  //     }
  //   }
  // }
  //  while( m_event.type != ButtonRelease );

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

  if (p1x > p2x)  // Std::Swap points if p1 is on the right of p2
    {
      std::swap(p1x, p2x);
      std::swap(p1y, p2y);
    }

  // Handle trivial cases separately for algorithm speed up.
  // Trivial case 1: m = +/-INF (Vertical line)
  if (p1x == p2x)
    {
      if (p1y > p2y)  // Std::Swap y-coordinates if p1 is above p2
        {
	  std::swap(p1y, p2y);
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
