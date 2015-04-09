#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <iostream>
#include <math.h>
#include "Point3D.h"


class Point3D;

class Matrix{
 private:
  int m_RowSize;
  int m_ColumnSize;
  double **m_mat;

 public:
  Matrix(int fRowSize,int fColumn,double **fMat = NULL);
  Matrix(int fRowAndColumnSize,double **fMat = NULL);
  static Matrix* RotationMatrix(double phi = 0,double theta = 0,double psi = 0);
  static Matrix* TranslationMatrix(double Tx = 0,double Ty = 0,double Tz = 0);
  static Matrix* ScalingMatrix(double Sx = 0,double Sy = 0,double Sz = 0);

  void SetTranslation(double Tx,double Ty,double Tz);
  void SetRotation(double Tx,double Ty,double Tz);
  void Print(const char* str = NULL);
  double Get(int i,int j);
  Matrix& operator*=(Matrix mat);
  Matrix* operator*(Matrix mat);
  Point3D* operator*(Point3D p);
  void Init();

 private:
  void Init(int fRowSize,int fColumn);
  void SetArray(double **fMat);

};

#endif
