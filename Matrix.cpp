#include "Matrix.h"

using namespace std;

Matrix::Matrix(int fRowSize,int fColumnSize,double **fMat){
  cout << "Construct Matrix" << endl;
  Init(fRowSize,fColumnSize);
  if(fMat) SetArray(fMat);
}

Matrix::Matrix(int fSize,double **fMat){
  cout << "Construct square Matrix" << endl;
  Init(fSize,fSize);
  if(fMat) SetArray(fMat);
}

void Matrix::Init(int fRowSize,int fColumnSize){
  cout << "Init Matrix" << endl;
  m_RowSize = fRowSize;
  m_ColumnSize = fColumnSize;
  m_mat = new double*[m_RowSize];

  for(int i = 0;i<m_RowSize;i++){
    m_mat[i] = new double[m_RowSize];
    for(int j = 0;j<m_ColumnSize;j++){
      if(i == j) m_mat[i][j] = 1;
      else m_mat[i][j] = 0;
    }
  }

}

 void Matrix::SetArray(double **fMat){
   cout << "SetArray" << endl;
   for(int i = 0;i<m_RowSize;i++){
     for(int j = 0;j<m_ColumnSize;j++){
       m_mat[i][j] = fMat[i][j];
     }
   }
 }

void Matrix::SetTranslation(double Tx,double Ty,double Tz){
  if(m_RowSize != 3 || m_ColumnSize != 1) cout << "error not a 3*1 matrix !" << endl;
  cout << "Matrix::SetTranslation" << endl;
  cout << m_RowSize << "\t" << m_ColumnSize << endl;
  m_mat[0][0] = Tx;
  m_mat[1][0] = Ty;
  m_mat[2][0] = Tz;
  cout << "end Matri::SetTranslation" << endl;
}

void Matrix::SetRotation(double phi,double theta,double psi){
  if(m_RowSize != 3 || m_ColumnSize != 3) cout << "error not a 3*3 matrix !" << endl;
  
  m_mat[0][0] = cos(theta) * cos(psi);
  m_mat[0][1] = cos(phi) * sin(psi) + sin(phi) * sin(theta) * cos(psi);
  m_mat[0][2] = sin(phi) * sin(psi) + cos(phi) * sin(theta) * cos(psi);
  m_mat[1][0] = cos(theta) * sin(psi);
  m_mat[1][1] = cos(phi) * cos(psi) + sin(phi) * sin(theta) * sin(psi);
  m_mat[1][2] = -sin(phi) * cos(psi) + cos(phi) * sin(theta) * sin(psi);
  m_mat[2][0] = -sin(theta);
  m_mat[2][1] = sin(phi) * cos(theta);
  m_mat[2][2] = cos(phi) * cos(theta);
}


// Matrix* Matrix::LeftMultiply(Matrix* fMat){
//   if(m_ColumnSize != fMat -> GetNRows()){ cout << "bad number of column and row !" << endl; exit(-1);}
  
//   for(int i = 0;i<m_RowSize;i++){
    
//   }
// }


void Matrix::Print(){
  cout << "Matrix is : " << endl << endl;
  for(int i = 0;i<m_RowSize;i++){
    for(int j = 0;j<m_ColumnSize;j++) cout << m_mat[i][j] << "\t";
    cout << endl;
  }
}

double Matrix::Get(int i,int j){
  if(i > m_RowSize-1){
    cout << i << " bigger than row size (" << m_RowSize << ")" << endl;
    exit(-1);
  }

  if(j > m_ColumnSize-1){
    cout << i << " bigger than row size (" << m_RowSize << ")" << endl;
    exit(-1);
  }

  return m_mat[i][j];
}
