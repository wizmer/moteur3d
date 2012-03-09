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

void Matrix::Init(){
  if(m_ColumnSize == m_RowSize){
    for(int i = 0;i<m_RowSize;i++){
      for(int j = 0;j<m_ColumnSize;j++){
	if(i == j) m_mat[i][j] = 1;
	else m_mat[i][j] = 0;
      }
    }
  }
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
  cout << "SetTranslation" << endl;
  if(m_ColumnSize != 4 || m_RowSize != 4){
    cout << "error not a 4*4 matrix" << endl;
    exit(-1);
  }

  m_mat[0][0] = 1;
  m_mat[0][1] = 0;
  m_mat[0][2] = 0;
  m_mat[0][3] = Tx;

  m_mat[1][0] = 0;
  m_mat[1][1] = 1;
  m_mat[1][2] = 0;
  m_mat[1][3] = Ty;

  m_mat[2][0] = 0;
  m_mat[2][1] = 0;
  m_mat[2][2] = 1;
  m_mat[2][3] = Tz;

  m_mat[3][0] = 0;
  m_mat[3][1] = 0;
  m_mat[3][2] = 0;
  m_mat[3][3] = 1;
  cout << "end Matri::SetTranslation" << endl;
}

void Matrix::SetRotation(double Rx,double Ry,double Rz){
  if(m_ColumnSize != 4 || m_RowSize != 4){
    cout << "error not a 4*4 matrix" << endl;
    exit(-1);
  }

  double phi = Rz;
  double tau = Rx;
  m_mat[0][0] = cos(phi);
  m_mat[0][1] = - sin(phi);
  m_mat[0][2] = 0;
  m_mat[0][3] = 0;

  m_mat[1][0] = cos(tau) * sin(phi);
  m_mat[1][1] = cos(tau) * cos(phi);
  m_mat[1][2] = - sin(tau);
  m_mat[1][3] = 0;

  m_mat[2][0] = sin(phi) * sin(tau);
  m_mat[2][1] = sin(tau) * cos(phi);
  m_mat[2][2] = cos(tau);
  m_mat[2][3] = 0;

  m_mat[3][0] = 0;
  m_mat[3][1] = 0;
  m_mat[3][2] = 0;
  m_mat[3][3] = 1;
}

Matrix* Matrix::RotationMatrix(double phi,double theta,double psi){
  Matrix* mat = new Matrix(4);
  mat -> SetRotation(phi,theta,psi);
  return mat;
}

Matrix* Matrix::TranslationMatrix(double Tx,double Ty,double Tz){
  Matrix* mat = new Matrix(4);
  mat -> SetTranslation(Tx,Ty,Tz);
  return mat;
}

Matrix* Matrix::ScalingMatrix(double Sx,double Sy,double Sz){
  double **array = new double*[4];
  for(int i = 0;i<4;i++) array[i] = new double[4];
  array[0][0] = Sx;
  array[0][1] = 0;
  array[0][2] = 0;
  array[0][3] = 0;

  array[1][0] = 0;
  array[1][1] = Sy;
  array[1][2] = 0;
  array[1][3] = 0;

  array[2][0] = 0;
  array[2][1] = 0;
  array[2][2] = Sz;
  array[2][3] = 0;

  array[3][0] = 0;
  array[3][1] = 0;
  array[3][2] = 0;
  array[3][3] = 1;

  Matrix* mat = new Matrix(4,array);
  
  for(int i = 0;i<4;i++) delete array[i];
  delete[] array;
  return mat;
}


// Matrix* Matrix::LeftMultiply(Matrix* fMat){
//   if(m_ColumnSize != fMat -> GetNRows()){ cout << "bad number of column and row !" << endl; exit(-1);}
  
//   for(int i = 0;i<m_RowSize;i++){
    
//   }
// }


void Matrix::Print(const char* str){
  if(str) cout << str << " ";
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

Matrix& Matrix::operator*=(Matrix mat){
  
  if(m_ColumnSize != mat.m_ColumnSize || m_RowSize != mat.m_RowSize ){
    cout << "Bad number of row or column" << endl;
    exit(-1);
  }
  
  double *array = new double[m_ColumnSize*m_RowSize];
  for(int i = 0;i<m_RowSize;i++){
    for(int j = 0;j<mat.m_ColumnSize;j++){
      array[i*m_ColumnSize + j] = 0;
      for(int k = 0;k<m_ColumnSize;k++) array[i*m_ColumnSize + j] += m_mat[i][k] * mat.Get(k,j);
    }
  }

  for(int i = 0;i<m_RowSize;i++) for(int j = 0;j<m_ColumnSize;j++) m_mat[i][j] = array[i*m_ColumnSize + j];
  
  return *this;
}

Matrix* Matrix::operator*(Matrix mat){
  
  if(m_ColumnSize != mat.m_ColumnSize || m_RowSize != mat.m_RowSize ){
    cout << "Bad number of row or column" << endl;
    exit(-1);
  }
  
  double **array = new double*[m_RowSize];
  for(int i = 0;i<m_RowSize;i++){
    array[i] = new double[m_ColumnSize];
    for(int j = 0;j<mat.m_ColumnSize;j++){
      array[i][j] = 0;
      for(int k = 0;k<m_ColumnSize;k++) array[i][j] += m_mat[i][k] * mat.Get(k,j);
    }
  }

  Matrix* OutMatrix = new Matrix(m_ColumnSize,array);
  for(int i = 0;i<m_RowSize;i++) delete array[i];
  delete[] array;

  return OutMatrix;
}


Point3D* Matrix::operator*(Point3D p){
  
  if(m_ColumnSize !=  4){
    cout << "Bad number of row or column in operator*" << endl;
    exit(-1);
  }

  double x = 0,y = 0, z = 0;
  for(int i = 0;i<3;i++){
    x += m_mat[0][i] * p.Get(i);
    y += m_mat[1][i] * p.Get(i);
    z += m_mat[2][i] * p.Get(i);
  }
  
  // Add translation
  x += m_mat[0][3];
  y += m_mat[1][3];
  z += m_mat[2][3];

  return new Point3D(x,y,z);
}
