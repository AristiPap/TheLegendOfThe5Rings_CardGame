#include "Gameplay.hpp"


//This function interprets the starting phase for a player:
void startingPhase(Player& player)
{
    cout << "\n\n \t" << BOLD(FYEL("~~~STARTING PHASE~~~")) << "\n" << endl;
    cout << "Untaping " << player.getName() << " cards..." << endl;
    player.untapEverything(); // untap all player's cards
    cout << player.getName() << " drawing a Fate card...";
    player.drawFateCard(); // draw a card from the fate deck
    player.revealProvinces(); // reveal all the provinces of the player
    cout << BOLD("\nPrinting " << player.getName() << "'s hand\n" )<< endl;
    player.printHand(); // print th ecurrent hand of the player
    cout << BOLD("\n \nPrinting " << player.getName() << "'s provinces" )<< endl;
    player.printProvinces(); // print all the releaved provinces
}
// function that imitates the equip phase for the player
void equipPhase(Player& player)
{
    cout << "\n\n \t" << BOLD(FYEL("~~~EQUIP PHASE~~~")) << "\n" << endl;
    cout << "Printing the hand of player: " << player.getName() << " ...\n" << endl;
    player.printHand(); // print the hand of current player
    cout << "Printing the army of player: " << player.getName() << " ...\n" << endl;
    //player.printArmy();
    cout << "Do you want to purchase any fate cards to enchance your personalities?('yes' or 'no'): ";
    string answer;
    do{ // get the answer and not some irrelevant one
        cin >> answer;
        if(!cin || (answer!="yes" && answer!="no"))
        {
            cout << "The answer is either a 'yes' or a 'no'. Please, try again: ";
        }
    } while (!cin || (answer != "yes" && answer != "no"));
    if(answer == "yes")
    {
        int cardNum,personNum;
        do
        {
            cout << "\nChoose a card from your hand(1 to " << player.getFateCardsNum() << "):";
            cin >> cardNum;
        }
        while(cardNum > player.getFateCardsNum() || !cin);
        
        do
        {
            cout << "\nChoose a personality from your army(1 to " << player.getArmyNum() << "):";
            cin >> personNum;
        } while (personNum > player.getArmyNum() || !cin);
        player.equip(personNum, cardNum);
    }
}

bool battlePhase(Player& attacker,list<Player* >* players,int playersNum)
{
    int defender;
    string instruction;
    bool nxt=true,check=false;
    cout<<"\n\n \t" << BOLD(FYEL("~~~BATTLE PHASE~~~")) << "\n" << endl;
    cout<<attacker.getName()<< ", do you want to proceed with an attack?(Type:yes || no)"<<endl;
    while(1){
        cin>>instruction;
        if(!cin || (instruction!="yes" && instruction!="no"))
        {
            cout << "The answer is either a 'yes' or 'no'. Please, try again: ";
        }
        else if(instruction=="no" ){
            return false;
        }
        else if(instruction=="yes"){
            break;
        }
    }    
    cout<<attacker.getName()<< " it's now time to choose the player you want to fight (choose a number between:1-"<<playersNum<<")"<<endl; 
    auto it=players->begin();
    do
    {
        cin >> defender; // get the proper holding from the list
        if (!cin || defender>players->size())
          cout << "Enter a valid number that represents a player..." << endl;
    } while (defender >players->size() || !cin);
    cout << endl;
    do{
       // cin>>defender;
        defender--;
        it=players->begin();
        it=next(players->begin(),defender);
        if(*it==&attacker){
            cout<<"You chose yourself to attack...You have to choose a different player.Please try again"<<endl;
            cin >> defender;
        }
    }while(*it==&attacker);

    while(nxt=true){ 
        check=attacker.attack(**it);
        if(check==true)
        {
            nxt=false;
            break;
        }
        else{
            cout<<attacker.getName()<<" do you want to attack again at the same player?(choose yes or no)"<<endl;
            cin>>instruction;
            //if(instruction == "yes") nxt=true;
            if(!cin || (instruction!="yes" && instruction!="no"))
            {
                cout << "The answer is either a 'yes' or 'no'. Please, try again: ";
            }
            else if(instruction=="yes" ){
                if(attacker.getArmyNum()>0)
                nxt=true;
                else{
                   nxt=false;
                   break;
                }
            }
            else if(instruction == "no")
            {
                nxt = false;
                break;
            }
        }
    }

    return check;
}

void economyPhase(Player &player)
{
    cout << "\n\n \t" << BOLD(FYEL("~~~ECONOMY PHASE~~~")) << "\n" << endl;
    cout << "Printing " << player.getName() << "'s releaved provinces..." << endl;
    player.printProvincesToBuy(); // print the provinces

    cout << "Do you want to purchase any dynasty cards? ('yes' or 'no'): " << endl;
    string answer;
    do{ // get the answer and not some irrelevant one
        cin >> answer;
        if(!cin || (answer!="yes" && answer!="no"))
        {
            cout << "The answer is either a 'yes' or 'no'. Please, try again: ";
        }
    } while (!cin || (answer != "yes" && answer != "no"));

    if(answer == "yes")
    {
        while(true)
        {
            int provinceID;
            cout << "\nChoose a card from the provinces above(1 to 4): " << endl;
            cin >> provinceID;
            if (provinceID <= 4){
                player.buyProvince(provinceID);
                break;
            }
            else
                cout << "\nWrong Input number. Try Again!\n";
        }
    }
}


void Gameplay(list<Player* >* players)
{
   int num_players;
   while(1)
   {
        //we want the players to get turns based on their honor
        //using a lambda expression and a operator> overload in order to accomplisha stylish way to sort the player list according to the current lap order.
        players->sort([](const Player* p1, const Player* p2)
        {
            return *p1 > *p2;
        });

        //now we can iterate the list and let every player get their turn
        for (auto player : *players)
        {
            startingPhase(*player);
            std::chrono::milliseconds(14);
            if (player->getArmyNum() != 0){
                // if the player has an army he can get items/followers to equip his personallities
                //or/and he can attack other players
                num_players=players->size();
                equipPhase(*player);
                std::chrono::milliseconds(10);
                if(battlePhase(*player,players,num_players) == true )
                {
                    cout << FYEL(UNDL(BOLD("THANKS FOR PLAYING !"))) << endl;
                    players->remove(player);
                    return;//} // exit the function
                }
            }
            std::chrono::milliseconds(10);
            economyPhase(*player);

            //checking if the fate deck is empty and if it is then we need to refresh it
            if(player->isFateDeckEmpty())
                player->refreshFateDeck();
            //same for the dynasty deck
            if(player->isDynastyDeckEmpty())
                player->refreshDynastyDeck();

            //end of the turn so the needed prints are taking place
            cout << BOLD(UNDL("\nPrinting " << player->getName() << "'s hand...")) << endl;
            player->printHand();
            cout << BOLD(UNDL("\nPrinting " << player->getName() << "'s provinces...")) << endl;
            player->printProvinces();
            cout << BOLD(UNDL("\nPrinting " << player->getName() << "'s arena..." ))<< endl;
            player->printArena();
        }
   }
} 
