#ifndef KEYHANDLER_H
#define KEYHANDLER_H
#include "TGFrame.h"
#include "TPad.h"
#include <TRootCanvas.h>
#include <KeySymbols.h>
#include "ProjPolygone.h"
#include "TClass.h"

#include <iostream>

#include "Camera.h"

class KeyHandler : public TGFrame {

public:
  KeyHandler(Camera* fCam,TPad* fBoard,ProjPolygone* pol);
   TPad* Board;
   Camera* Pos;
   ProjPolygone* Pol;
   ~KeyHandler();

   Bool_t HandleKey(Event_t *event);    // handler of the key events
};

#endif

