#include <iostream>
#include "Game.h"

using namespace std;
bool running = true;

int main(int argc, char** argv)
{
  GameEngine *engine = GameEngine::CreateInstance();
  engine->Initialize();

  // While the console is open for now
  while (running)
  {
    engine->Update();
    engine->Draw();
  }

  engine->Shutdown();

  return 0;
}