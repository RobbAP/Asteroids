#include "Asteroid.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Asteroid::Asteroid() : GameObject()
{
	
}

Asteroid::~Asteroid()
{
}

// Initialize an Asteroid with random dimensions and speed
void Asteroid::Initialize()
{
	isAlive = true;
	asteroid.x = ((rand() * 640) / RAND_MAX);
	asteroid.y = ((rand() * 640) / RAND_MAX);
	endPointOffsetA = { rand() % 10, rand() % 10 };
	endPointOffsetB = { rand() % 10, -rand() % 10 };
	endPointOffsetC = { -rand() % 10, -rand() % 10 };
	endPointOffsetD = { -rand() % 10, rand() % 10 };
	velocity = { rand() % 25 -20, rand() % 25 - 20 };
}

// Asteroid update function. If the asteroid isn't dead, recalculate its position otherwise move it off the screen
void Asteroid::Update(float dt)
{
	if (isAlive)
	{
		asteroid.x += velocity.x*dt;
		asteroid.y += velocity.y*dt;

		// If the asteroid goes out of the screen bounds, wrap it.
		if (asteroid.x > 645)
			asteroid.x = 0;
		if (asteroid.x < -5)
			asteroid.x = 640;
		if (asteroid.y > 645)
			asteroid.y = 0;
		if (asteroid.y < -5)
			asteroid.y = 640;
	}
	else
	{
		asteroid.x = -250;
		asteroid.y = -250;
	}
}

// Asteroid draw function used to re draw the asteroid after it's position has been recalculated, only happens if the asteroid is alive.
void Asteroid::Draw(SDL_Renderer *renderer, float dt)
{
	if (isAlive)
	{
		transformedEndPointA = { asteroid.x + endPointOffsetA.x, asteroid.y + endPointOffsetA.y };
		transformedEndPointB = { asteroid.x + endPointOffsetB.x, asteroid.y + endPointOffsetB.y };
		transformedEndPointC = { asteroid.x + endPointOffsetC.x, asteroid.y + endPointOffsetC.y };
		transformedEndPointD = { asteroid.x + endPointOffsetD.x, asteroid.y + endPointOffsetD.y };

		SDL_RenderDrawLine(renderer, transformedEndPointA.x, transformedEndPointA.y, transformedEndPointB.x, transformedEndPointB.y);
		SDL_RenderDrawLine(renderer, transformedEndPointB.x, transformedEndPointB.y, transformedEndPointC.x, transformedEndPointC.y);
		SDL_RenderDrawLine(renderer, transformedEndPointC.x, transformedEndPointC.y, transformedEndPointD.x, transformedEndPointD.y);
		SDL_RenderDrawLine(renderer, transformedEndPointD.x, transformedEndPointD.y, transformedEndPointA.x, transformedEndPointA.y);
	}
}