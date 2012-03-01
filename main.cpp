#include "WorldManager.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
  WorldManager* TheWorldManager = WorldManager::CreateWorldManager();
  GeomObject* obj = new GeomObject("Cube.txt");
  WorldObject* WObj = new WorldObject(obj);
  TheWorldManager->AddWorldObject(WObj);
  return 1;
}
