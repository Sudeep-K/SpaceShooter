#include "Asteroid.h"

void Asteroid::initVariables()
{
	this->healthMax=1;
	this->health = this->healthMax;
	this->damage=1;
}

Asteroid::Asteroid(Texture* texture, float pos_x, float pos_y, unsigned points)
{
	/*set the point count for out asteroid*/
	this->points = points;

	/*configure the sprite of Asteroid*/
	this->asteroidSprite.setTexture(*texture);
	this->asteroidSprite.setOrigin((this->asteroidSprite.getGlobalBounds().left + this->asteroidSprite.getGlobalBounds().width) / 2.f, (this->asteroidSprite.getGlobalBounds().top + this->asteroidSprite.getGlobalBounds().height) / 2.f);
	this->asteroidSprite.setPosition(pos_x, pos_y);
	this->asteroidSprite.scale(1.25f,1.f);
	

	/*constructor for Asteroid class*/
	this->initVariables();
}

Asteroid::~Asteroid()
{
	/*destrutor for Asteroid class*/
}

const FloatRect Asteroid::getbounds() const
{
	return this->asteroidSprite.getGlobalBounds();
}

const unsigned& Asteroid::getPoints() const
{
	return this->points;
}

void Asteroid::update()
{
	/*checks for event of the asteroid*/
	this->asteroidSprite.move(-2.f,0.f);
}

void Asteroid::render(RenderTarget* target)
{
	target->draw(this->asteroidSprite);
}
