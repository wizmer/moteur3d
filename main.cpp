#include "Scene3D.h"
#include "KeyHandler.h"

#include "TCanvas.h"
#include "TH2D.h"
#include "TApplication.h"

#include <iostream>

#define print(token) cout << #token << " : " << token << endl
using namespace std;

int main(int argc, char *argv[]){
  TApplication app("app", &argc, argv);
  Scene3D* TheScene3D = Scene3D::GetScene3D();
  GeomObject* obj = new GeomObject("Triangle.txt");
  
  TheScene3D->AddWorldObject(new WorldObject(obj));
  TheScene3D->AddWorldObject(new WorldObject(obj,5,0,0));
  TheScene3D->AddWorldObject(new WorldObject(obj,5,5,0));
  TheScene3D->AddWorldObject(new WorldObject(obj,0,5,0));

  Camera* Cam = new Camera(0,-4,0);

  TCanvas* can = new TCanvas();
  TH2D* h = new TH2D("h","h;Phi(rad);Tau(rad)",100,-1,1,100,-0.5,0.5);
  h->Draw("a");

  TheScene3D -> Project(Cam);
  KeyHandler* key = new KeyHandler(Cam,can);
  app.Run();
  return 1;

}
