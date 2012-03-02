#include "Scene.h"
#include "ProjPolygone.h"

#include "TCanvas.h"
#include "TH2D.h"
#include "TApplication.h"

#include <iostream>

#define print(token) cout << #token << " : " << token << endl
using namespace std;

int main(int argc, char *argv[]){
  TApplication app("app", &argc, argv);
  Scene* TheScene = Scene::CreateScene();
  GeomObject* obj = new GeomObject("Triangle.txt");
  WorldObject* WObj = new WorldObject(obj);
  TheScene->AddWorldObject(WObj);

  int N = TheScene->m_wobj.size();
  for(int i = 0;i<N;i++){
    int Npol = ((TheScene->m_wobj)[i])->m_pol.size();
    for(int j = 0;j<Npol;j++){
      cout << ((TheScene->m_wobj)[i])->m_pol[j]->M[j]->x << "\t";
      cout << ((TheScene->m_wobj)[i])->m_pol[j]->M[j]->y << "\t";
      cout << ((TheScene->m_wobj)[i])->m_pol[j]->M[j]->z << "\t" << endl;

      cout << ((TheScene->m_wobj)[i])->m_pol[j]->M[1]->x << "\t";
      cout << ((TheScene->m_wobj)[i])->m_pol[j]->M[1]->y << "\t";
      cout << ((TheScene->m_wobj)[i])->m_pol[j]->M[1]->z << "\t" << endl;

      cout << ((TheScene->m_wobj)[i])->m_pol[j]->M[2]->x << "\t";
      cout << ((TheScene->m_wobj)[i])->m_pol[j]->M[2]->y << "\t";
      cout << ((TheScene->m_wobj)[i])->m_pol[j]->M[2]->z << "\t" << endl;
    }
  }

  Camera* Cam = new Camera(0,-4,0);
  ProjPolygone* ProjPol = new ProjPolygone(((TheScene->m_wobj)[0])->m_pol[0]);
  ProjPol->Update(Cam);
  ProjPol->Dump();

  TCanvas* can = new TCanvas();
  TH2D* h = new TH2D("h","h",100,-0.5,0.5,100,-0.5,0.5);
  h->Draw();
  ProjPol->Plot();
  app.Run();
  return 1;

}
