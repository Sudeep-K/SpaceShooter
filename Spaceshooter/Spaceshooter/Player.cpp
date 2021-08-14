#include "Player.h"

void Player::initVariables()
{
	this->healthMax = 10;
	this->health = this->healthMax;
	this->playerSpeed = 5.f;

	/*bullet shooting cooldown*/
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
}

void Player::initTexture()
{
	/*loads texture from file*/
	if (!this->texture.loadFromFile("Textures/sokol.png"))
		cout << "Error Player::initTexture couldn't load file" << endl;
}

void Player::initSprite()
{
	/*loads texture to sprite*/
	this->sprite.setTexture(this->texture);
	/*set the origin of sprite to its center*/
	this->sprite.setOrigin((sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) / 2.f,
		(sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) / 2.f);

	this->sprite.setPosition(450.f, 225.f);
	this->sprite.setColor(Color::White);
}

Player::Player()
{
	/*constructor for Player class*/
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{
	/*destructor for Player class*/
}

const Vector2f& Player::getPosition() const
{
	return sprite.getPosition();
}

const FloatRect Player::getbounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->health;
}

void Player::loseHp(const int value)
{
	this->health -= value;
	if (this->health < 0)
		this->health = 0;
}

void Player::setPlayerPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

const bool Player::canPlayerAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax) {
		this->attackCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::updateAttackCooldown()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 1.f;
}

void Player::movePlayer(const float dir_x, const float dir_y)
{
	/*moves the player across the window*/
	this->sprite.move(this->playerSpeed*dir_x, this->playerSpeed * dir_y);
}

void Player::update()
{
	/*checks for any events in window by our character*/
	this->updateAttackCooldown();
}

void Player::render(RenderTarget& target)
{
	/*draws our character to window*/
	target.draw(this->sprite);
}
