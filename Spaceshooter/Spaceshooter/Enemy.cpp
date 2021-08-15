#include "Enemy.h"

void Enemy::initVariables()
{
	this->healthMax = 3;
	this->health = this->healthMax;
	this->damage = 1;
	this->points = 500;

	/*bullet shooting cooldown*/
	this->attackCooldownMax = 20.f;
	this->attackCooldown = this->attackCooldownMax;
}

Enemy::Enemy(Texture* texture, float pos_x, float pos_y)
{
	/*constructor for Enemy class*/
	this->initVariables();

	/*sets texture of enemy*/
	this->enemySprite.setTexture(*texture);
	/*resets origin of enemy to its center*/
	this->enemySprite.setOrigin((enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width) / 2.f,
		(enemySprite.getGlobalBounds().top + enemySprite.getGlobalBounds().height) / 2.f);
	this->enemySprite.setPosition(pos_x, pos_y);


}

Enemy::~Enemy()
{
	/*destructor for enemy class*/
}

const FloatRect Enemy::getbounds() const
{
	return this->enemySprite.getGlobalBounds();
}

const unsigned& Enemy::getPoints() const
{
	return this->points;
}

const bool Enemy::canPlayerAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Enemy::updateAttackCooldown()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 1.f;
}

void Enemy::updateEnemyNormalizedVector()
{
	this->normalizedVector = Vector2f(dx / sqrt(pow(dx, 2) + pow(dx, 2)), dy / sqrt(pow(dx, 2) + pow(dx, 2)));
}

void Enemy::update()
{
	/*checks for movement in enemy*/
	this->updateEnemyNormalizedVector();
	this->updateAttackCooldown();
}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->enemySprite);
}
