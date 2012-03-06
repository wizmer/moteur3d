#include "KeyHandler.h"

using namespace std;

///////////////////////////////////////////////////////////////////
//  KeyHandler - virtual frame used to catch and handle key events
///////////////////////////////////////////////////////////////////
KeyHandler::KeyHandler(Camera* fCam,TPad* fBoard) : TGFrame(gClient->GetRoot(),0,0)
{
  // Key handler constructor.
  Pos = fCam;
  Board = fBoard;
  // get main frame of Tetris canvas
  TRootCanvas *main_frame = (TRootCanvas*)(Board->GetCanvasImp());
  // bind arrow keys and space-bar key
  main_frame->BindKey((const TGWindow*)this, gVirtualX->KeysymToKeycode(kKey_Up),    0);
  main_frame->BindKey((const TGWindow*)this, gVirtualX->KeysymToKeycode(kKey_Left),  0);
  main_frame->BindKey((const TGWindow*)this, gVirtualX->KeysymToKeycode(kKey_Right), 0);
  main_frame->BindKey((const TGWindow*)this, gVirtualX->KeysymToKeycode(kKey_Down),  0);

  main_frame->BindKey((const TGWindow*)this, gVirtualX->KeysymToKeycode(kKey_w),    0);
  main_frame->BindKey((const TGWindow*)this, gVirtualX->KeysymToKeycode(kKey_a),  0);
  main_frame->BindKey((const TGWindow*)this, gVirtualX->KeysymToKeycode(kKey_d), 0);
  main_frame->BindKey((const TGWindow*)this, gVirtualX->KeysymToKeycode(kKey_s),  0);

  main_frame->BindKey((const TGWindow*)this, gVirtualX->KeysymToKeycode(kKey_Space), 0);
}


Bool_t KeyHandler::HandleKey(Event_t *event)
{
  // Handle arrow and spacebar keys
  //  cout << "HandleKey : " << event << endl;
  char tmp[2];
  UInt_t keysym;

  gVirtualX->LookupString(event, tmp, sizeof(tmp), keysym);

  if (event->fType == kGKeyPress) {
    // cout << Pos->x <<  "  " << Pos->y << endl;
    // print(Pos->Phi);
    switch ((EKeySym)keysym) {
    case kKey_Left:
      Pos->RotateLeft();
      break;
    case kKey_Right:
      Pos->RotateRight();
      break;
    case kKey_Down:
      Pos->RotateDown();
      break;
    case kKey_Up:
      Pos->RotateUp();
      break;
    case kKey_a:
      Pos->MoveLeft();
      break;
    case kKey_d:
      Pos->MoveRight();
      break;
    case kKey_s:
      Pos->MoveBack();
      break;
    case kKey_w:
      Pos->MoveUp();
      break;
    case kKey_Space:
      //      Pos->Init();
      break;
    default:
      return kTRUE;
    }
    // int N = Obj.size()-1;
    // for(int i = 0;i<N;i++){
    //   Obj[i]->DoTauPhi();
    //   Obj[i]->Draw();
    // }
    
    Pos->Moving();
    int Nboard = Board->GetListOfPrimitives()->GetEntries();
    for(int i = Nboard - 1;i>=0;i--){
      if(strcmp(Board->GetListOfPrimitives()->At(i)->IsA()->GetName(),"TMarker") == 0 || strcmp(Board->GetListOfPrimitives()->At(i)->IsA()->GetName(),"TLine") == 0) {
	delete Board->GetListOfPrimitives()->At(i);
      }
    }
    //    Pol->Update(Pos);
    //    Pol->Plot();
    Scene3D::GetScene3D() -> Project(Pos);
  }
  //  gGo->CurrentStone->Redraw();
  gPad->Update();
  return kTRUE;
}

KeyHandler::~KeyHandler()
{
  // // Cleanup key handler.

  // // get main frame of Tetris canvas
  // TRootCanvas *main_frame = (TRootCanvas*)((gGo->fBoard)->GetCanvasImp());

  // // remove binding of arrow keys and space-bar key
  // main_frame->RemoveBind(this, gVirtualX->KeysymToKeycode(kKey_Up),    0);
  // main_frame->RemoveBind(this, gVirtualX->KeysymToKeycode(kKey_Left),  0);
  // main_frame->RemoveBind(this, gVirtualX->KeysymToKeycode(kKey_Right), 0);
  // main_frame->RemoveBind(this, gVirtualX->KeysymToKeycode(kKey_Down),  0);
  // main_frame->RemoveBind(this, gVirtualX->KeysymToKeycode(kKey_Space), 0);
  // // restore key auto repeat functionality, was turned off in TGMainFrame::HandleKey()
  // gVirtualX->SetKeyAutoRepeat(kTRUE);
}

