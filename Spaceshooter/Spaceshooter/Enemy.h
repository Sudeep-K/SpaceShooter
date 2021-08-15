#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;
class Enemy
{
private:
	int healthMax;
	unsigned points;
	float attackCooldown;
	float attackCooldownMax;
private:
	void initVariables();
public:
	Sprite enemySprite;

	int health;
	int damage;
	/*vector difference between player and enemy*/
	float dx = 0.f;
	float dy = 0.f;
	float rotation = 0.f;
	Vector2f normalizedVector;
public:
	Enemy(Texture* texture, float pos_x, float pos_y);
	~Enemy();

	/*Accessor functions*/
	const FloatRect getbounds() const;
	const unsigned& getPoints() const;
	const bool canPlayerAttack();
	void updateAttackCooldown();


	void updateEnemyNormalizedVector();

	void update();
	void render(RenderTarget* target);
};

