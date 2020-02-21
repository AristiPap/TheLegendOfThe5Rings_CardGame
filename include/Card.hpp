#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Colours.hpp"
enum{PERSONALITY=1, HOLDING, FOLLOWER, ITEM};
class Card
{
protected:
    bool isTapped;    //check of the card has been tapped
    unsigned int cost; //value of the card
    std::string name; //name of the card
    unsigned int type;
public:
    Card();                //default constructor
    Card(std::string, unsigned int);
    //Card(const Card &src); //Copy constructor
    virtual ~Card();
    std::string getName(void)const;
    unsigned int getCost(void)const;
    bool checkTapped(void);
    void tapCard(void);
    void untapCard(void);
    unsigned int getType(void);
    virtual void print(void)=0;
};

/*Card Types : Green and Black*/
class GreenCard: public Card
{
protected:
    unsigned int attackBonus; //bonus attack of the card
    unsigned int defenceBonus;// bonus defence of the card
    unsigned int minimumHonour;//necessary minimum ammount of honour
    unsigned int effectCost; //the cost of upgrading the card, using the method effectBonus
    unsigned int effectBonus; //the actual upgrade to the
    unsigned int greenCardType; 
public:
    GreenCard(); //default constructor
    GreenCard(std::string, unsigned int);
    //GreenCard(const GreenCard& src); //Copy constructor
    virtual ~GreenCard();
    bool Upgrade(unsigned int); // the method that could upgrade the card if effectCost <= cashAmmount and then return true
    unsigned int getAttackBonus(void);
    unsigned int getDefenceBonus(void);
    unsigned int getMinimumHonour();
    unsigned int getEffectCost(void);
    virtual void print(void) override;
};

class BlackCard: public Card
{
protected:
    bool isReleaved;
    unsigned int blackCardType;
public:
    BlackCard();//default constructor
    BlackCard(std::string, unsigned int);
    //BlackCard(const BlackCard& );//copy constructor
    virtual ~BlackCard();
    bool checkReleaved(void);
    void Reveal(void);
    void Hide(void);
    virtual void print(void)override;
};
unsigned int getAttributes(const char*, const char*, const char*); 