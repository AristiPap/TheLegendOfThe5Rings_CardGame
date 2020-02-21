#pragma once 

#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <algorithm>
#include "DeckBuilder.hpp"
#include "Card.hpp"
#include "Item.hpp"
#include "Follower.hpp"
#include "Personality.hpp"
#include "Holding.hpp"
#include "Stronghold.hpp"
#include "TypeConverter.hpp"
#define MAX_HAND 6
#define MAX_HIDDEN_PROVINCES 4
class Player
{
    friend bool operator>(const Player&, const Player&);
private:
    std::string name; // The name of the player
    unsigned int honour; // The honour of the player = initial Honour + Personalities' Honour
    unsigned int provincesDefence;
    Stronghold stronghold; // the stronghold that gives the player his starting attributes
    std::list<GreenCard *>* fateDeck; // the Fate Deck
    std::list<BlackCard *>* dynastyDeck; // dynasty deck
    std::list<GreenCard *>* hand; // the cards the player keeps in hand
    std::list<BlackCard *>* provinces;//provinces of player
    std::list<BlackCard *>* provincesToBuy;//provinces of player
    std::list<Personality *>* army; //The available personalities in control of the player 
    std::list<Holding *>* holdings; //The Releaved holdings of the player (initial: 4)

public:
    Player();
    Player(std::string _name);
    ~Player();
/*     bool hasLost(void); //checks if numberOfProvinces == 0
 */    std::string getName(void); //get the name of the player
    unsigned int getInitProvinceDefence(void    );//get the initial defence;
    unsigned int getHonour(void); //get the honour points of the player
    void printHand(void); //print the cards that the player has in hand(max lim: MAX_HAND)
    void untapEverything();//untap all cards
    void drawFateCard(void); //pull a green card from fate deck if the hand count < MAX_HAND
    void revealProvinces(void); //reveal all provinces
    bool attack(Player&);
    bool HasLost(Player&);
    void printProvinces(void);
    void printProvincesToBuy();
    void equip(int, int); // equipPhase function that checks whether the player can equip the personality with the specific green card
    int getArmyNum(void);
    void printArmy(void);
    void printArena(void);
    int getFateCardsNum(void);
    int getProvinceNum(void);
    void buyProvince(int provinceID);
    void equip(Personality&, GreenCard&); // equipPhase function that checks whether the player can equip the personality with the specific green card 
    //void PushHand(std::list<Follower *>::iterator );
    bool isFateDeckEmpty(void);
    bool isDynastyDeckEmpty(void);
    void refreshFateDeck(void);
    void refreshDynastyDeck(void);
};
bool operator>(const Player &p1, const Player &p2);
