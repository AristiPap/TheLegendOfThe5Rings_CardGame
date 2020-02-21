#include "Card.hpp"
#include <iomanip>
#include <fstream>
#include <iostream>

using namespace std;

/*Card class (abstract) methods*/
Card::Card()
:isTapped{true},cost{0}, name{"Uninitialized"}
{}

//Overloaded Constructor
Card::Card(string _name, unsigned int _type)
:isTapped{true}, cost{0}, name{_name}, type{_type}
{}

Card::~Card() { /* cout << "Card D" << endl; */ }
string Card::getName(void)const
{
    return name;
}

unsigned int Card::getCost(void)const
{
    return cost;
}

bool Card::checkTapped(void)
{
    return isTapped;
}

void Card::tapCard(void)
{
    isTapped = true;
}

void Card::untapCard(void)
{
    isTapped = false;
}

unsigned int Card::getType()
{
    return type;
}
/////////////////////////////////////////////////////////////////////
GreenCard::GreenCard()
{}

GreenCard::GreenCard(string name,unsigned int type_val):Card(name,type_val){}
//Calling Card Constructor with the same parameters as the parameters of the green/blackcard constructor
GreenCard::~GreenCard(){/* cout <<"Green Card D" << endl; */ }
void GreenCard::print(void)
{
    cout << name << ", cost: " << cost << endl;
    cout <<"Attack-Bonus: " << attackBonus << endl;
    cout << "Defence-Bonus: " << defenceBonus << endl;
    cout << "Min-Honour required: " << minimumHonour << endl;
    cout << "Upgrade-Bonus: " << effectBonus << " (extra-cost: " << effectCost << ")" << endl;
}
unsigned int GreenCard::getAttackBonus()
{
    return attackBonus;
}
unsigned int GreenCard::getDefenceBonus()
{
    return defenceBonus;
}
unsigned int GreenCard::getMinimumHonour()
{
    return minimumHonour;
}
unsigned int GreenCard::getEffectCost()
{
    return effectCost;
}
bool GreenCard::Upgrade(unsigned int cashAmount)
{
    if(this->getEffectCost()>cashAmount)
    {
        cout<<"You need:"<<this->getEffectCost()-cashAmount<<"more tokens to unlock upgrade"<<endl;
        return false;
    }
    else
    {
        attackBonus+=effectBonus;
        defenceBonus+=effectBonus;
        cout<<"Upgrade granted"<<endl;
        return true;
    }
}
///////////////////////////
BlackCard::BlackCard()
{}
BlackCard::BlackCard(string name,unsigned int type_val)
: Card(name,type_val),isReleaved{false}
{}
BlackCard::~BlackCard(){}
void BlackCard::print()
{
    cout << name << ", cost: " << cost << endl;
}
bool BlackCard::checkReleaved()
{
    return isReleaved;
}
void BlackCard::Reveal()
{
    isReleaved=true;
}
void BlackCard::Hide()
{
    isReleaved=false;
}






