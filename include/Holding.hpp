#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Card.hpp"
enum{PLAIN, MINE, GOLD_MINE, CRYSTAL_MINE, FARMS, SOLO, STRONGHOLD};

class Holding : public BlackCard
{
private:
    unsigned int harvestValue;
    Holding *subHolding;
    Holding *upperHolding;

public:
    Holding(); //default constructor
    Holding(std::string , unsigned int);
   // Holding(const Holding &);
    virtual ~Holding();
    Holding* getUpperHolding(void);
    Holding* getSubHolding(void);
    bool checkUpperHolding(Holding* ptr);
    bool checkSubHolding(Holding* ptr);
    unsigned int getHarvestValue(void);
    bool setUpperHolding(Holding*);
    bool setSubHolding(Holding*);
    virtual void print(void) override;
};
