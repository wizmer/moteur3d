#include "GeomObject.h"

GeomObject::GeomObject(const char* NameFile){
  ifstream f(NameFile);
  if(f.is_open()){
    double x1,y1,z1,x2,y2,z2,x3,y3,z3;
    while(!f.eof()){
      f >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
      m_pol.push_back(new Polygone(x1,y1,z1,x2,y2,z2,x3,y3,z3));
    }
  }else{
    cout << "File : " << NameFile << " not found !" << endl;
  }
}

void GeomObject::ApplyMatrices(double Rot[3][3],double Trans[3]){
  int N = m_pol.size();
  for(int i = 0;i<N;i++){
    m_pol[i]->ApplyMatrices(Rot,Trans);
  }
}

GeomObject::~GeomObject(){
  //In prevision of dynamical allocations;
}

// void Object::Show(){
//   int N = Surf.size();
//   TH3F* h = new TH3F("h","h",100,-2,2,100,-2,2,100,-2,2);
//   for(int i = 0;i<N;i++){
//     int Nsurf = Surf[i]->M.size();
//     for(int j = 0;j<Nsurf;j++){
//       h->Fill(Surf[i]->M[j]->x,Surf[i]->M[j]->y,Surf[i]->M[j]->z);
//     }
//   }
//   h->Draw();
// }
