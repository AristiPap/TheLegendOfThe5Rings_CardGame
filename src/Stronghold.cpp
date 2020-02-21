#include "Stronghold.hpp"

using namespace std;

Stronghold::Stronghold()
{
/*     cout << "Default Stronghold Constructor invoked!" << endl;
 */}


Stronghold::Stronghold(string _name, unsigned int _blackCardType)
:Holding(_name, STRONGHOLD)
{
/*     cout << "STRONGHOLD" << endl;
 */    blackCardType = _blackCardType;
    cost = 0;
    honour = getAttributes("./CardsStats/Personalities_and_Holdings.txt", "STRONGHOLD", "Starting Honour");
    initialDefence = getAttributes("./CardsStats/Personalities_and_Holdings.txt", "STRONGHOLD", "InitialDefense");
    money = getAttributes("./CardsStats/Personalities_and_Holdings.txt", "STRONGHOLD", "Harvest");
/*     cout << cost << " " << honour << " " << initialDefence << " " << money << endl;
 */}

Stronghold::~Stronghold() { /* cout << "stronghold D" << endl;  */}

unsigned int Stronghold::getHonour(void)
{
    return honour;
}

unsigned int Stronghold::getMoney(void)
{
    return money;
}

unsigned int Stronghold::getInitialDefence(void)
{
    return initialDefence;
}
void Stronghold::print(void)
{
    cout << endl;
    if (isTapped)
        cout << "~";
    else
        cout << " ";
    cout << BOLD(FRED("***Stronghold***")) << endl;
    BlackCard::print();
    //Here we print the stats
    cout << "Honour: " << honour << endl;
    cout << "Harvest-Value: " << money << endl;
    cout << "Initial-Province-Defence: " << initialDefence << endl;
}