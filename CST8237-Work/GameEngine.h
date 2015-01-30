#pragma once // Preprocessor directive to ensure that this header will only be included once. -- Generally used on Windows

// Preprocessor directive to ensure that this header will only be included once. -- Generally used for all environments.
/*#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_

#endif // _GAME_ENGINE_H_*/

#include "MathUtils.h"
#include "Player.h"
#include "Timer.h"
#include <string>

#define SCREENWIDTH 640
#define SCREENHEIGHT 640
#define STARTINGLIVES 5

// Number of images the program needs to load
#define NUMIMAGES 1

// Forward declaring our renderer and window.
// Because we're using them as pointers, we don't need to know their size
// at compile time to define this class.
struct SDL_Renderer;
struct SDL_Window;

class GameEngine
{
public:
  static GameEngine* CreateInstance();

  void Initialize();
  void Shutdown();
  void updateTitle();
  void Update();
  void Draw();

  //const char * imagenames[NUMIMAGES];

  ~GameEngine();

protected:
  GameEngine();

  virtual void InitializeImpl() = 0;
  virtual void UpdateImpl(float dt) = 0;
  virtual void DrawImpl(SDL_Renderer *renderer, float dt) = 0;

  static GameEngine *_instance;

  SDL_Window *_window;
  SDL_Renderer *_renderer;
  Timer _engineTimer;

  // Buffer to update the window text
  char buffer[50];
  // Number of lives default to 5
  int _lives;
  // Player score
  float _score;
  float _oldTime, _currentTime, _deltaTime;
};