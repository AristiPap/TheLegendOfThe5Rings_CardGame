#include "Follower.hpp"

using namespace std;

Follower::Follower()
{
    /* cout << "The default Follower constructor is used" << endl; */
}
Follower::Follower(string _name, unsigned int _greenCardType)
:GreenCard{_name, FOLLOWER}
{
    string className;
    switch (_greenCardType)
    {
    case FOOTSOLDIER:
        className = "FOOTSOLDIER";
        break;
    case ARCHER:
        className = "ARCHER";
        break;
    case SIEGER:
        className = "SIEGER";
        break;
    case CAVARLY:
        className = "CAVALRY";
        break;
    case NAVAL:
        className = "NAVAL";
        break;
    case BUSHIDO:
        className = "BUSHIDO";
        break;
    }
    cost = getAttributes("./CardsStats/Followers_and_Weapons.txt", className.c_str(), "Cost");
    attackBonus = getAttributes("./CardsStats/Followers_and_Weapons.txt", className.c_str(), "AttackBonus");
    defenceBonus = getAttributes("./CardsStats/Followers_and_Weapons.txt", className.c_str(), "DefenseBonus");
    minimumHonour = getAttributes("./CardsStats/Followers_and_Weapons.txt", className.c_str(), "MinimumHonor");
    effectCost = getAttributes("./CardsStats/Followers_and_Weapons.txt", className.c_str(), "EffectCost");
    effectBonus = getAttributes("./CardsStats/Followers_and_Weapons.txt", className.c_str(), "EffectBonus");
    greenCardType=_greenCardType;
}

Follower::~Follower() { /* cout << "Follower D" << endl; */ }

void Follower::print()
{
    string className;
    switch (greenCardType)
    {
    case FOOTSOLDIER:
        className = BOLD(FGRN("Footsoldier"));
        break;
    case ARCHER:
        className = BOLD(FGRN("Archer"));
        break;
    case SIEGER:
        className = BOLD(FGRN("Sieger"));
        break;
    case CAVARLY:
        className = BOLD(FGRN("Cavalry"));
        break;
    case NAVAL:
        className = BOLD(FGRN("Naval"));
        break;
    case BUSHIDO:
        className = BOLD(FGRN("Bushido"));
        break;
    }

    cout << endl;
    if (isTapped)
        cout << "~";
    else
        cout << " ";
    cout <<"***" << className << "***" << endl;
    GreenCard::print();
}