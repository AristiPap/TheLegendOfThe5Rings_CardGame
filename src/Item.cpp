#include "Item.hpp"

/* Item Methods Implementation */
using namespace std;

Item::Item()
{
   /*  cout << "The default constructor is being used!" << endl; */
}

Item::Item(string _name, unsigned int _greenCardType)
:GreenCard(_name, ITEM)
{
    string className;
    switch(_greenCardType)
    {
        case KATANA: className = "KATANA";
        break;
        case SPEAR: className = "SPEAR";
        break;
        case BOW: className = "BOW";
        break;
        case NINJATO: className = "NINJATO";
        break;
        case WAKIZASHI: className = "WAKIZASHI";
        break;
    }
    cost = getAttributes("./CardsStats/Followers_and_Weapons.txt", className.c_str(), "Cost");
    attackBonus = getAttributes("./CardsStats/Followers_and_Weapons.txt", className.c_str(), "AttackBonus");
    defenceBonus = getAttributes("./CardsStats/Followers_and_Weapons.txt", className.c_str(), "DefenseBonus");
    minimumHonour = getAttributes("./CardsStats/Followers_and_Weapons.txt", className.c_str(), "MinimumHonor");
    effectCost = getAttributes("./CardsStats/Followers_and_Weapons.txt", className.c_str(), "EffectCost");
    effectBonus = getAttributes("./CardsStats/Followers_and_Weapons.txt", className.c_str(), "EffectBonus");
    durability = getAttributes("./CardsStats/Followers_and_Weapons.txt", className.c_str(), "Durability");
    greenCardType = _greenCardType;
}


Item::~Item(){/* cout << "Item D" << endl; */}

void Item::print(void)
{
    string className;
    switch (greenCardType)
    {
    case KATANA:
        className = BOLD(FCYN("Katana"));
        break;
    case SPEAR:
        className = BOLD(FCYN("Spear"));
        break;
    case BOW:
        className = BOLD(FCYN("Bow"));
        break;
    case NINJATO:
        className = BOLD(FCYN("Ninjato"));
        break;
    case WAKIZASHI:
        className = BOLD(FCYN("Wakizashi"));
        break;
    }

    cout << endl;
    if (isTapped)
        cout << "~";
    else
        cout << " ";
    cout << "***" << className << "-" << durability << "***" << endl;
    GreenCard::print();
}

int Item::getDurability(){
    return durability;
}

void Item::ReduceDurability(){
    durability--;
}
