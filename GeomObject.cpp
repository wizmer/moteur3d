#include "GeomObject.h"

using namespace std;

GeomObject::GeomObject(const char* NameFile){
  vector<Point3D*> Vec;
  ifstream f(NameFile);
  char name[256];
  if(f.is_open()){
    int N = -1;
  int Nface = -1;
  double x,y,z,u,v,w;
  while(strcmp(name,"end_header") != 0){
    f.getline (name,256);
    if(strncmp(name,"element vertex",14) == 0){
      N = atoi(name+15);
    }

    if(strncmp(name,"element face",12) == 0){
      Nface = atoi(name+13);
    }
  }

  for(int i = 0;i<N;i++){
    f >> x >> y >> z >> u >> v >> w;
    cout << x << "\t" << y << "\t" << z << "\t" << u << "\t" << v << "\t" << w << endl;
    Vec.push_back(new Point3D(x,y,z));
  }
  

  cout << "nface : " << Nface << endl;
  double trash;
  int Npoint,p1,p2,p3;
  for(int i = 0;i<Nface;i++){
    f >> Npoint >> p1 >> p2 >> p3;
    m_pol.push_back(new Polygone(Vec[p1],Vec[p2],Vec[p3]));
  }
  
  }else{
    cout << "File : " << NameFile << " not found !" << endl;
  }
}

// GeomObject::GeomObject(const char* NameFile){
//   ifstream f(NameFile);
//   if(f.is_open()){
//     double x1,y1,z1,x2,y2,z2,x3,y3,z3;
//     while(!f.eof()){
//       f >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
//       m_pol.push_back(new Polygone(x1,y1,z1,x2,y2,z2,x3,y3,z3));
//     }
//     m_pol.pop_back();
//   }else{
//     cout << "File : " << NameFile << " not found !" << endl;
//   }
// }

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
