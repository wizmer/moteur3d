#include "Scene3D.h"
#include "X11Display.h"

#include <iostream>

#define PI 3.14159265358979312
#define print(token) cout << #token << " : " << token << endl
using namespace std;

int main(int argc, char *argv[]){
  Scene3D* TheScene3D = Scene3D::GetScene3D();
  //  GeomObject* obj = new GeomObject("spaceship.ply");
  //  GeomObject* obj = new GeomObject("vadertie.ply");
  GeomObject* obj = new GeomObject("Cube.txt");
  //  GeomObject* obj = new GeomObject("LightVadertie.ply");

  int N = 10;
  for(int i = 0;i<N;i++){
    for(int j = 0;j<N;j++){
      TheScene3D->AddWorldObject(new WorldObject(obj,5*i,5*j,0));
    }
  }

  Camera* Cam = new Camera(0,-30,0);

  X11Display::GetX11Display(Cam);

  X11Display::GetX11Display() -> Run();
  return 1;
}
