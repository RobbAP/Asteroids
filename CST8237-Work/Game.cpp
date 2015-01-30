#include "Game.h"
#include "InputManager.h"
#include <SDL.h>
#include <math.h>
#include <time.h>

// Initializing our static member pointer.
GameEngine* GameEngine::_instance = nullptr;

GameEngine* GameEngine::CreateInstance()
{
  if (_instance == nullptr)
  {
    _instance = new Game();
  }
  return _instance;
}

// Constructor
Game::Game() : GameEngine()
{
}

// Main Initialize problem
void Game::InitializeImpl()
{
	srand(time(NULL));
  _player.Initialize();
  for (int i = 0; i < MAXASTEROIDS; i++)
  {
	  _asteroids[i].Initialize();
  }
}

// Main update function
void Game::UpdateImpl(float dt)
{
	InputManager *im = InputManager::GetInstance();
	im->Update(dt);

	// UP ARROW
	if (im->IsKeyDown(SDLK_UP) == true)
	{
		_player.velocity.x += (sinf(_player.rotationRadians)*dt*_player.rateOfAcc);
		_player.velocity.y -= (cosf(_player.rotationRadians)*dt*_player.rateOfAcc);
	}
	// RIGHT ARROW
	if (im->IsKeyDown(SDLK_RIGHT) == true)
	{
		_player.rotationDegrees += (_player.rotationSpeed * dt);
	}
	// LEFT ARROW
	if (im->IsKeyDown(SDLK_LEFT) == true)
	{
		_player.rotationDegrees -= (_player.rotationSpeed * dt);
	}
	// UP ARROW released which slows the ship slowly
	if (im->IsKeyDown(SDLK_UP) == false)
	{
		_player.velocity.x *= _player.friction;
		_player.velocity.y *= _player.friction;
	}
	// SPACE KEY 
	if (im->IsKeyDown(SDLK_SPACE) == true && _player.shoot == false)
	{
		_player.shoot = true;
	}
	else if (im->IsKeyDown(SDLK_SPACE) == false)
	{
		_player.shoot = false;
		_player.shootDown = true;
	}

	// Update the player
	_player.Update(dt);
	// Update the asteroids
	for (int i = 0; i < MAXASTEROIDS; i++)
		_asteroids[i].Update(dt);	
	
	// Check for player collision with asteroids
	for (int j = 0; j < MAXASTEROIDS; j++)
	{
		if (checkCollision(_player.ship, _asteroids[j].asteroid))
		{
			_lives--;
			_player.Initialize();
			_asteroids[j].isAlive = false;
			_score += 100;
		}
	}

	// Check if bullets hit
	for (int k = 0; k < MAXASTEROIDS; k++)
	{
		for (int l = 0; l < MAXBULLETS; l++)
		{
			if (checkCollision(_asteroids[k].asteroid, _player.bullet[l].bullet))
			{
				_asteroids[k].isAlive = false;
				_score += 200;
				_player.hits++;
			}
		}
	}

	if (_lives < 1 || _player.hits > 9)
	{
		_lives = 5;
		_score = 0;
		InitializeImpl();
	}

}

// Main Draw Function
void Game::DrawImpl(SDL_Renderer *renderer, float dt)
{
  // Set the draw colour for our point.
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  
  // Draw the point.
  _player.Draw(renderer, dt);
  for (int i = 0; i < MAXASTEROIDS; i++)
  _asteroids[i].Draw(renderer, dt);
}

// Check for asteroid collision, I've set the asteroids to have a 10x10 hitbox
bool Game::checkCollision(Vector2 asteroid, Vector2 otherObject)
{
	if ((abs(asteroid.x - otherObject.x) < 10) && (abs(asteroid.y - otherObject.y) < 10))
	{
		return true;
	}
	return false;
}