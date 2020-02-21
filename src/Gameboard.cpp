#include <iostream>
#include <fstream>
#include <iomanip>
#include "Gameboard.hpp"
#include <thread>
#include <chrono>

using namespace std;

Gameboard::Gameboard()
{
    players = new list<Player *>();
    playersNumber = 0;
}
/* Gameboard::Gameboard(const Gameboard& src)
:playersNumber{src.playersNumber}
{
    players = new list<Player *>();
    list<Player *>::iterator i;
    for(i = players->begin(); i != players->end(); i++)
    {
        players->push_back(new Player{(**i)});
    }
} */
Gameboard::~Gameboard()
{
    list<Player*>::iterator it;

    for(it = players->begin(); it != players->end();)
    {
        delete *it;
        players->erase(it);
        it = players->begin();
    }
    delete players;
}

void Gameboard::initializeGameboard(void)
{
    unsigned int decksizeF, decksizeD;
    string playerName;
    cout << "Determine the number of the players:\n>";
    cin >> playersNumber;
    while (playersNumber > 8 || playersNumber < 2 || !cin)
    {
        cout << "\nThe players must be from 2 up to 8. Try Again!" << endl;
        cout << "Determine the number of the players:\n>";
        cin >> playersNumber;
    }
    cout << "\nDetermine the max deck size for the fate deckboard (Pick a number from 40 up to 60):\n>";
    cin >> decksizeF;
    while (decksizeF > 60 || decksizeF < 40 || !cin)
    {
        cout << "You must type an integer at the range [40,60]" << endl;
        cout << "Determine the max deck size for the fate deckboard (Pick a number from 40 up to 60):\n>";
        cin >> decksizeF;
    }
    cout << "\nDetermine the max deck size for the dunasty deckboard (Pick a number from 40 up to 60):\n>";
    cin >> decksizeD;
    while (decksizeD > 60 || decksizeD < 40 || !cin)
    {
        cout << "You must type an integer at the range [40,60]" << endl;
        cout << "Determine the max deck size for the dynasty deckboard (Pick a number from 40 up to 60):\n>";
        cin >> decksizeD;
    }

    //we have the number of players in the game and also the decksizes at the decksizeD decksizeF variables
    for(int i=0; i<playersNumber; i++)
    {
        cout<<"PLease enter username for player:"<<endl;
        cin>>playerName;
        players->push_back(new Player{playerName});
    }

}

int PrintGameStatistics(const char *filename)
{

    std::ifstream in_file;
    //opening file
    in_file.open(filename);
    //testing if we opened the file
    if (!in_file)
    {
        std::cerr << "Problem opening file" << std::endl;
        return 1;
    }
    //std::cout<<"File is good to go"<<std::endl;

    //Store each line we read from the file
    std::string line{};
    //traverse the file line by line till eof
    while (std::getline(in_file, line))
    {
        std::cout <<line;//std::setw(100) << std::left << line;
        std::cout << std::endl;
    }

    in_file.close();
    return 0;
}

void Gameboard::printGameStatistics(void)
{
    PrintGameStatistics("./CardsStats/Personalities_and_Holdings.txt");
    PrintGameStatistics("./CardsStats/Followers_and_Weapons.txt");
}

void Gameboard::gameplay(void)
{   
    string s1="\t\t\tWelcome to the Legend of the Five Rings!!";
    string s2="\n\n~Now printing the game-statistics\n\n";
    for(char c: s1)
    {
        this_thread::sleep_for(std::chrono::milliseconds(20));
        cout<< "\033[1;31m"<<c<<"\033[0m"<<std::flush;
    }
    for(char ch: s2){
        this_thread::sleep_for(std::chrono::milliseconds(20));
        cout<< "\033[1;36m"<<ch<<"\033[0m"<< std::flush;
    }
    cout<<"\n\n";
    printGameStatistics();
    std::list<Player *> *players = new list<Player *>();
    bool instruction=true;
    string name,order;
    int counter=0;
    while(instruction==true){
       cout<<"Enter the name of player:\n\n";
       cin>>name;
       players->push_back(new Player{name});
       counter++;
       cout<<"Want to insert a new player?(Type yes||no)\n";
       cin>>order;
       if(!cin || (order!="yes" && order!="no"))
        {
            cout << "The answer is either a 'yes' or 'no'. Please, try again: ";
        }
        else if(order=="no") {
            if(counter>=2){
                instruction=false;
            }
            else{
                instruction=true;
                cout<<"There must be at least 2 players to initiate the game...Please insert another name\n";
            }    
        }
    }

    Gameplay(players);
}