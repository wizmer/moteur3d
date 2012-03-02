#include "Transformation.h"

Transformation::Transformation(double **fRot,double *fTranslation, double fScale){
  m_scale = fScale;
  for(int i = 0;i<3;i++){
    if(fRot) for(int j = 0;j<3;j++) m_rot[i][j] = fRot[i][j];
    else {
      for(int j = 0;j<3;j++){
	if(i==j) m_rot[i][j] = 1;
	else m_rot[i][j] = 0;
      }
    }
    if(fTranslation) m_trans[i] = fTranslation[i];
    else m_trans[i] = 0;
  }
}


