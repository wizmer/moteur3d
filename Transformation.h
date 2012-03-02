#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

class Transformation{
 public:
  double m_rot[3][3];
  double m_trans[3];
  double m_scale;
  Transformation(double **fRot,double *fTranslation, double fScale);
};

#endif
