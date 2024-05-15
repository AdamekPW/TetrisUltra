#pragma once

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Shapes.h"
#include <string>
#include <sstream>

class Menu : Board
{
private:
    std::vector<Shapes*> ListOfShapes;

public:
    bool ShowShadowContest;
    int Volume;
    Menu();
    sf::RectangleShape Button(int Width, int Height, int x, int y);

    void MenuLoop(int *GameOrMenu, sf::RenderWindow &window);
    
    
};

