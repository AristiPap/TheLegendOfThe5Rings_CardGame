#include "Holding.hpp"

using namespace std;

Holding::Holding()
{
    /* cout << "The default Holding constructor is being called" << endl; */
}

Holding::Holding(string _name, unsigned int _blackCardType)
:BlackCard(_name, HOLDING)
{
    string className;
    switch (_blackCardType)
    {
    case PLAIN:
        className = "PLAIN";
        break;
    case MINE:
        className = "MINE";
        break;
    case GOLD_MINE:
        className = "GOLD_MINE";
        break;
    case CRYSTAL_MINE:
        className = "CRYSTAL_MINE";
        break;
    case FARMS:
        className = "FARMS";
        break;
    case SOLO:
        className = "SOLO";
        break;
    case STRONGHOLD:
        className = "STRONGHOLD";
        break;
    }

    isReleaved = false;
    subHolding = NULL;
    upperHolding = NULL;
    cost = getAttributes("./CardsStats/Personalities_and_Holdings.txt", className.c_str(), "Cost");
    harvestValue = getAttributes("./CardsStats/Personalities_and_Holdings.txt", className.c_str(), "Harvest");
    blackCardType = _blackCardType;
}

Holding::~Holding()
{}

void Holding::print(void)
{
    string className;
    switch (blackCardType)
    {
    case PLAIN:
        className = BOLD(FRED("Plain"));
        break;
    case MINE:
        className = BOLD(FRED("Mine"));
        break;
    case GOLD_MINE:
        className = BOLD(FRED("Gold Mine"));
        break;
    case CRYSTAL_MINE:
        className = BOLD(FRED("Crystal Mine"));
        break;
    case FARMS:
        className = BOLD(FRED("Farm"));
        break;
    case SOLO:
        className = BOLD(FRED("Solo"));
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
    cout << "Harvest-Value: " << harvestValue << endl; 
}

Holding* Holding::getUpperHolding(){
    return upperHolding;
}

Holding* Holding::getSubHolding(){
    return subHolding;
}

unsigned int Holding::getHarvestValue(){
    return harvestValue;
}
///////////////////////////////////////////////

bool Holding::checkUpperHolding(Holding* ptr){
    if(ptr->subHolding==NULL){
        return true;
    }
    else{
        return false;
    }
}

bool Holding::checkSubHolding(Holding* ptr){
    if(ptr->upperHolding == NULL){
        return true;
    }
    else{
        return false;
    }
}

bool Holding::setUpperHolding(Holding* ptr){

    if(ptr->blackCardType<=CRYSTAL_MINE && ptr->blackCardType>=MINE){

        if(ptr->blackCardType==this->blackCardType+1){
            if(upperHolding == NULL )
            {
                int temp=this->harvestValue;
                //We have to set the subholder for the upholder we just set
              //  if(ptr->subHolding==NULL){
               //     ptr->setSubHolding(this);
               // }  
                upperHolding=ptr;
                if(this->blackCardType==MINE && ptr->blackCardType==GOLD_MINE && ptr->upperHolding==NULL){
                    harvestValue=temp+2;
                }
                else if(this->blackCardType==GOLD_MINE && this->subHolding==NULL){
                    harvestValue=temp+5;
                }
                else if(this->blackCardType==GOLD_MINE && this->subHolding->blackCardType==MINE && ptr->blackCardType==CRYSTAL_MINE){
                    harvestValue+=2*temp;
                }
                return true;
            }
        }
        else if(this->blackCardType >= ptr->blackCardType || ptr->blackCardType == this->blackCardType + 2){
           // cout<<"Can't set upper_holding.."<<endl;
            return false;
        }
    }
    else return false;
}
////////////////////////////////////////////////
bool Holding::setSubHolding(Holding* ptr){

    if(ptr->blackCardType>= MINE && ptr->blackCardType<=CRYSTAL_MINE){
        int temp=this->harvestValue;

        if(ptr->blackCardType==this->blackCardType-1){
            if(subHolding == NULL)
            {
                //We have to set the upholder for the subholder we just set
                //if(ptr->upperHolding==NULL){
                 subHolding=ptr;
                //ptr->setUpperHolding(this);
               // }
                if(this->blackCardType==GOLD_MINE && ptr->blackCardType==MINE)
                    harvestValue=temp+4;
                else if(this->blackCardType==CRYSTAL_MINE &&ptr->blackCardType==GOLD_MINE && ptr->subHolding==NULL)
                    harvestValue+=temp;
                else if(this->blackCardType==CRYSTAL_MINE && ptr->blackCardType==GOLD_MINE && ptr->subHolding->blackCardType==MINE)
                {
                    harvestValue+=3*temp;
                }
                return true;
            }
        }
        else if(this->blackCardType<=ptr->blackCardType || ptr->blackCardType == this->blackCardType - 2){
            //cout<<"Can't set sub_holding.."<<endl;
            return false;
        }
    } 
    else return false;
}
