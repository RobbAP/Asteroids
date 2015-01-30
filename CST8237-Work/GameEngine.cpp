#include "GameEngine.h"
#include <SDL.h>
#include "MathUtils.h"

GameEngine::GameEngine()
{
	_score = 0.0f;
	_lives = STARTINGLIVES;
}

GameEngine::~GameEngine()
{

}

void GameEngine::Initialize()
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  //title = new char[_title.length() + 1];
  //strncpy(title, _title.c_str(), _title.length());
  //title[_title.length()] = '\0';

  _window = SDL_CreateWindow("ASTEROIDS",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    SCREENWIDTH, SCREENHEIGHT,
    SDL_WINDOW_SHOWN);

  //imagenames[0] = { "starfield.gif" };
  
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

  //planes[0] = IMG_Load(imagenames[0]);

  InitializeImpl();

  /* Get the time at the beginning of our game loop so that we can track the
  * elapsed difference. */
  _engineTimer.Start();
}

void GameEngine::Shutdown()
{
  _engineTimer.Stop();

  SDL_DestroyRenderer(_renderer);
  SDL_DestroyWindow(_window);
}

void GameEngine::Update()
{
  // Calculating the time difference since our last loop.
  _engineTimer.Update();
  updateTitle();
  UpdateImpl(_engineTimer.GetDeltaTime());
}

void GameEngine::Draw()
{
  // Set the draw colour for screen clearing.
  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

  // Clear the renderer with the current draw colour.
  SDL_RenderClear(_renderer);

  DrawImpl(_renderer, _engineTimer.GetDeltaTime());

  // Present what is in our renderer to our window.
  SDL_RenderPresent(_renderer);
}

void GameEngine::updateTitle()
{
	// Add the default life count and score to the window's title bar
	sprintf(buffer, "AsteROIDS \t - \t Lives: %i \t\t - \t\t Score: %.2f", _lives, _score);
	SDL_SetWindowTitle(_window, buffer);      
}