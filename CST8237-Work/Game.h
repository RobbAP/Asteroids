#pragma once

#include "GameEngine.h"
#include "Asteroid.h"

class Game: public GameEngine
{
  friend class GameEngine;

protected:
  Game();

  void InitializeImpl();
  void UpdateImpl(float dt);
  void DrawImpl(SDL_Renderer *renderer, float dt);
  bool checkCollision(Vector2 asteroid, Vector2 otherObject);

  // The player
  Player _player;
  // The asteroid array default 10
  Asteroid _asteroids[MAXASTEROIDS];
};