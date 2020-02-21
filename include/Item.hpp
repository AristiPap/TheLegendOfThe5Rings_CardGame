#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Card.hpp"

enum itemEnum {KATANA, SPEAR, BOW, NINJATO, WAKIZASHI};

class Item : public GreenCard
{
private:
    unsigned int durability;
public:
    Item();             //default cosntructor
    Item(std::string, unsigned int);
   // Item(const Item &); //copy constructor
    int getDurability();
    void ReduceDurability();
    virtual ~Item();
    virtual void print(void)override;
};