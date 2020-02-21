#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Card.hpp"
#include "Holding.hpp"
class Stronghold : public Holding
{
private:
    unsigned int honour;
    unsigned int money;
    unsigned int initialDefence;

public:
    Stronghold(); //default constructor
    Stronghold(std::string , unsigned int);
    //Stronghold(const Stronghold &); //copy constructor
    virtual ~Stronghold();
    virtual void print(void) override;
    unsigned int getHonour(void);
    unsigned int getMoney(void);
    unsigned int getInitialDefence(void);
};