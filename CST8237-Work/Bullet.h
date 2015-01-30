#pragma once 

#include "MathUtils.h"
#include "GameObject.h"
#include <SDL.h>

#define MAXBULLETS 10

struct SDL_Renderer;

class Bullet : public GameObject
{
public:
	void Initialize();

	void Update(float dt);
	void Draw(SDL_Renderer *renderer, float dt);
	void setRotation(float v);
	void setOrigin(Vector2 o);
	void initBullets();

	// Time to live (3 seconds)
	int ttl;

	// The bullets x,y position
	Vector2 bullet;

	// The bullets angle
	float rotation;

	// endpoint to draw the bullet as a line
	Vector2 endPointOffset;

	~Bullet();
	Bullet();
protected:
	Transform _transform;
};