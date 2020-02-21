#pragma once

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include "Card.hpp"
#include "Follower.hpp"
#include "Item.hpp"
#include "TypeConverter.hpp"

enum{ATTACKER, DEFENDER, SHOGUN, CHANCELLOR, CHAMPION};

class Personality : public BlackCard
{
private:
    unsigned int attack;
    unsigned int defence;
    unsigned int honor;
    bool isDead;
    std::list<Follower *> followers;
    std::list<Item *> items;

public:
    Personality();                    //default constructor
    Personality(std::string, unsigned int);
   // Personality(const Personality &); //copy cosntructor
    void getBonus(GreenCard& );
    unsigned int getAttack();
    unsigned int getDefence();
    void ModifyItem();
    void DetachFollower(int ,bool);
    unsigned int getBonus();
    unsigned int getHonour(void);
    int DecreaseHonour();
    virtual ~Personality();
    virtual void print(void)override;
    void printFollowers(void);
    void printItems(void);
};