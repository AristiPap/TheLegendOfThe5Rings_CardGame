#include "Player.hpp"

using namespace std;

static void setHand(list<GreenCard*>* fateDeck, list<GreenCard*>* hand)
{
    //we must set the first MAX_HAND=6 cards of the fate deck as the hand of the player
    auto it = fateDeck->begin();
    for(int i=0; i<MAX_HAND; i++)
    {
        hand->push_back(*it);
        fateDeck->remove(*it);
        it = fateDeck->begin();
    }
}

static void setProvinces(list<BlackCard*>* dynastyDeck, list<BlackCard*>* provinces)
{
    //We choose the first 4 cards of the dynasty deck as the promises
    auto it = dynastyDeck->begin();
    auto max = MAX_HIDDEN_PROVINCES-provinces->size();
    for(int i=0; i<max; i++)
    {
        provinces->push_back(*it);
        dynastyDeck->remove(*it);
        it = dynastyDeck->begin();
    }
}

bool operator>(const Player &p1, const Player &p2)
{
    return p1.honour > p2.honour;
}

Player::Player()
:stronghold{"Stronghold",STRONGHOLD}{
    DeckBuilder deckBuilder;
    stronghold.Reveal();
    stronghold.untapCard();
    honour = stronghold.getHonour();
    provincesDefence = stronghold.getInitialDefence();
    //create the fate and the dynasty deck
    fateDeck =new list<GreenCard*>();
    deckBuilder.createFateDeck(fateDeck); 
    dynastyDeck = new list<BlackCard*>();
    deckBuilder.createDynastyDeck(dynastyDeck);
    //shuffle the 2 decks
    deckBuilder.deckShuffler(fateDeck);
    deckBuilder.deckShuffler(dynastyDeck);
    //create the hand list 
    hand = new list<GreenCard*>();
    //set the hand ready
    setHand(fateDeck, hand);
    //create the provinces list
    provinces = new list<BlackCard *>();
    provincesToBuy = new list<BlackCard *>();

    //set the provinces
    setProvinces(dynastyDeck, provincesToBuy);

    //create the empty holding list
    holdings = new list<Holding*>();
    Holding* strong = new Stronghold{stronghold};
    provinces->push_back(strong);
    holdings->push_back(strong);//add strong hold as your first province
    army = new list<Personality*>(); //the army is empty so nothing more to be done
}

Player::Player(std::string _name)
:Player()
{
    name=_name;
}

Player::~Player()
{
    for(auto it=fateDeck->begin(); it!=fateDeck->end(); )
    {
        delete *it;
        it=fateDeck->erase(it);
    }   
    delete fateDeck;
    for(auto it=dynastyDeck->begin(); it!=dynastyDeck->end(); )
    {
       delete *it;
        it=dynastyDeck->erase(it);
    }
    delete dynastyDeck;
    for(auto it=provincesToBuy->begin(); it!=provincesToBuy->end(); )
    {
        delete *it;
        it=provincesToBuy->erase(it);
    }
    delete provinces;
    delete provincesToBuy;
    for(auto it=hand->begin(); it!=hand->end(); )
    {
        delete *it;
        it=hand->erase(it);
    }
    delete hand;
    for(auto it=holdings->begin(); it!=holdings->end(); )
    {
        delete *it;
        it=holdings->erase(it);
    }
    delete holdings;
    for(auto it=army->begin(); it!=army->end(); )
    {
        delete *it;
        it=army->erase(it);
    }
    delete army;
}
/* bool Player::hasLost(void)           //checks if numberOfProvinces == 0
{
    return (provinces->empty());
} */

//Functions to handle the case that either the fate or the dynasty deck are empty
bool Player::isFateDeckEmpty(void)
{
    return fateDeck->empty();
}
bool Player::isDynastyDeckEmpty(void)
{
    return dynastyDeck->empty();
}
void Player::refreshFateDeck(void)
{
    if(fateDeck->empty())
    {
        DeckBuilder db;
        db.createFateDeck(fateDeck);
    }
}
void Player::refreshDynastyDeck(void)
{
    if(dynastyDeck->empty())
    {
        DeckBuilder db;
        db.createDynastyDeck(dynastyDeck);
    }
}

