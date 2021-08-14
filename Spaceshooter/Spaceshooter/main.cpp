#include "Game.h"
#include <time.h>

int main() {
	/*initializing random seed with time*/
	std::srand(static_cast<unsigned>(time(NULL)));

	/*plays background music*/
	//Music music;
	//music.openFromFile("Audios/theme.wav");
	//music.play();

	Game game;
	game.run();
}