#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;
using namespace std;

class Player
{
private:
	Texture texture;
	float playerSpeed;
	float attackCooldown;
	float attackCooldownMax;
	int health;
	int healthMax;

private:
	void initVariables();
	void initTexture();
	void initSprite();
public:
	Sprite sprite;
public:
	Player();
	~Player();

	/*accessor function*/
	const Vector2f& getPosition() const;
	const FloatRect getbounds() const;
	const int& getHp() const;
	void loseHp(const int value);

	/*modifier function*/
	void setPlayerPosition(const float x, const float y);

	const bool canPlayerAttack();
	void updateAttackCooldown();

	void movePlayer(const float, const float);
	void update();
	void render(RenderTarget& target);
};