std::string Player::getName(void)    //get the name of the player
{
    return name;
}
unsigned int Player::getInitProvinceDefence(void)
{
    return provincesDefence;
}
unsigned int Player::getHonour(void) //get the honour points of the player
{
    return honour;
}

void Player::printHand(void)         //print the cards that the player has in hand(max lim: MAX_HAND)
{
    for (auto card : *hand)
    {
        card->print(); // overloaded holdings constructor TO BE DONE
    }
}
void Player::untapEverything()       //untap all cards
{
    list<BlackCard*>::iterator it0;
    list<Personality*>::iterator it1;
    list<Holding*>::iterator it2;

    for(it0=provinces->begin(); it0!=provinces->end(); it0++)
    {
        (**it0).untapCard();
    }
    for(it0=provincesToBuy->begin(); it0!=provincesToBuy->end(); it0++)
    {
        (**it0).untapCard();
    }
    for(it1 = army->begin(); it1 != army->end(); it1++)
    {
        (**it1).untapCard();
    }
    for(it2 = holdings->begin(); it2 != holdings->end(); it2++)
    {
        (**it2).untapCard();
    }
    stronghold.untapCard();
}

void Player::drawFateCard(void)      //pull a green card from fate deck if the hand count < MAX_HAND
{
    auto card = fateDeck->begin();
    
    if(hand->size()<MAX_HAND)
    {
        fateDeck->remove(*card);
        hand->push_back(*card);
    }
    else
    {
        cout << "TOO MANY CARDS" << endl;
    }
}

void Player::revealProvinces(void)   //reveal all provinces
{
    list<BlackCard*>::iterator it;
    for(it=provincesToBuy->begin(); it!=provincesToBuy->end(); it++)
    {
        (**it).Reveal();
    }
}
int Player::getArmyNum(void)
{
    return army->size();
}
int Player::getFateCardsNum(void)
{
    return hand->size();
}
int Player::getProvinceNum(void)
{
    return provinces->size();
}
void Player::printArmy(void)
{
    for (auto person : *army)
    {
        if (person->checkReleaved() == true){ // if the person is not hidden
            if(person->checkTapped()==false)
            person->print();
        }    
        else
        {
            cout << "***HIDDEN SOLDIER SHOUDL NOT GO IN THERE***" << endl;
        }
    }
}
void printBattleArmy(list<Personality* >* players){
    for (auto person : *players)
    {
        if(person->checkTapped()==false)
        person->print();
    }
}
void Player::printProvinces(void)
{
    for (auto province : *provinces)
    {
        if (province->checkReleaved() == true) // if the province is not hidden
            province->print();                 
        else
        {
            cout << "***HIDDEN PROVINCE***" << endl;
        }
    }
}
void Player::printArena(void){
    for(auto soldier : *army)
    {
        soldier->print();
        soldier->printItems();
        soldier->printFollowers();
    }
}
void Player::printProvincesToBuy(void)
{
    for(auto province : *provincesToBuy)
    {
        if(province->checkReleaved() == true) // if the province is not hidden
            province->print();
        else
        {
            cout << "***HIDDEN PROVINCE***" << endl;
        }
        
    }
}
//utility function to make the upgrade progress easier
static bool wantUpgrade(GreenCard& card)
{
    cout << "Do you want to Upgrade the card and get the upgrade bonus for " << card.getEffectCost() << " currency units? ('yes' or 'no'): ";
    string answer;
    do
    {
        cin >> answer;
        if(!cin || (answer!="yes" && answer!="no"))
        {
            cout << "The answer must be a 'yes' or a 'no'. Answer again: ";
        }
    } while (!cin || (answer!="yes" && answer!="no"));
    if(answer == "yes")
    {
        return true;
    }
    return false;
}

