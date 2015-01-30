#pragma once 

#include "MathUtils.h"
#include "GameObject.h"
#include <SDL.h>

#define MAXASTEROIDS 1

struct SDL_Renderer;

class Asteroid : public GameObject
{
public:
	void Initialize();

	void Update(float dt);
	void Draw(SDL_Renderer *renderer, float dt);

	// True if the asteroid is alive
	bool isAlive;

	// Asteroids x,y position
	Vector2 asteroid;

	// Asteroids velocity which is random
	Vector2 velocity;

	// Asteroids are quadrilaterals connected by 4 points 
	Vector2 endPointOffsetA;
	Vector2 endPointOffsetB;
	Vector2 endPointOffsetC;
	Vector2 endPointOffsetD;

	// Endpoints used to re-calculate an asteroids position 
	Vector2 transformedEndPointA;
	Vector2 transformedEndPointB;
	Vector2 transformedEndPointC;
	Vector2 transformedEndPointD;

	~Asteroid();
	Asteroid();
protected:
	Transform _transform;
};