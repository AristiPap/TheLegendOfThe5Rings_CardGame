#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Card.hpp"
enum followerEnum{FOOTSOLDIER=0, ARCHER, SIEGER, CAVARLY, NAVAL, BUSHIDO};

class Follower : public GreenCard
{
public:
    Follower();                 //default constructor
    Follower(std::string, unsigned int _greenCardType);
    //Follower(const Follower &); //copy cosntructor
    virtual ~Follower();
    virtual void print(void) override;
};