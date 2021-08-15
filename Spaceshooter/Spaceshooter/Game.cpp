#include "Game.h"

void Game::initWindow()
{
	/*initializes window using pointer*/
	this->window = new RenderWindow(VideoMode(1200, 600), "Space Shooter");
	this->window->setFramerateLimit(30);
}

void Game::initBackground()
{
	this->backgroundTexture.loadFromFile("Textures/background.png");
	this->backgroundSprite.setTexture(backgroundTexture);
}

void Game::initMediafiles()
{
	/*initializes laser shooting sound*/
	bulletBuffer.loadFromFile("Audios/laser.wav");
	bulletSound.setBuffer(bulletBuffer);

	/*initializes player hitting sound*/
	oofBuffer.loadFromFile("Audios/oof.wav");
	oofSound.setBuffer(oofBuffer);

	/*initializes asteroid hitting sound*/
	explosionBuffer.loadFromFile("Audios/explosion.wav");
	explosionSound.setBuffer(explosionBuffer);
}

void Game::initTextures()
{
	this->textures["ENEMY"] = new Texture();
	this->textures["ENEMY"]->loadFromFile("Textures/enemy.png");

	this->textures["BULLET"] = new Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");

	this->textures["ENEMYBULLET"] = new Texture();
	this->textures["ENEMYBULLET"]->loadFromFile("Textures/enemylaser.png");

	this->textures["SMALLASS"] = new Texture();
	this->textures["SMALLASS"]->loadFromFile("Textures/asteroid-small.png");

	this->textures["NORMALASS"] = new Texture();
	this->textures["NORMALASS"]->loadFromFile("Textures/asteroid-medium.png");

	this->textures["BIGASS"] = new Texture();
	this->textures["BIGASS"]->loadFromFile("Textures/asteroid.png");
	
}

void Game::initGUI()
{
	/*loads font from the file*/
	this->font.loadFromFile("Fonts/Pixeboy-z8XGD.ttf");

	/*sets text*/
	this->text.setFont(this->font);
	this->text.setFillColor(Color::Green);
	this->text.setCharacterSize(20);

	/*sets gameover text*/
	this->gameOverText.setFont(this->font);
	this->gameOverText.setFillColor(Color::White);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setString("Game over");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	/*initializes our player*/
	this->player = new Player();
}

void Game::initAsteroid()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initEnemy()
{
	
}

Game::Game()
{
	/*constructor for Game class*/
	this->initBackground();
	this->initWindow();
	this->initTextures();
	this->initPlayer();
	this->initAsteroid();
	this->initGUI();
	this->initSystems();
	this->initMediafiles();
}

Game::~Game()
{
	/*Destructor for Game class*/
	delete this->window;
	delete this->player;
	
	/*Deletes textures*/
	for (auto& i : this->textures) {
		delete i.second;
	}

	/*Deletes bullets*/
	for (auto* i : this->bullets) {
		delete i;
	}

	/*Deletes asteroids*/
	for (auto* i : this->asteroids) {
		delete i;
	}

	/*Deletes enemies*/
	for (auto* i : this->enemies) {
		delete i;
	}

	/*Deletes enemy bullets*/
	for (auto* i : this->enemyBullets) {
		delete i;
	}
}

void Game::updatePollEvents()
{
	/*checks for any type of events in window*/
	Event event;
	while (this->window->pollEvent(event)) {
		if (event.type == Event::Closed)
			this->window->close();
	}
}

void Game::updateNormalisedVector()
{
	this->normalizedVector = Vector2f(dx / sqrt(pow(dx, 2) + pow(dx, 2)), dy / sqrt(pow(dx, 2) + pow(dx, 2)));
}

void Game::updatePlayerRotation()
{
	/*calculate the current player position*/
	Vector2f currentPlayerPosition;
	currentPlayerPosition.x = this->player->sprite.getGlobalBounds().left;
	currentPlayerPosition.y = this->player->sprite.getGlobalBounds().top;
	/*calculate the current position of mouse*/
	Vector2i mousePosition = Mouse::getPosition(*this->window);

	const float PI = 3.14159265;

	/*vector difference between player and mouse*/
	this->dx = currentPlayerPosition.x - mousePosition.x;
	this->dy = currentPlayerPosition.y - mousePosition.y;
	this->rotation = ((atan2(dy, dx)) * 180 / PI);

	this->player->sprite.setRotation(rotation + 180);
}

