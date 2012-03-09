#include "Scene3D.h"
#include "KeyHandler.h"

#include "TCanvas.h"
#include "TH2D.h"
#include "TApplication.h"
#include "TMath.h"

#include <iostream>

#define print(token) cout << #token << " : " << token << endl
using namespace std;

int main(int argc, char *argv[]){
  TApplication app("app", &argc, argv);
  Scene3D* TheScene3D = Scene3D::GetScene3D();
  //  GeomObject* obj = new GeomObject("cube.ply");
  GeomObject* obj = new GeomObject("vadertie.ply");

  int N = 1;
  for(int i = 0;i<N;i++){
    for(int j = 0;j<N;j++){
      TheScene3D->AddWorldObject(new WorldObject(obj,5*i,5*j,0));
    }
  }


  cout << "cam"  << endl;
  Camera* Cam = new Camera(0,-300,0);
  cout << "cam end"  << endl;

  TCanvas* can = new TCanvas("can","can",400,50,800,600);
  
  TH2D* h = new TH2D("h","h;Phi(rad);Tau(rad)",100,-40/180.*TMath::Pi(),40/180.*TMath::Pi(),100,-20/180.*TMath::Pi(),30/180.*TMath::Pi());
  h->Draw("a");

  TheScene3D -> Project(Cam);
  KeyHandler* key = new KeyHandler(Cam,can);

  app.Run();
  return 1;

}
