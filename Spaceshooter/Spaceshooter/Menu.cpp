#include <iostream>
#include "Menu.h"

Menu::Menu(float width, float height)
{

    /*Main menu font*/
    if (!font.loadFromFile("Fonts/Pixeboy-z8XGD.ttf"))
    {
        // handle error
    }

    menu[0].setFont(font);
    menu[0].setFillColor(Color::Green);
    menu[0].setCharacterSize(50);
    menu[0].setStyle(Text::Bold);
    menu[0].setString("Initiate Millenium falcon");
    menu[0].setPosition(Vector2f(350, 300));

    menu[1].setFont(font);
    menu[1].setFillColor(Color::White);
    menu[1].setCharacterSize(50);
    menu[1].setStyle(Text::Bold);

    menu[1].setString("Quit");
    menu[1].setPosition(Vector2f(550, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    selectedItemIndex = 0;
}


Menu::~Menu()
{
}
void Menu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
}

void Menu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color::Green);
    }
}

void Menu::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color::Green);
    }
}