void Game::updateEnemiesRotation()
{
	for (int i=0; i < enemies.size(); i++) {
		/*calculate the current enemy position*/
		Vector2f currentEnemyPosition;
		currentEnemyPosition.x = this->enemies[i]->enemySprite.getGlobalBounds().left + this->enemies[i]->enemySprite.getGlobalBounds().width;
		currentEnemyPosition.y = (this->enemies[i]->enemySprite.getGlobalBounds().top + this->enemies[i]->enemySprite.getGlobalBounds().height)/2.0f;
		
		/*calculate the current position of player*/
		Vector2f currentPlayerPosition;
		currentPlayerPosition.x = this->player->sprite.getGlobalBounds().left;
		currentPlayerPosition.y = this->player->sprite.getGlobalBounds().top;

		const float PI = 3.14159265;

		/*vector difference between player and enemy*/
		this->enemies[i]->dx = currentEnemyPosition.x - currentPlayerPosition.x;
		this->enemies[i]->dy = currentEnemyPosition.y - currentPlayerPosition.y;
		this->enemies[i]->rotation = ((atan2(this->enemies[i]->dy, this->enemies[i]->dx)) * 180 / PI);

		this->enemies[i]->enemySprite.setRotation((rotation + 180));
	}
}

void Game::updatePlayerInput()
{
	/*checks for the player movement*/
	if (Keyboard::isKeyPressed(Keyboard::A))
		this->player->movePlayer(-1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::D))
		this->player->movePlayer(1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::W))
		this->player->movePlayer(0.f, -1.f);
	if (Keyboard::isKeyPressed(Keyboard::S))
		this->player->movePlayer(0.f, 1.f);

	/*checks if player shoots bullet*/
	if (Mouse::isButtonPressed(Mouse::Left) && this->player->canPlayerAttack()) {
		this->bulletSound.play();
		this->bullets.push_back(new Bullet(this->textures["BULLET"],
			this->player->getPosition().x,
			this->player->getPosition().y,
			-this->normalizedVector.x,
			-this->normalizedVector.y,
			20.f, this->rotation));
	}
}

