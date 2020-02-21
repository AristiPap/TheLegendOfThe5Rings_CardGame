# The Legend of the 5 Rings

Foobar is a Python library for dealing with word pluralization.

## Creators

Aristi Papastavrou (sdi1800154@di.uoa.gr)       		 	   
Vissarion Moutafis (sdi1800119@di.uoa.gr)

## Compilation Options

We used a makefile to compile the whole program since there are many source files and the file hierarchy is divided to source files, includes, and a directory for the Card Statistics.

-To compile with no flags :
```bash
~$ make
```
-To compile and execute the program: 
```bash
~$ make run
```
-To compile, run and create a valgrind_out.txt file:
```bash
~$ make valgrind
```
-To clean the project:
```bash
~$ make clean
```
## Description

Every class and routine is implemented in accordance with the Assignment's readings.
For implementation specifications read further...

Given Files Specifications:
        We changed the syntax and behaviour of the most crucial functions since we implemented the classes of dynasty/fate cards with enumerations (also given in the notes of the reading)
        We also changed the destructor and constructor of deck builder class since it was unnecessary given the rest of the class design.
        Finaly, we changed the body of the deck creators according to our new enumarations and adjusted the design to fit this condition.

Start of the game:
        We just implemented a function to print the card statistics from the proper files, as well as getting the 2 players      
        names(at least 2 players) and then we continued with the following game phases:
        We also implemented a function 'Gameplay' that actually calls every one of the following ones for each player
        (with proper order and proper arguments.)
	      Also the functions in the Gameplay.cpp file call the related functions from the player class.

-> Starting Phase: 
                  The starting phase does exactly what is suppossed to do given the description in the reading but, as said             
                  earlier, it operates only in one player and is called at the start of current player's turn.
                  
-> Equip Phase: 
                The algorithm that operates here firstly, checks if the card chosen (given by a number) is in the related               
                list, after that checks the balance of the player and whether if he's able to buy the chosen fate card.
                Next he asks if the player wants to upgrade the card and after checking if this is possible, it may or may      
                not operate the upgrade. While all of these happen the related holding are being tapped when is needed.

-> Economy Phase: 
                 The economy phase is pretty much acting like the equip Phase but with the main differences that no upgrades    
                 are being conducted and we are dealing with dynasty cards and not fate cards,so if we buy a holding 
                 we must operate a check for the holding-chains that are specified by the reading.
   >>Chains: In detail,in order to check if we can create a chain,we traverse the list of the player's holdings.If there are any already-existing chains,(that contain different holdings than the one we currently have),or a single holding that can be connected with the current holding(according to the rules specified by the reading),we call the functions upper-holding/sub-holding accordingly.In these functions,we set the prev and the next of the current holding (as well as the prev and next of the other holding we are "connecting") and fix the new values of the holdings accordingly.

-> Battle Phase: 
               Gives the choice to the player playing at the moment(attacker) to choose the player he wants to   
               attack(defender).After the choice has been settled,we call the attack function.
             Steps followed in the attack function:
             1)the attacker chooses his army and the province he wants to attack
             2)Defender chooses his army
             3)we sum up the attack points from all the personalities/items that form the attacker's army
              (same with the defender's army-the initial defence is equal to the province's original cost)
             4)if the total of the attack points-total of defence points > initial defence points then the attacker wins.
               Else there are 3 different circumstances.
              ~if total_attack_points>total-defence-points tgen the defender loses all his army,
               the province gets destroyed and the attacker loses the personalities/followers whose value is equal 
               or greater than the (attack-points-defence points)
              ~attack points=defence points. Then it's a drawand both parties lose their armies
              ~total defence points>total attack points then the defender wins,attacker loses all his army and the defender           
              loses the personalities/followers whose value is equal/greater than the defence points-attack points difference
NOTE:Whenever we have to destroy an army or delete a personality/follower then we delete the "subarmy" created in the battle phase,and we erase the personality/follower from the player's army.
Attack returns true/false depending on whether the attacker won(first subcategory) or lost(all the other categories)                                             We added the choice for the player to skip the battle phase as it was difficult to showcase that the game could end.
~> Main Function: Calls the "gameplay",which welcomes the players to the game,prints the cars statistics, and then proceeds to create a list with the names of the participants. Finally in the body of the gameplay , we call the "Gameplay" function that we described at the beginning.                              

## Notes:

1.We added a color library to make the text and basically the titles of the cards quite distinct.

2.Also we added a delay effect at the beggining greeting the players so that we make the GUI Environment, a bit more interesting/intriguing.

3.We used some of the algorithms of the STL data structures, such as list.sort, to sort the players in descenting order.
Also we used a lambda expression in this particular case since the  default compare function was sorting in increasing order.

4. The card classes are implemented with enumerated types so that the type converter functions work properly and that's the basic reason we changed the DeckBuilder methods.

## Contributions
~Aristi Papastavrou implemented:

         From the Player.cpp:  attack,HasLost,printBattleArmy,printArmy,setchain functions
                              as well as the Player destructor
         From the Gameboard.cpp:  gameplay,PrintGameStatistics
         From the Gameplay.cpp: Battlephase and part of the Gameplay
         From the Holdings.cpp: all the functions from this file
         From the Personality.cpp: all the functions except the print functions
         From Cards.cpp:Greencard/Blackcard type functions
  
~VissarionMoutafis  implemented:
         
	  From the Player.cpp: buyProvince,equip,setProvinces as well as the remaining set
	                       functions,all the remaining printfunctions.
          From the Gameboard.cpp: InitialiseGameboard,and the gameboard destructor
          From the  Gameplay.cpp:Economy phase,Equip phase,Starting phase and part of Gameplay  
	  
	  From the Personality.cpp:all the print functions
	  From Cards.cpp: Card type functions 
          +fileread.cpp and Makefile
