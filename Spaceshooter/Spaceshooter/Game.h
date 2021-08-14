#pragma once
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include <map>
#include <string>
#include <sstream>
#include <vector>

class Game
{
private:
	RenderWindow* window;

	/*Resources*/
	map<string, Texture*> textures;
	vector<Bullet*> bullets;

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
public:
	/*constructor and destructor*/
	Game();
	~Game();

	/*functions for game logic*/
	void updatePollEvents();

	void updateNormalisedVector();
	void updatePlayerRotation();
	void updatePlayerInput();
	void updatePlayerBoundary();
	
	void updateBullets();
	void updateAsteroidsAndBullets();
	
	void updateGUI();

	void renderGUI();

	void run();
	void update();
	void render();
};