void Game::updatePlayerBoundary()
{
	/*updates the position of the player if it crosses windows boundary*/
	//if (this->player->getPosition().x < 0.f)
		//this->player->setPlayerPosition(0.f, this->player->getbounds().top);
	//if (this->player->getPosition().x + this->player->getbounds().width >= this->window->getSize().x)
		//this->player->setPlayerPosition(this->window->getSize().x - this->player->getbounds().width, this->player->getbounds().top);

	//if (this->player->getPosition().y < 0.f)
		//this->player->setPlayerPosition(this->player->getbounds().left, 0.f);
	//if (this->player->getPosition().y + this->player->getbounds().height >= this->window->getSize().y)
		//this->player->setPlayerPosition(this->player->getbounds().left, this->window->getSize().y - this->player->getbounds().height);
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* i : this->bullets) {
		i->update();

		/*Delete the bullet if it goes beyond boundary*/
		if (i->getBounds().left + i->getBounds().width > 1200.f) {
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		else if (i->getBounds().left < 0.f) {
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		else if (i->getBounds().top < 0.f) {
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		else if (i->getBounds().top + i->getBounds().height > 1200.f) {
			delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
		}
		//cout << this->bullets.size() << endl;
		++counter;
	}
}

void Game::updateAsteroidsAndBullets()
{
	/*changes the color of the player back to white after some delay*/
	if (clock.getElapsedTime().asSeconds() > 0.25f) {
		clock.restart();
		this->player->sprite.setColor(Color::White);
	}


	/*spawn random asteroids at random location*/
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax) {
		switch (rand() % 3) {
		case 0:
			/*initializes small asteroid*/
			this->asteroids.push_back(new Asteroid(this->textures["SMALLASS"], 1200.f, rand() % 600 + 1.f, 150));
			break;
		case 1:
			/*initializes medium asteroid*/
			this->asteroids.push_back(new Asteroid(this->textures["NORMALASS"], 1200.f, rand() % 600 + 1.f, 100));
			break;
		case 2:
			/*initializes big asteroid*/
			this->asteroids.push_back(new Asteroid(this->textures["BIGASS"], 1200.f, rand() % +600 + 1.f, 50));
			break;
		}
		this->spawnTimer = 0.f;
	}

	
	for (int i = 0; i < this->asteroids.size(); i++) {
		
		bool asteroid_removed = false;
		this->asteroids[i]->update();
		this->asteroids[i]->asteroidSprite.rotate(1.f);
		
		/*check and remove bullet and enemy if both intersects*/
		for (int k = 0; k < this->bullets.size() && !asteroid_removed; k++) {
			if (this->bullets[k]->getBounds().intersects(this->asteroids[i]->getbounds())) {
				this->explosionSound.play();
				this->points += this->asteroids[i]->getPoints();
				this->bullets.erase(this->bullets.begin() + k);
				this->asteroids.erase(this->asteroids.begin() + i);
				asteroid_removed = true;
			}
		}
		/*to remove the asteroid from left of screen*/
		if (!asteroid_removed) {
			if (this->asteroids[i]->getbounds().left < 0.f) {
				this->asteroids.erase(this->asteroids.begin() + i);
			}
			/*remove asteroid if it touches our player*/
			else if (this->asteroids[i]->getbounds().intersects(this->player->getbounds())) {
				this->oofSound.play();
				this->player->loseHp(1);
				this->asteroids.erase(this->asteroids.begin() + i);
				/*changes the color of player to red to indicate it is hit*/
				clock.restart();
				this->player->sprite.setColor(Color::Red);
			}
		}
	}
	//cout << asteroids.size() << endl;
}

void Game::updateEnemyBulletBoundary()
{
	unsigned counter = 0;
	for (auto* i : this->enemyBullets) {

		/*Delete the bullet if it goes beyond boundary*/
		if (i->getBounds().left + i->getBounds().width > 1200.f) {
			delete this->enemyBullets.at(counter);
			this->enemyBullets.erase(this->enemyBullets.begin() + counter);
			--counter;
		}
		else if (i->getBounds().left < 0.f) {
			delete this->enemyBullets.at(counter);
			this->enemyBullets.erase(this->enemyBullets.begin() + counter);
			--counter;
		}
		else if (i->getBounds().top < 0.f) {
			delete this->enemyBullets.at(counter);
			this->enemyBullets.erase(this->enemyBullets.begin() + counter);
			--counter;
		}
		else if (i->getBounds().top + i->getBounds().height > 1200.f) {
			delete this->enemyBullets.at(counter);
			this->enemyBullets.erase(this->enemyBullets.begin() + counter);
			--counter;
		}
		else if (i->getBounds().intersects(this->player->getbounds())) {

			/*delete enemy bullet and decrease health of player*/
			delete this->enemyBullets.at(counter);
			this->enemyBullets.erase(this->enemyBullets.begin() + counter);
			--counter;

			/*changes color of player to red incase it is hit*/
			this->player->loseHp(1);
			clock.restart();
			this->player->sprite.setColor(Color::Red);
		}
		cout << this->enemyBullets.size() << endl;
		++counter;
	}
}

void Game::updateEnemyBullets()
{
	for (int k = 0; k < enemyBullets.size(); k++) {
		enemyBullets[k]->update();
	}
}

void Game::updateEnemiesAndBullets()
{
	/*spawns new enemies once all four are dead*/
	if (this->enemies.size() <= 0 && (enemyclock.getElapsedTime().asSeconds() > 10.f )) {
		enemyclock.restart();
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], 200.f, 200.f));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], 400.f, 400.f));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], 300.f, 300.f));
		this->enemies.push_back(new Enemy(this->textures["ENEMY"], 250.f, 250.f));
	}
	

	/*rotates enemy in the direction of player*/
	this->updateEnemiesRotation();

	/*checks for each enemy, bullet and player for intersection*/
	for (int i = 0; i < this->enemies.size(); i++) {
		
		/*changes the color of the enemy back to white after some delay*/
		if (clock.getElapsedTime().asSeconds() > 0.25f) {
			clock.restart();
			this->enemies[i]->enemySprite.setColor(Color::White);
		}
		bool enemy_removed = false;
		this->enemies[i]->update();

		/*check and remove bullet and enemy if both intersects*/
		for (int k = 0; k < this->bullets.size() && !enemy_removed; k++) {
			if (this->bullets[k]->getBounds().intersects(this->enemies[i]->getbounds())) {
				if (enemies[i]->health > 0) {
					this->bullets.erase(this->bullets.begin() + k);
					this->enemies[i]->health -= this->enemies[i]->damage;
					/*changes color of enemy to red incase it is hit*/
					clock.restart();
					this->enemies[i]->enemySprite.setColor(Color::Red);
				}
				else if (enemies[i]->health <= 0) {
					/*restart enemy time each time a ship is destoryed*/
					enemyclock.restart();
					this->explosionSound.play();
					this->points += this->enemies[i]->getPoints();
					this->bullets.erase(this->bullets.begin() + k);
					this->enemies.erase(this->enemies.begin() + i);
					enemy_removed = true;
				}
			}
		}
		/*remove enemy if it touches our player*/
		if (!enemy_removed && this->enemies[i]->getbounds().intersects(this->player->getbounds())) {
			this->oofSound.play();
			this->player->loseHp(1);
			this->points += this->enemies[i]->getPoints();
			this->enemies.erase(this->enemies.begin() + i);
			enemy_removed = true;

			/*changes the color of player to red to indicate it is hit*/
			clock.restart();
			this->player->sprite.setColor(Color::Red);
			/*restart enemy time each time a ship is destroyed*/
			enemyclock.restart();
		}
	}

	/*spawn enemy bullets*/
	for (int i = 0; i < this->enemies.size(); i++) {
		if (this->enemies[i]->canPlayerAttack()) {
			this->enemyBullets.push_back(new Bullet(this->textures["ENEMYBULLET"],
				this->enemies[i]->enemySprite.getPosition().x,
				this->enemies[i]->enemySprite.getPosition().y,
				-this->enemies[i]->normalizedVector.x,
				-this->enemies[i]->normalizedVector.y,
				10.f, (this->enemies[i]->rotation)));
		}
	}
}

