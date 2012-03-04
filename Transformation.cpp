#include "Transformation.h"

using namespace std;

#define print(token) cout << #token << " : " << token << endl

Transformation::Transformation(double Rx,double Ry, double Rz,double Tx,double Ty,double Tz,double Sx,double Sy,double Sz){
  m_rot = Matrix::RotationMatrix(Rx,Ry,Rz);
  m_trans = Matrix::TranslationMatrix(Tx,Ty,Tz);
  m_scale = Matrix::ScalingMatrix(Sx,Sy,Sz);

  // m_rot -> Print("rot");
  // m_trans -> Print("trans");
  // m_scale -> Print("m_scale");
  
  m_FinalTransfo = new Matrix(4,4);
}

// Transformation::Transformation(double **fRot,double *fTranslation, double fScale){
//   cout << "Construct Transformation" << endl;
//   double **TmpTrans = NULL;
//   if(fTranslation){
//     TmpTrans = new double*[3];
//     for(int i = 0;i<3;i++){
//       TmpTrans[i] = new double[1];
//       TmpTrans[i][0] = fTranslation[i];
//     }
//   }

//   m_rot = new Matrix(4,fRot);
//   m_trans = new Matrix(4,4,TmpTrans);
//   m_scale = fScale;
//   m_FinalTransfo = new Matrix(4,4);
//   if(TmpTrans){
//     cout << "delete TmpTrans" << endl;
//     for(int i = 0;i<3;i++) delete TmpTrans[i];
//     delete[] TmpTrans;
//   }
// }

Point3D* Transformation::Apply(Point3D *p){
  double x = p -> GetX();
  double y = p -> GetY();
  double z = p -> GetZ();
  Apply(x,y,z);
  return new Point3D(x,y,z);
}

void Transformation::Apply(double &x,double &y,double &z){
  
}

void Transformation::SetTranslation(double Tx,double Ty,double Tz){
  cout << "Transformation::SetTranslation"  << endl;
  m_trans -> SetTranslation(Tx,Ty,Tz);
}

void Transformation::ComputeFinalTransfo(){
  m_FinalTransfo -> Init();
  (*m_FinalTransfo) *= (*m_trans);
  (*m_FinalTransfo) *= (*m_rot);
  (*m_FinalTransfo) *= (*m_scale);
  m_FinalTransfo -> Print("m_FinalTransfo");
}

void Transformation::Print(){
  m_FinalTransfo -> Print("m_FinalTransfo");
}
