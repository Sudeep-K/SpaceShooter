#include "Bullet.h"

Bullet::Bullet(Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y, float bulletSpeed, float rotation)
{
	this->shapeBullet.setTexture(*texture);
	this->shapeBullet.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->shapeBullet.setRotation(rotation + 180);
	this->bulletSpeed = bulletSpeed;
}

Bullet::~Bullet()
{
}

const FloatRect Bullet::getBounds() const
{
	return this->shapeBullet.getGlobalBounds();
}

void Bullet::update()
{
	this->shapeBullet.move(this->bulletSpeed * this->direction);
}

void Bullet::render(RenderTarget* target)
{
	target->draw(this->shapeBullet);
}