void Game::updateGUI()
{
	stringstream ss;
	ss << "Points:\t" << this->points <<endl << "Health:\t"<<this->player->getHp();
	this->text.setString(ss.str());
}

void Game::renderGUI()
{
	this->window->draw(this->text);
}

void Game::run()
{
	/*while loop running all game logics here*/
	while(this->window->isOpen())
	{
		this->updatePollEvents();
		if(this->player->getHp() > 0)
			this->update();
		this->render();
	}
}

void Game::update()
{
	this->updatePlayerRotation();
	this->updateNormalisedVector();
	this->updatePlayerInput();
	this->player->update();
	this->updatePlayerBoundary();
	this->updateBullets();
	this->updateAsteroidsAndBullets();
	this->updateEnemiesAndBullets();
	this->updateEnemyBullets();
	this->updateEnemyBulletBoundary();
	this->updateGUI();
}

void Game::render()
{
	/*draws all shapes on windows of different entities*/
	this->window->clear();
	/*render background*/
	this->window->draw(this->backgroundSprite);
	/*renders gameover text*/
	if (this->player->getHp() <= 0)
		this->window->draw(this->gameOverText);

	/*renders bullet*/
	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}
	/*renders enemy bullets*/
	for (auto* enemybullet : this->enemyBullets) {
		enemybullet->render(this->window);
	}
	/*renders player*/
	this->player->render(*this->window);
	/*renders asteroid*/
	for (auto* asteroid : this->asteroids) {
		asteroid->render(this->window);
	}
	/*renders enemies*/
	for (auto* enemy : this->enemies) {
		enemy->render(this->window);
	}
	/*renders GUI text on window*/
	this->renderGUI();
	this->window->display();
}