void Player::equip(int personNum, int cardNum)
{
    //first I need to find the card
    cardNum --; //indexing from 1 (begin + i-1 == i)
    personNum --;
    auto card = hand->begin();
    while(cardNum-- > 0)
    {
        card++;
    }
    auto personality = army->begin(); // now we have to find the personality
    while(personNum-- > 0)
    {
        personality++;
    }

    unsigned int totalMoney=0;  
    //first we have to find if the player has enough money to buy the card
    for(auto holding=holdings->begin(); holding!=holdings->end(); holding++)
    {
        if((*holding)->checkTapped() == false) // if the holding is untapped
            totalMoney+= (**holding).getHarvestValue(); //get the harvest value of all the money the player has
    }

    //Now we check: 
    // if total Money > card cost and the personality has enough honor to buy the card
    if(totalMoney >= (*card)->getCost() && (*personality)->getHonour() >= (*card)->getMinimumHonour())
    {
        int totalCost = (*card)->getCost();
        //delete the card from the hand list
        if(wantUpgrade(**card))
        {
            if((*card)->Upgrade(totalMoney - totalCost)) 
            {
                // we pass 'totalMoney - totalCost' cause those are the extra money we
                //have to give and we have to check if we could afford the upgrade,
                //if not then we just skip the part and move on to the purchase if the simple card's edition
                totalCost+=(*card)->getEffectCost(); // add the upgrade cost to the total amount of money you will give
            }
        }
        (*personality)->getBonus(**card);  //assign a copy of the card to either followers' or items' lists
        delete *card; // free the memory.
        card = hand->erase(card);

        //To complete the transaction we need to get the cost value full filled-the player must choose the holdings to tap
        int cash = 0;
        while(cash < totalCost)
        {
            cout << "Choose one out of your available holdings in order to pay the cost of the card(Remaining Cost: " << totalCost-cash << " currency units)" <<  endl;
            cout << ">Holding # -> " ;
            int holdingNum;
            do{
                cin >> holdingNum; // get the proper holding from the list
                if(!cin || holdingNum > holdings->size()) 
                    cout << "Enter a valid number that represents a holding..." << endl;
            }while(!cin || holdingNum > holdings->size());
            cout << endl;
            auto it=holdings->begin();
            holdingNum--;
            for(int i=0; i<holdingNum; i++)
            {
                it++; // traverse through the list in order to find the element
            }
            if((**it).checkTapped() == false)
            {
                cash += (**it).getHarvestValue(); // get the money
                (**it).tapCard(); // tap the card
            }  
        }
    }
    else
    {
        cout << "Not enough money for the purchase..." << endl;
    }
}

//utillity function to introduce the holding to the proper holding  chain, if that possible
static void setChain(std::list<Holding*>* holdings, Holding* hold)
{
    //We have to traverse the list so that we find a proper holding
    auto it = holdings->begin();
    bool upperSet=false, subSet = false,check_upper=true,check_sub=true;
    while(it != holdings->end() && (!upperSet || !subSet)) 
    {
        //traverse till we reach the end of the list or if the holding is connected to a full chain (sub and upper holding)
       /* if(upperSet==false)
        {
            upperSet = hold->setUpperHolding(*it);
        }
        if(subSet == false) 
        {
            subSet = hold->setSubHolding(*it);
        }*/
        check_upper=hold->checkUpperHolding(*it);

        if(upperSet==false){
            if(check_upper==true)
            upperSet=hold->setUpperHolding(*it);
            check_sub=(*it)->checkSubHolding(hold);
            if(upperSet==true && check_sub==true){
                (**it).setSubHolding(hold);
            }
        }
        check_sub=hold->checkSubHolding(*it);
        if(subSet==false){
            if(check_sub==true)
            subSet=hold->setSubHolding(*it);
            check_upper=(*it)->checkSubHolding(hold);
            if(subSet==true && check_upper==true){
                (**it).setUpperHolding(hold);
            }
        }


        it++; // traverse to the next node
    }
} 

