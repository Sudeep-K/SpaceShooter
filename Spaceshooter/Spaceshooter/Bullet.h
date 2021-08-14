#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;

class Bullet
{
private:
	Vector2f direction;
	float bulletSpeed;
public:
	Sprite shapeBullet;
public:
	Bullet(Texture* texture,float pos_x, float pos_y, float dir_x, float dir_y, float bulletSpeed, float rotation);
	~Bullet();

	/*Accessor function*/
	const FloatRect getBounds() const;

	void update();
	void render(RenderTarget* target);
};

