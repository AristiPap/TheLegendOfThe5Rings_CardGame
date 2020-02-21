#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <chrono>
#include "Player.hpp"
#include "Gameboard.hpp"
#include "Colours.hpp"

using namespace std;

void startingPhase(Player& player);
void equipPhase(Player& player);
bool battlePhase(Player& attacker,list<Player* >* players,int playersNum);
void economyPhase(Player &player);
void Gameplay(list<Player* >* players);