void Player::buyProvince(int provinceID)
{
    //First we have to find out which is the province the player wants to buy
    auto province = provincesToBuy->begin();
    provinceID--;
    while(provinceID-- > 0)
        province++;
    
    //Now to get the total ammount of money the player has available:
    int totalMoney=0;
    for(auto holding : *holdings)
    {
        if((holding)->checkTapped() == false) // if the holding is untapped
        {
            totalMoney+=holding->getHarvestValue();
        }
    }
    if(totalMoney >= (*province)->getCost())
    {
        //Now we have to repay the province using all the available holdings we have left:
        //To complete the transaction we need to get the cost value full filled-the player must choose the holdings to tap
        int cash = 0;
        int totalCost = (int)(*province)->getCost();
        while(cash < totalCost)
        {
            cout << "Choose one out of your available holdings in order to pay the cost of the card(Remaining Cost: " << totalCost - cash << " currency units)" << endl;
            cout << ">Holding # -> ";
            int holdingNum;
            do
            {
                cin >> holdingNum; // get the proper holding from the list
                if (!cin || holdingNum > holdings->size())
                    cout << "Enter a valid number that represents a holding..." << endl;
            } while (holdingNum > holdings->size());
            cout << endl;
            holdingNum--;
            auto it = holdings->begin();
            for (int i = 0; i < holdingNum; i++)
            {
                it++; // traverse through the list in order to find the element
            }
            if ((**it).checkTapped() == false)
            {
                cash += (**it).getHarvestValue(); // get the money
                (**it).tapCard();                 // tap the card
            }
        }

        //Now we have to determine where to add the card (army or holdings)
        Personality *person;
        Holding* hold;
        TypeConverter conv;
        conv.getCorrectType(*province, &person, &hold);

        if(person != NULL)
        {
            cout << "Army" << endl;
            //the card is a personality
            army->push_back(person);
        }
        else if(hold != NULL)
        {
            cout << "Holding" << endl;
            //the card is a holding
            holdings->push_back(hold);
            //Now we have to add the holding to a chain if this is possible calling the following function
            setChain(holdings, hold);
        }
        provinces->push_back(*province);
        province = provincesToBuy->erase(province); // remove the card from the provinces list and change the number of hidden provinces
        //we don't want to destroy the province pointer since we add it roughly in the new list (either army or holdings)

        //Now we will update player's honour in case the new province is a personality
        honour = stronghold.getHonour(); // set the honor to the initial one 
        for (auto person : *army)
        {
            honour += person->getHonour();
        }
        //update the provincesToBuy list
        setProvinces(dynastyDeck, provincesToBuy);
    }
}

