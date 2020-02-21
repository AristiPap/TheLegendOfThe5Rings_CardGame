#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
void cleanWhitespace(string & str)
{
	int i;
	while((i=str.find(' ')) != string::npos){
		str.erase(str.begin()+i);
	}
}
class Katana
{
public:
	unsigned int Cost;
	unsigned int AttackBonus;
	unsigned int DefenseBonus;
	unsigned int MinimumHonor;
	unsigned int EffectBonus;
	unsigned int EffectCost;
	unsigned int Durability;

	Katana();
	~Katana();
	//void print(void);
};
Katana::Katana(){}
Katana::~Katana(){}
unsigned int getAttributes(const char* filename , const char* className, const char* attr)
{
	//cout << "HELLO";
	ifstream file{filename};
	if(!file) cout <<"" << endl;
	string line;
	while(!file.eof())
	{
		getline(file, line);
		if(line.find(className) != string::npos)
		{/*  cout << "FOUND "<< className << endl; */
			//here we have found katana item
			while(line != "" )
			{
				getline(file, line); ///get the new line
				if(line.find(attr) != string::npos)
				{ /* cout << "FOUND Cost" << endl; */
					//we have found the attribute we want to set
					cleanWhitespace(line); //clear the line from teh white spaces
					int i = line.find(':'); //locate the ':' symbol, to the right is the value of the attribute
					i++;
					unsigned int num=0;
					while(line[i] <= '9' && line[i] >= '0')
					{
						num = num*10 + line[i]-'0';
						i++;
					}
					//cout << line << endl;
					file.close();
					//cout << "++" << endl;
					return num;
				}
			}
		}
	}
	file.close();
	return -1;
}
/* int main(void)
{
	Katana katana;
	katana.Cost = getAttributes("./CardsStats/Followers_and_Weapons.txt", "KATANA", "AttackBonus");
	cout << katana.Cost << endl;
} */