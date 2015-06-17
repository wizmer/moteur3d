#include "X11Display.h"

X11Display* X11Display::m_X11 = NULL;
#define PI 3.14159265358979312


//Mat image;
//Point origin;
//Rect selection;

bool backprojMode = false;
bool selectObject = false;
int trackObject = 0;
bool showHist = true;
int vmin = 10, vmax = 256, smin = 30;

void onMouse( int event, int x, int y, int, void* )
{
    // if( selectObject )
    // {
    //     selection.x = MIN(x, origin.x);
    //     selection.y = MIN(y, origin.y);
    //     selection.width = std::abs(x - origin.x);
    //     selection.height = std::abs(y - origin.y);

    //     selection &= Rect(0, 0, image.cols, image.rows);
    // }

    // switch( event )
    // {
    // case CV_EVENT_LBUTTONDOWN:
    //     origin = Point(x,y);
    //     selection = Rect(x,y,0,0);
    //     selectObject = true;
    //     break;
    // case CV_EVENT_LBUTTONUP:
    //     selectObject = false;
    //     if( selection.width > 0 && selection.height > 0 )
    //         trackObject = -1;
    //     break;
    // }
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


void renderScene(){
    //std::cout << "render" << std::endl;
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Reset transformations
    glLoadIdentity();
    Scene3D::GetScene3D() -> Project( X11Display::GetX11Display()->m_Camera);
    glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
    switch(key){
    case 'a':
    	X11Display::GetX11Display()->m_Camera->MoveLeft();
        break;
        
    case 'd':
    	X11Display::GetX11Display()->m_Camera->MoveRight();
        break;

    case 'w':
    	X11Display::GetX11Display()->m_Camera->MoveForward();
        break;

    case 's':
    	X11Display::GetX11Display()->m_Camera->MoveBack();
        break;
    }
}

void processSpecialKeys(int key, int x, int y) {
    switch(key){
    case GLUT_KEY_LEFT:
        X11Display::GetX11Display()->m_Camera->RotateLeft();
        break;

    case GLUT_KEY_RIGHT:
        X11Display::GetX11Display()->m_Camera->RotateRight();
        break;

    case GLUT_KEY_DOWN:
        X11Display::GetX11Display()->m_Camera->RotateDown();
        break;

    case GLUT_KEY_UP:
        X11Display::GetX11Display()->m_Camera->RotateUp();
        break;
    }
}

X11Display::X11Display(Camera* fCam):m_Camera(fCam){
    m_SizeX = 800;
    m_SizeY = 600;

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(m_SizeX,m_SizeX);
    glutCreateWindow("Lighthouse3D- GLUT Tutorial");

    // register callbacks
    glutDisplayFunc(renderScene);
    glutSpecialFunc(processSpecialKeys);
    
    // here is the idle func registration
    glutIdleFunc(renderScene);

    glutKeyboardFunc(processNormalKeys);
}

int X11Display::AugmentedReality(){
//     help();

//     double Xmin = 99999;
//     double Ymin = 99999;
//     double Xmax = 0;
//     double Ymax = 0;
//     double CurrentR;

//     double ScaleX = 0.02, ScaleY = 0.02, ScaleDist = 0.1;
//     VideoCapture cap;
//     Rect trackWindow;
//     RotatedRect trackBox;
//     int hsize = 16;
//     float hranges[] = {0,180};
//     const float* phranges = hranges;
//     //	CommandLineParser parser(argc, argv, keys);
//     CommandLineParser parser(1, NULL, keys);
//     int camNum = parser.get<int>("1");     
	
//     cap.open(camNum);

//     if( !cap.isOpened() )
//         {
//             help();
//             std::cout << "***Could not initialize capturing...***\n";
//             std::cout << "Current parameter's value: \n";
//             parser.printParams();
//             return -1;
//         }

//     namedWindow( "Histogram", 0 );
//     namedWindow( "CamShift Demo", 0 );
//     setMouseCallback( "CamShift Demo", onMouse, 0 );
//     createTrackbar( "Vmin", "CamShift Demo", &vmin, 256, 0 );
//     createTrackbar( "Vmax", "CamShift Demo", &vmax, 256, 0 );
//     createTrackbar( "Smin", "CamShift Demo", &smin, 256, 0 );

//     Mat frame, hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;
//     bool paused = false;

//     OldX = 200;
//     OldY = 200;
//     OldSize = 200;

//     for(;;)
//         {
//             if( !paused )
//                 {
//                     cap >> frame;
//                     if( frame.empty() )
//                         break;
//                 }

//             frame.copyTo(image);
        
//             if( !paused )
//                 {
//                     cvtColor(image, hsv, CV_BGR2HSV);

//                     if( trackObject )
//                         {
//                             int _vmin = vmin, _vmax = vmax;

//                             inRange(hsv, Scalar(0, smin, MIN(_vmin,_vmax)),
//                                     Scalar(180, 256, MAX(_vmin, _vmax)), mask);
//                             int ch[] = {0, 0};
//                             hue.create(hsv.size(), hsv.depth());
//                             mixChannels(&hsv, 1, &hue, 1, ch, 1);

//                             if( trackObject < 0 )
//                                 {
//                                     Mat roi(hue, selection), maskroi(mask, selection);
//                                     calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
//                                     normalize(hist, hist, 0, 255, CV_MINMAX);
                    
//                                     trackWindow = selection;
//                                     trackObject = 1;

//                                     histimg = Scalar::all(0);
//                                     int binW = histimg.cols / hsize;
//                                     Mat buf(1, hsize, CV_8UC3);
//                                     for( int i = 0; i < hsize; i++ )
//                                         buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180./hsize), 255, 255);
//                                     cvtColor(buf, buf, CV_HSV2BGR);
                        
//                                     for( int i = 0; i < hsize; i++ )
//                                         {
//                                             int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);
//                                             rectangle( histimg, Point(i*binW,histimg.rows),
//                                                        Point((i+1)*binW,histimg.rows - val),
//                                                        Scalar(buf.at<Vec3b>(i)), -1, 8 );
//                                         }
//                                 }

//                             calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
//                             backproj &= mask;
//                             RotatedRect trackBox = CamShift(backproj, trackWindow,
//                                                             TermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ));
//                             if( trackWindow.area() <= 1 )
//                                 {
//                                     int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5)/6;
//                                     trackWindow = Rect(trackWindow.x - r, trackWindow.y - r,
//                                                        trackWindow.x + r, trackWindow.y + r) &
//                                         Rect(0, 0, cols, rows);
//                                 }

//                             if( backprojMode )
//                                 cvtColor( backproj, image, CV_GRAY2BGR );
//                             ellipse( image, trackBox, Scalar(0,0,255), 3, CV_AA );
//                             //		std::cout << trackWindow.x << "\t" << trackWindow.y << std::endl;
//                             if(trackWindow.x > Xmax) Xmax = trackWindow.x;
//                             if(trackWindow.x < Xmin) Xmin = trackWindow.x;
//                             if(trackWindow.y > Ymax) Ymax = trackWindow.y;
//                             if(trackWindow.y < Ymin) Ymin = trackWindow.y;

//                             HeadX = (trackWindow.x - OldX) * ScaleX;
//                             HeadY = (trackWindow.y - OldY) * ScaleY;
//                             double Size = sqrt(trackWindow.width*trackWindow.width + trackWindow.height*trackWindow.height);
//                             HeadDist = (Size - OldSize) * ScaleDist;

//                             OldX = trackWindow.x;
//                             OldY = trackWindow.y;
//                             OldSize = Size;
		
//                             std::cout << "trackWindow.width : " << trackWindow.width << std::endl;
//                             std::cout << "trackWindow.height : " << trackWindow.height << std::endl;
//                             std::cout << "r : " << CurrentR << std::endl;
//                             std::cout << "("<< Xmin << "," << Xmax << ")  -  (" << Ymin << "," << Ymax << ")" << std::endl;
//                         }
//                 }
//             else if( trackObject < 0 )
//                 paused = false;

//             if( selectObject && selection.width > 0 && selection.height > 0 )
//                 {
//                     Mat roi(image, selection);
//                     bitwise_not(roi, roi);
//                 }

//             imshow( "CamShift Demo", image );
//             imshow( "Histogram", histimg );

//             std::cout << "HeadX : " << HeadX << std::endl;
//             std::cout << "HeadY : " << HeadY << std::endl;
//             m_Camera->MoveLeft(HeadX);
//             m_Camera->MoveUp(HeadY);
//             //	m_Camera->MoveForward(HeadDist);
//             Do();

//             Scene3D::GetScene3D() -> Project(m_Camera);
//             char c = (char)waitKey(10);
//             if( c == 27 )
//                 break;
//             switch(c)
//                 {
//                 case 'b':
//                     backprojMode = !backprojMode;
//                     break;
//                 case 'c':
//                     trackObject = 0;
//                     histimg = Scalar::all(0);
//                     break;
//                 case 'h':
//                     showHist = !showHist;
//                     if( !showHist )
//                         destroyWindow( "Histogram" );
//                     else
//                         namedWindow( "Histogram", 1 );
//                     break;
//                 case 'p':
//                     paused = !paused;
//                     break;
//                 default:
//                     ;
//                 }
//         }

//     return 0;
// }

// int Check(Display* a,XEvent* b,char *c){
//   return 1;
// }

}

void X11Display::Run(){
  std::cout << "frite : " << m_X11 << std::endl;

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
  glutMainLoop();
  
}

X11Display::~X11Display(){

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

  //std::cout << x1 << ', ' << y1 << ', ' << x2 << ', ' << y2 << std::endl;
  //std::cout << "update " << X1 << "\t" << Y1 << "\t" << X2 << "\t" << Y2 << std::endl;


  glBegin(GL_LINES);
  glVertex2f(x1, y1);
  glVertex2f(x2, y2);
  // glVertex2f(X1, Y1);
  // glVertex2f(X2, Y2);
  glEnd();
}


void X11Display::Flush(){
    
}