bool Player::HasLost(Player& player){
    if(player.getProvinceNum()==0){
        cout<<player.getName()<<" you just lost...\n";
        return true;
    }
    else if(this->getProvinceNum()==0){
        cout<<this->getName()<<" you just lost...\n";
        return true;
    }
    else return false;
}
bool Player::attack(Player& player){    
     list<Personality*>* _copy;
     list<Personality*>* _copy2;
     list<Personality*>* attack_army;
     attack_army=new list<Personality*>();
     _copy=new list<Personality*>();
     _copy2=new list<Personality*>();
     auto it=attack_army->begin();
     auto it_val=_copy->begin();
     auto it_val2=_copy->begin();
     list<Personality*>* defend_army;
     defend_army=new list<Personality*>();
     auto it_0=defend_army->begin();
     TypeConverter obj;
     bool move=true,attack,flag=false;
     bool lose=false;
     int card_num;
     string instruction;
     int defence_points=0,attack_points=0,times=0,counter=0;
      
    for(auto ptr=this->army->begin(); ptr!=this->army->end(); ptr++){
        if((**ptr).checkTapped()==true)
        counter++;
    }
    if(counter==this->army->size()){
        cout<<"All your army is tapped,unfortunately you can't attack"<<endl;
        return false;
    }
     cout<<"Attacker choose your army!(Choose from 1 to "<<this->getArmyNum()<<")"<<endl;
    //print untapped personalities of this player
    this->printArmy();   
    int army_counter=this->getArmyNum();
    for(it_val=this->army->begin(); it_val!=this->army->end(); it_val++){
            _copy->push_back(*it_val);
    }
    while(move==true && this->army->empty()==false && army_counter>0){
        if(times==0){
            cin>>card_num;
            if(card_num>this->getArmyNum()){
                flag=true;
                cout<<"You must enter a valid number..Try again"<<endl;
            }
            else{
                flag=false;
                card_num--;
                it=next(army->begin(),card_num);
                if((**it).checkTapped()==false){
                    attack_army->push_back(*it);
                    _copy->remove(*it);
                }
                else cout<<"The personality you chose is tapped\n\n"<<endl;
            } 
        }
        else if(times>0){
          cout<<"Attacker choose your army!(Choose from 1 to "<<this->getArmyNum()-times<<")"<<endl;
          printBattleArmy(_copy);
          cin>>card_num;
          if(card_num>this->getArmyNum()-times){
              flag=true;
               cout<<"You must enter a valid number..Try again"<<endl;
          }
          else{
            flag=false;
            card_num--;
            it=next(_copy->begin(),card_num);
            if((**it).checkTapped()==false){
                attack_army->push_back(*it);
                _copy->remove(*it);
            }
            else cout<<"The personality you chose is tapped\n\n"<<endl;
          }
        }
        if(flag==false){
            cout<<"Want to choose another personality for your army?\n(type:yes || no)"<<endl;
            army_counter--;
            times++;
            cin>>instruction;
            if(!cin || (instruction!="yes" && instruction!="no"))
            {
                cout << "The answer is either a 'yes' or 'no'. Please, try again: ";
            }
            else if(instruction=="yes") move=true;
            else if (instruction=="no") move=false;
        }
    }
    for(it=attack_army->begin(); it!=attack_army->end(); it++)
    {  
        attack_points+=(**it).getAttack();
        (**it).tapCard();
    }
    delete _copy;
    cout<<"Finally choose the province you want to attack:"<<endl;
    //print provinces of the defender
    player.printProvinces();
    do
    {
        cin >> card_num; // get the proper holding from the list
        if (!cin || card_num > player.getProvinceNum())
          cout << "Enter a valid number that represents a province..." << endl;
    } while (card_num >player.getProvinceNum());
    cout << endl;
    //cin>>card_num;
    card_num--;
    auto provinceptr=provinces->begin();
    provinceptr=next(player.provinces->begin(),card_num);

    army_counter=player.getArmyNum();
    cout<<"Defender,it's now time to choose your army! (Choose from 1 to "<<player.getArmyNum()<<")"<<endl;
    player.printArmy();
    //print untapped personalities of the defender
    move=true;
    
    for(it_val2=player.army->begin(); it_val2!=player.army->end(); it_val2++){
            _copy2->push_back(*it_val2);
    }
    times=0;
    flag=false;
    while(move==true && player.army->empty()==false && army_counter>0){
       if(times==0){
            cin>>card_num;
            if(card_num>player.getArmyNum()){
                flag=true;
                cout<<"You must enter a valid number..Try again"<<endl;
            }
            else{
                flag=false;
                card_num--;
                it_0=next(player.army->begin(),card_num);
                if((**it_0).checkTapped()==false){
                    defend_army->push_back(*it_0);
                    _copy2->remove(*it_0);
                }
                else cout<<"The personality you chose is tapped\n\n"<<endl;
            }
        }
        else if(times>0){
          cout<<"Defender choose your army!(Choose from 1 to "<<player.getArmyNum()-times<<")"<<endl;
          printBattleArmy(_copy2);
          cin>>card_num;
          if(card_num>player.getArmyNum()-times){
              flag=true;
               cout<<"You must enter a valid number..Try again"<<endl;
          }
          else{
            flag=false;
            card_num--;
            it_0=next(_copy2->begin(),card_num);
            if((**it_0).checkTapped()==false){
                defend_army->push_back(*it_0);
                _copy2->remove(*it_0);
            }
            else cout<<"The personality you chose is tapped\n\n"<<endl;
          }
        }
        if(flag==false){
            cout<<"Want to choose another personality for your army?\n(type:yes ||no)"<<endl;    
            army_counter--;
            times++;
            cin>>instruction;
            if(!cin || (instruction!="yes" && instruction!="no"))
            {
                cout << "The answer is either a 'yes' or 'no'. Please, try again: ";
            }
            else if(instruction=="yes") move=true;
            else if (instruction=="no") move=false;
        }
    }
    
    if(player.army->empty()==true)
        defence_points=player.getInitProvinceDefence();
    else{
        for(it_0=defend_army->begin(); it_0!=defend_army->end(); it_0++)
        {  
            defence_points+=(**it_0).getDefence();
        }
        defence_points+=player.getInitProvinceDefence();
    }
    delete _copy2;
         auto it_2=player.army->begin();
         auto it_3=this->army->begin();
         auto it_4=this->holdings->begin();
         auto it_5=this->provinces->begin();
         auto it_6=player.holdings->begin();
         auto it_7=player.provinces->begin();
        //attacker wins
        if((attack_points-defence_points)>(int) player.getInitProvinceDefence()){// && (attack_points-defence_points)>0){
            //deleting the personalities that took place in the battle with the defend army
            for(it_0=defend_army->begin(); it_0!=defend_army->end(); it_0++){
                it_2=find(player.army->begin(),player.army->end(),*it_0);
                if(player.army->empty()==false){
                    it_5=find(player.provinces->begin(),player.provinces->end(),*it_2);
                    if(it_5!=player.provinces->end()) 
                        it_5=player.provinces->erase(it_5);
                    
                    delete *it_2;
                    it_2=player.army->erase(it_2);
                }
            }
            delete defend_army;
            //now deleting province
            Personality *person;
            Holding *hold;
            obj.getCorrectType(*provinceptr, &person, &hold);
            provinceptr=player.provinces->erase(provinceptr);
            
            if(hold==NULL)//province is a personality
            {
                it_2=find(player.army->begin(),player.army->end(),person);
                if(player.army->empty()==false && it_2!=player.army->end()){
                    delete *it_2;
                    it_2=player.army->erase(it_2);
                }
            }
            else if(hold!=NULL)//province is a holding
            {
                it_4=find(player.holdings->begin(),player.holdings->end(),hold);
                if(player.holdings->empty()==false && it_4!=player.holdings->end()){
                    delete *it_4;
                    it_4=player.holdings->erase(it_4);
                }
            }
            lose=this->HasLost(player);
            cout<< this->getName()<<", you won this round! PROVINCE DESTROYED!"<<endl;
        }
        else{
            //partial win of the attacker-defender loses everything
            if(attack_points>defence_points){///////////////////////////////////////////////
                for(it=attack_army->begin(); it!=attack_army->end(); it++){
                    int p_honor=(**it).DecreaseHonour();
                    if((**it).getAttack()>=attack_points-defence_points){                         
                         //delete that personality from the player's army
                         it_3=find(this->army->begin(),this->army->end(),*it);
                         if(this->army->empty()==false){
                            it_5=find(this->provinces->begin(),this->provinces->end(),*it_3);
                            if(it_5!=this->provinces->end()) 
                                it_5=this->provinces->erase(it_5);
                    
                            delete *it_3;
                            it_3=this->army->erase(it_3);
                        }
                        if(attack_army->empty()==false){
                                it=attack_army->erase(it);
                        }
                    }
                    //remove followers(or not) but not the personality
                    else if((**it).getAttack()<attack_points-defence_points){
                        //detach followers
                        attack=true;
                        (**it).DetachFollower(attack_points-defence_points,attack);
                       // (**it).tapCard();
                 //       int p_honor=(**it).DecreaseHonour();
                        (**it).ModifyItem();
                        if(p_honor==0)
                        {
                            cout<<"I shall not dishonor my family...(performing Seppuku)"<<endl;
                             it_3=find(this->army->begin(),this->army->end(),*it);
                             if(this->army->empty()==false){
                                it_5=find(this->provinces->begin(),this->provinces->end(),*it_3);
                                if(it_5!=this->provinces->end()) 
                                    it_5=this->provinces->erase(it_5);

                                delete *it_3;
                                it_3=this->army->erase(it_3);  
                            }  
                            if(attack_army->empty()==false){
                                it=attack_army->erase(it);
                            }
                        }
                    }
                }
                 //deleting the personalities that took place in the battle with the defend army
                for(it_0=defend_army->begin(); it_0!=defend_army->end(); it_0++){
                    it_2=find(player.army->begin(),player.army->end(),*it_0);
                    if(player.army->empty()==false){
                            it_5=find(player.provinces->begin(),player.provinces->end(),*it_2);
                            if(it_5!=player.provinces->end()) 
                                it_5=player.provinces->erase(it_5);
                          delete *it_2;
                          it_2=player.army->erase(it_2);
                    }
                }
                delete defend_army;
                cout<<this->getName()<<",you didn't win but you survived the battle!"<<attack_points-defence_points<<endl;
            }
            //DRAW(delete all the personalities from both sides)
            else if(attack_points==defence_points){
                //deleting the personalities that took place in the battle with the defend army
                for(it_0=defend_army->begin(); it_0!=defend_army->end(); it_0++){
                    it_2=find(player.army->begin(),player.army->end(),*it_0);
                    if(player.army->empty()==false){
                        it_5=find(player.provinces->begin(),player.provinces->end(),*it_2);
                        if(it_5!=player.provinces->end()) 
                            it_5=player.provinces->erase(it_5);
                        delete *it_2;
                        it_2=player.army->erase(it_2);
                    }
                }
                delete defend_army;
                //deleting the personalities that took place in the battle with the attack army
                for(it=attack_army->begin(); it!=attack_army->end(); it++){
                    it_3=find(this->army->begin(),this->army->end(),*it);
                    if(this->army->empty()==false){
                        it_5=find(this->provinces->begin(), this->provinces->end(),*it_3);
                        if(it_5!=this->provinces->end()) 
                            it_5=this->provinces->erase(it_5);
                        delete *it_3;
                        it_3=this->army->erase(it_3);
                    }
                }
                delete attack_army;
                cout<<"IT'S A DRAW!"<<endl;
            }
            //attacker loses completely
            else{
                 for(it_0=defend_army->begin(); it_0!=defend_army->end(); it_0++){
                    if((**it_0).getAttack()>=(defence_points-attack_points)){
                        //delete that personality first from the player's army then from the defend army
                         it_2=find(player.army->begin(),player.army->end(),*it_0);
                         if(player.army->empty()==false){
                            it_5=find(player.provinces->begin(),player.provinces->end(),*it_2);
                            if(it_5!=player.provinces->end()) 
                                it_5=player.provinces->erase(it_5);
                             delete *it_2;
                            it_2=player.army->erase(it_2);
                        }   
                        if(defend_army->empty()==false){
                        it_0=defend_army->erase(it_0);
                        }
                    }
                     else{
                        //detach followers
                        attack=false;
                        (**it_0).DetachFollower(defence_points-attack_points,attack);
                        int _honor=(**it_0).DecreaseHonour();
                        /////////////////////////////////////
                        (**it_0).ModifyItem();
                        if(_honor==0)
                        {
                            cout<<"I shall not dishonor my family...(performing Seppuku)"<<endl;
                            it_2=find(player.army->begin(),player.army->end(),*it_0);
                             if(player.army->empty()==false){
                                it_7=find(player.provinces->begin(),player.provinces->end(),*it_2);
                                if(it_7!=player.provinces->end()) 
                                    it_7=player.provinces->erase(it_7);

                                delete *it_2;
                                it_2=this->army->erase(it_2);
                            }  
                            if(defend_army->empty()==false){
                                it_0=defend_army->erase(it_0);
                            }
                        }
                        ////////////////////////////////////
                    }
                }
                //deleting the personalities that took place in the battle with the attack army
                for(it=attack_army->begin(); it!=attack_army->end(); it++){
                    it_3=find(this->army->begin(),this->army->end(),*it);
                    if(this->army->empty()==false){
                        it_5=find(this->provinces->begin(),this->provinces->end(),*it_3);
                        if(it_5!=this->provinces->end()) 
                            it_5=this->provinces->erase(it_5);
                         delete *it_3;
                        it_3=this->army->erase(it_3);
                    }
                }
                delete attack_army;
                cout<<this->getName()<<",you just lost the battle!"<<attack_points-defence_points<<endl;
            }
        }                                 
        return lose;                                               
 }
