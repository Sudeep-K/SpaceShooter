#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;
using namespace std;

#define MAX_NUMBER_OF_ITEMS 2

class Menu
{
public:
    Menu(float width, float height);

    void draw(RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }

    ~Menu();

private:
    int selectedItemIndex;
    Font font;
    Text menu[MAX_NUMBER_OF_ITEMS];
};

