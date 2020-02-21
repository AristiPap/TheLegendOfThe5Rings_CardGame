#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <list>
#include <functional>
#include "DeckBuilder.hpp"
#include "Player.hpp"
#include "Gameplay.hpp"
#include "Colours.hpp"

class Gameboard
{
private:
    std::list<Player *>* players;
    unsigned int playersNumber;
public:
    Gameboard();//default cosntructor
    ~Gameboard();
    void initializeGameboard(void);
    void printGameStatistics(void);
    void gameplay(void);
};

