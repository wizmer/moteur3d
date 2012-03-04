#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <math.h>

class Matrix{
 private:
  int m_RowSize;
  int m_ColumnSize;
  double **m_mat;

 public:
  Matrix(int fRowSize,int fColumn,double **fMat = NULL);
  Matrix(int fRowAndColumnSize,double **fMat = NULL);
  void SetRotation(double phi,double theta,double psi);
  void SetTranslation(double Tx,double Ty,double Tz);
  void Print();
  double Get(int i,int j);

 private:
  void Init(int fRowSize,int fColumn);
  void SetArray(double **fMat);

};

#endif
