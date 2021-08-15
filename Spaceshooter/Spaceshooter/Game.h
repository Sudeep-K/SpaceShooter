#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Enemy.h"
#include <map>
#include <string>
#include <sstream>
#include <vector>

class Game
{
private:
	RenderWindow* window;

	/*clock*/
	Clock clock;
	Clock enemyclock;

	/*Resources*/
	map<string, Texture*> textures;
	vector<Bullet*> bullets;
	vector<Bullet*> enemyBullets;

	/*background*/
	Texture backgroundTexture;
	Sprite backgroundSprite;

	/*fonts*/
	Font font;
	Text text;
	Text gameOverText;

	/*audio files*/
	SoundBuffer bulletBuffer;
	Sound bulletSound;
	SoundBuffer oofBuffer;
	Sound oofSound;
	SoundBuffer explosionBuffer;
	Sound explosionSound;

	/*system*/
	unsigned points;

	/*Player initialization*/
	Player* player;

	/*Asteroid initialization*/
	float spawnTimer;
	float spawnTimerMax;
	vector<Asteroid*> asteroids;
	Asteroid* asteroid;

	/*Enemy initialization*/
	vector<Enemy*> enemies;
	Enemy* enemy;
	int maxEnemies = 4;

	/*vector difference between player and mouse cursor*/
	float dx = 0.f;
	float dy = 0.f;
	float rotation = 0.f;
	Vector2f normalizedVector;

private:
	void initWindow();

	void initBackground();
	void initMediafiles();
	void initTextures();
	void initGUI();
	void initSystems();
	void initPlayer();
	void initAsteroid();
	void initEnemy();
public:
	/*constructor and destructor*/
	Game();
	~Game();

	/*functions for game logic*/
	void updatePollEvents();

	void updateNormalisedVector();
	void updatePlayerRotation();
	void updateEnemiesRotation();
	void updatePlayerInput();
	void updatePlayerBoundary();
	
	void updateBullets();
	void updateAsteroidsAndBullets();

	void updateEnemyBulletBoundary();
	void updateEnemyBullets();
	void updateEnemiesAndBullets();

	void updateBulletCollision();
	
	void updateGUI();

	void renderGUI();

	void run();
	void update();
	void render();
};

