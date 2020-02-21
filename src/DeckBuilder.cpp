#include "DeckBuilder.hpp"
#include <iostream>
#include <string>
using namespace std;
	
DeckBuilder::DeckBuilder()
{
	srand(unsigned(time(NULL)));
}

DeckBuilder::~DeckBuilder()
{
	/* list<BlackCard *>::iterator it;
	list<GreenCard *>::iterator it2;
	for (it = black->begin(); it != black->end(); it++)
	{
		black->remove((*it));
		delete *it;
		it = black->begin();
	}
	for (it2 = green->begin(); it2 != green->end(); it++)
	{
		green->remove((*it2));
		delete *it2;
		it2 = green->begin();
	}
	delete black;
	delete green; */
}

void DeckBuilder::createFateDeck(list<GreenCard*>* green)
{

	int i;
	for (i = 0; i < NO_FOOTSOLDIER; i++)
		green->push_back(new Follower("Peasants", FOOTSOLDIER));
	for (i = 0; i < NO_ARCHER; i++)
		green->push_back(new Follower("Elite Troops", ARCHER));
	for (i = 0; i < NO_SIEGER; i++)
		green->push_back(new Follower("Immortal Bushi", SIEGER));
	for (i = 0; i < NO_CAVALRY; i++)
		green->push_back(new Follower("Unicorn Horses", CAVARLY));
	for (i = 0; i < NO_NAVAL; i++)
		green->push_back(new Follower("Yomi Ships", NAVAL));
	for (i = 0; i < NO_BUSHIDO; i++)
		green->push_back(new Follower("7 Samurai", BUSHIDO));

	for (i = 0; i < NO_KATANA; i++)
		green->push_back(new Item{"Daijtso", KATANA});
	for (i = 0; i < NO_BOW; i++)
		green->push_back(new Item("Yumi", BOW));
	for (i = 0; i < NO_SPEAR; i++)
		green->push_back(new Item("Kama", SPEAR));
	for (i = 0; i < NO_NINJATO; i++)
		green->push_back(new Item("Butterfly Dagger", NINJATO));
	for (i = 0; i < NO_WAKIZASHI; i++)
		green->push_back(new Item("Kusanagi", WAKIZASHI));
}

void DeckBuilder::createDynastyDeck(list<BlackCard*>* black)
{

	int i;
	 //Create Personalities
	//NO_DEFENSIVE 10
	for (i = 0; i < NO_DEFENSIVE; i++)
		black->push_back(new Personality("Footsoldiers", DEFENDER));
	//NO_ATTACKING 10
	for (i = 0; i < NO_ATTACKING; i++)
		black->push_back(new Personality("Steadfast bushi", ATTACKER));
	//NO_SHOGUN	2
	black->push_back(new Personality("Akodo Kaneka", SHOGUN));
	black->push_back(new Personality("Isawa Shi en", SHOGUN));
	//NO_CHANCELLOR 2
	black->push_back(new Personality("Hida Shozen", CHANCELLOR));
	black->push_back(new Personality("Mirimuto Enishi", CHANCELLOR));
	//NO_CHAMPION 1
	black->push_back(new Personality("Hida Kisada", CHAMPION));
	//Create holdings
	for (i = 0; i < NO_PLAIN; i++)
		black->push_back(new Holding("Rice Fields", PLAIN));
	for (i = 0; i < NO_FARMS; i++)
		black->push_back(new Holding("Fish Farms", FARMS)); 
	for (i = 0; i < NO_MINE; i++)
		black->push_back(new Holding("Ashio Copper Mine", MINE));
	for (i = 0; i < NO_GOLD_MINE; i++)
		black->push_back(new Holding("Konomai Gold Mine", GOLD_MINE));
	for (i = 0; i < NO_CRYSTAL_MINE; i++)
		black->push_back(new Holding("Ichinokawa Crystal Mine", CRYSTAL_MINE));
	for (i = 0; i < NO_SOLO; i++)
		black->push_back(new Holding("Gifts and Favors", SOLO));

}

void DeckBuilder::deckShuffler(list<BlackCard *> *black)
{
	vector<BlackCard *> vect;
	list<BlackCard *>::iterator it;
	for (it = black->begin(); it != black->end(); it++)
		vect.push_back((*it));
	srand((unsigned int) time(NULL));
	random_shuffle(vect.rbegin(), vect.rend());

	black->clear();

	vector<BlackCard *>::iterator it2;
	for (it2 = vect.begin(); it2 != vect.end(); it2++)
		black->push_back((*it2));
}

void DeckBuilder::deckShuffler(list<GreenCard *> *green)
{
	vector<GreenCard *> vect;
	list<GreenCard *>::iterator it;
	for (it = green->begin(); it != green->end(); it++)
		vect.push_back((*it));
		
	srand((unsigned int)time(NULL));
	random_shuffle(vect.begin(), vect.end());

	green->clear();

	vector<GreenCard *>::iterator it2;
	for (it2 = vect.begin(); it2 != vect.end(); it2++)
		green->push_back((*it2));
}