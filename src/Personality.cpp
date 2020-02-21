#include "Personality.hpp"
/* Item Methods Implementation */
using namespace std;

Personality::Personality()
{
    /* cout << "The default constructor is being used!" << endl; */
}

Personality::Personality(string _name, unsigned int _blackCardType)
:BlackCard(_name, PERSONALITY)
{
    string className;
    switch(_blackCardType)
    {
        case ATTACKER: className = "ATTACKER";
        break;
        case DEFENDER: className = "DEFENDER";
        break;
        case SHOGUN: className = "SHOGUN";
        break;
        case CHANCELLOR: className = "CHANCELLOR";
        break;
        case CHAMPION: className = "CHAMPION";
        break;
    }
    cost = getAttributes("./CardsStats/Personalities_and_Holdings.txt", className.c_str(), "Cost");
    isReleaved =false;
    honor = getAttributes("./CardsStats/Personalities_and_Holdings.txt", className.c_str(), "Honor");
    attack= getAttributes("./CardsStats/Personalities_and_Holdings.txt", className.c_str(), "Attack");
    defence = getAttributes("./CardsStats/Personalities_and_Holdings.txt", className.c_str(), "Defense");
    isDead=false;
    blackCardType = _blackCardType;
}

Personality::~Personality(){
   for(auto it=followers.begin(); it!=followers.end(); it++){
       if(followers.empty()==false){
        delete *it;
        it=followers.erase(it);
        }   
   }
   for(auto ita=items.begin(); ita!=items.end(); ita++){
       if(items.empty()==false){
        delete *ita;
        ita=items.erase(ita);
        }   
   }

}

void Personality::print(void)
{
    string className;
    switch(blackCardType)
    {
        case ATTACKER: className = BOLD(FYEL("Attacker"));
        break;
        case DEFENDER: className = BOLD(FYEL("Defender"));
        break;
        case SHOGUN: className = BOLD(FYEL("Showgun"));
        break;
        case CHANCELLOR: className = BOLD(FYEL("Chancellor"));
        break;
        case CHAMPION: className = BOLD(FYEL("Champion"));
        break;
    }
    cout << endl;
    if (isTapped)
        cout << "~";
    else
        cout << " ";
    cout << "***" << className << "***" << endl;
    BlackCard::print();
    //Here we print the stats
    cout << "Attack: " << attack << endl;
    cout << "Defence: " << defence << endl;
    cout << "Honour: " << honor << endl;
}

unsigned int Personality::getHonour(void)
{
    return honor;
}
unsigned int Personality::getDefence(){
    return defence;
}
unsigned int Personality::getAttack(){
    return attack;
}
void Personality::ModifyItem(){
    if(items.size()!=0){
        for(auto it=items.begin(); it!=items.end(); it++){
            (**it).ReduceDurability();
            if((**it).getDurability()==0){
                items.remove(*it);
               // delete *it;
            }
        }
    }
}
void Personality::DetachFollower(int difference,bool attack){
    for(auto it_0=followers.begin(); it_0!=followers.end(); it_0++){
        if((**it_0).getAttackBonus()>=difference && attack==true){
            if(followers.empty()==false)
            followers.remove(*it_0);
            //delete *it_0;
        }
        else if((**it_0).getAttackBonus()>=difference && attack==false)
        {
            //list not empty
            if(followers.empty()==false)
            followers.remove(*it_0);
        }
    }

}

int Personality::DecreaseHonour(){
    this->honor--;
    return honor;
}
//call this function at equip stage
//when you equip your Personality with a Green Card,give option to PLayer to 
//upgrade his Green Card(Upgrade func).After we have equipped our personality
//call this function

void Personality::getBonus(GreenCard &ptr){
    Follower *follower_val;
    Item *item_val;
    TypeConverter obj;

    this->attack+=ptr.getAttackBonus();
    this->defence+=ptr.getDefenceBonus();
    
    obj.getCorrectType(&ptr,&follower_val,&item_val);
    if(follower_val!=NULL)
        followers.push_back(new Follower{*follower_val});
    else
        items.push_back(new Item{*item_val});    
}

void Personality::printItems(void)
{
    cout << UNDL(BOLD("\nItems:")) << endl;
    cout << BOLD("{") << endl;
    for(auto item : items)
    {
        item->print();
    }
    cout << BOLD("}") << endl;
}
void Personality::printFollowers(void)
{
    cout << UNDL(BOLD("\nFollowers:")) << endl;
    cout << BOLD("{") << endl;
    for (auto follower : followers)
    {
        follower->print();
    }
    cout << BOLD("}") << endl;
}
