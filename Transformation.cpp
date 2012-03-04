#include "Transformation.h"

using namespace std;

#define print(token) cout << #token << " : " << token << endl
Transformation::Transformation(double Rx,double Ry, double Rz,double Tx,double Ty,double Tz,double scale){
  m_rot = new Matrix(3);
  m_rot -> SetRotation(Rx,Ry,Rz);
  m_trans = new Matrix(3,1);
  m_trans -> SetTranslation(Tx,Ty,Tz);
  m_scale = scale;
}

Transformation::Transformation(double **fRot,double *fTranslation, double fScale){
  cout << "Construct Transformation" << endl;
  double **TmpTrans = NULL;
  if(fTranslation){
    TmpTrans = new double*[3];
    for(int i = 0;i<3;i++){
      TmpTrans[i] = new double[1];
      TmpTrans[i][0] = fTranslation[i];
    }
  }

  m_rot = new Matrix(3,fRot);
  m_trans = new Matrix(3,1,TmpTrans);
  m_scale = fScale;

  if(TmpTrans){
    cout << "delete TmpTrans" << endl;
    for(int i = 0;i<3;i++) delete TmpTrans[i];
    delete[] TmpTrans;
  }
}


void Transformation::Apply(double &x,double &y,double &z){
  double xtmp = x * m_scale;
  double ytmp = y * m_scale;
  double ztmp = z * m_scale;
  
  x = m_rot -> Get(0,0) * xtmp + m_rot -> Get(0,1) * ytmp + m_rot -> Get(0,2) * ztmp;
  y = m_rot -> Get(1,0) * xtmp + m_rot -> Get(1,1) * ytmp + m_rot -> Get(1,2) * ztmp;
  z = m_rot -> Get(2,0) * xtmp + m_rot -> Get(2,1) * ytmp + m_rot -> Get(2,2) * ztmp;

  x += m_trans -> Get(0,0);
  y += m_trans -> Get(1,0);
  z += m_trans -> Get(2,0);
}

void Transformation::SetTranslation(double Tx,double Ty,double Tz){
  cout << "Transformation::SetTranslation"  << endl;
  m_trans -> SetTranslation(Tx,Ty,Tz);
}
