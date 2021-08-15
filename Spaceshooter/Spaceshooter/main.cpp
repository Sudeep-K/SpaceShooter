#include "Game.h"
#include <time.h>
#include "Menu.h"

int main() {
    /*initializing random seed with time*/
    std::srand(static_cast<unsigned>(time(NULL)));

    /*plays background music*/
    //Music music;
    //music.openFromFile("Audios/theme.wav");
    //music.play();

    Game game;

    RenderWindow window(VideoMode(1200, 600), "Space shooter");
    Texture texture;

    if (!texture.loadFromFile("Textures/menu.png"))
    {
        cout << "load failed" << endl;
        system("pause");
    }

    Sprite sprite;
    sprite.setTexture(texture);

    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;

                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;

                case sf::Keyboard::Return:
                    switch (menu.GetPressedItem())
                    {
                    case 0:
                        window.close();
                        game.run();
                        break;
                    case 1:
                        window.close();
                        break;
                    }
                    break;
                }
                break;
            case sf::Event::Closed:
                window.close();

                break;
            }
        }
        window.clear();
        window.draw(sprite);
        menu.draw(window);
        window.display();
    }
}
