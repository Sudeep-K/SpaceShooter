#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;

class Asteroid
{
private:
	int health;
	int healthMax;
	int damage;
	unsigned points;
private:
	void initVariables();
public:
	Sprite asteroidSprite;
public:
	Asteroid(Texture* texture, float pos_x, float pos_y, unsigned points);
	~Asteroid();

	/*Accessor functions*/
	const FloatRect getbounds() const;
	const unsigned& getPoints() const;

	void update();
	void render(RenderTarget* target);
};

