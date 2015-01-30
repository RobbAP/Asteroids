#include "bullet.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

Bullet::Bullet() : GameObject()
{

}

Bullet::~Bullet()
{
}

// Bullet initialize function
void Bullet::Initialize()
{
	ttl = 1000;
	endPointOffset = { sinf(rotation), -cosf(rotation) };
}

// Bullet update function, updates the bullets position while its time to live is greater than 0
void Bullet::Update(float dt)
{
	if (ttl > 0)
	{
		bullet.x += endPointOffset.x;
		bullet.y += endPointOffset.y;

		// Screen wrap
		if (bullet.x > 640)
			bullet.x = 0;
		if (bullet.x < 0)
			bullet.x = 640;
		if (bullet.y > 640)
			bullet.y = 0;
		if (bullet.y < 0)
			bullet.y = 640;

		ttl -= dt;
	}
	else
	{
		bullet.x = -200;
		bullet.y = -200;
	}
}

// Bullet draw function
void Bullet::Draw(SDL_Renderer *renderer, float dt)
{
	if (ttl > 0)
	{
		SDL_RenderDrawLine(renderer, bullet.x, bullet.y, endPointOffset.x + bullet.x, endPointOffset.y + bullet.y);

	}
}

// Sets the bullets rotation
void Bullet::setRotation(float r)
{
	this->rotation = r;
}

// Sets the bullets origin(The ship)
void Bullet::setOrigin(Vector2 o)
{
	this->bullet = o;
}