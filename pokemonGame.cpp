//main driver
#include "Pokemon.cpp"
#include "Trainer.cpp"
#include "Location.cpp"
#include "Pokedex.cpp"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;


int main(){
    //initilization of early variables
    srand(time(NULL));
    string username;
    string starterChoice = "0";
    Pokemon starter;
    
    //intro text and starte choice
    cout << "Welcome to the world of Pokemon!" << endl;
    cout << "This world is filled with wonderful creatures called Pokemon. Pokemon live in harmony with humans and some people use them to fight." << endl;
    cout << "Please tell me your name?" << endl;
    getline(cin, username);
    cout << username << "! You will now embark on a journey in the C++ region! I hope you're ready for the challenge." << endl;
    cout << "If you collect 6 badges or 8 pokemon of different types you win the game!" << endl << endl;
    
    cout << "Now choose a starter pokemon to begin your adventure with. Please enter a number." << endl;
    cout << "1.Bulbasaur" << endl << "2.Charmander" << endl << "3.Squirtle" << endl << "4.Pikachu" << endl;
    
    //player error prevention
    while(starterChoice != "1" && starterChoice != "2" && starterChoice != "3" && starterChoice != "4"){
        getline(cin, starterChoice);
        if(starterChoice == "1" || starterChoice == "2" || starterChoice == "3" || starterChoice == "4"){
            break;
        }
        cout << "Invalid input. Please enter a number 1-4" << endl;
    }
    
    //Initialization of trainer and starter pokemon
    Trainer player;
    if(starterChoice == "1"){
        cout << "You have chosen Bulbasaur! Great choice!" << endl;
        starter.setPokemon(0);
        player.setLocation(340);
        player.join(starter);
    }else if(starterChoice == "2"){
        cout << "You have chosen Charmander! Great choice!" << endl;
        starter.setPokemon(3);
        player.setLocation(341);
        player.join(starter);
    }else if(starterChoice == "3"){
        cout << "You have chosen Squirtle! Great choice!" << endl;
        starter.setPokemon(6);
        player.setLocation(342);
        player.join(starter);
    }else if(starterChoice == "4"){
        cout << "You have chosen Pikachu! Great choice!" << endl;
        starter.setPokemon(24);
        player.setLocation(343);
        player.join(starter);
    }
    player.setPoints(10);           //points distinguishes from gym leaders
    
    
    //initialization of random wild pokemon across the map
    Pokemon wilds[20];
    Location randomLocation;
    for(int pos = 0; pos < 20; pos++){                          //loops for 20 pokemon
        bool possiblePokemonTravel = false;
        int pokedexNumber = rand() % 151;                       //random number 0 - 150
        wilds[pos].setPokemon(pokedexNumber);                   //sets random pokemon from text file
        
        while(!possiblePokemonTravel){                                                          //loops until a suitable wild pokemon space is found
            int locationNumber = rand() % 682 + 1;                                              //random position in the map
            possiblePokemonTravel = randomLocation.possiblePokeTravel(locationNumber);          //checks if position is a plains space
            if(possiblePokemonTravel){                                                          //if the space is suitable for a pokemon
                wilds[pos].setLocation(locationNumber);                                         //sets the position of the pokemon
            }
        }
    }
    
    
    //initialization of the gyms
    Trainer gyms[15];
    int gymLocations[15] = {99, 106, 138, 169, 239, 247, 298, 323, 349, 358, 445, 496, 544, 560, 577};      //all 15 gym positions on the map
    for(int pos = 0; pos < 15; pos++){                                          //loops for all gyms
        gyms[pos].setLocation(gymLocations[pos]);                               //sets location for gym
        gyms[pos].setBadges(1);                                                 //sets badges to 1
        
        int randPartySize = rand() % 6 + 1;                                     //random number 1 - 6 to represent the number of members on a team
        for(int vecPos = 0; vecPos < randPartySize; vecPos++){                  //loops for the party size
            Pokemon rando;                                                      
            int pokedexNumber = rand() % 151;
            rando.setPokemon(pokedexNumber);                                    //sets random pokemon
            gyms[pos].join(rando);                                              //random pokemon joins team
        }
    }
    
    //arrays check the positions of the player relative to their current location
    int twoByTwo[24] = {-22, -21, 1, 23, 22, 21, -1, -23, -44, -43, -42, -20, 2, 24, 46, 45, 44, 43, 42, 20, -2, -24, -46, -45};
    int threeByThree[48] = {-22, -21, 1, 23, 22, 21, -1, -23, -44, -43, -42, -20, 2, 24, 46, 45, 44, 43, 42, 20, -2, -24, -46, -45, -66, -65, -64, -63, -41, -19, 3, 25, 47, 69, 68, 67, 66, 65, 64, 63, 41, 19, -3, -25, -47, -69, -68, -67};
    
    
    //main game loop
    while(player.checkEnd() == false){          //ends when any of the win conditions are met
        player.updatePokemon();                 //updates the player's pokemon to the position of the player
        int option = player.options();          //checks which option a player chooses
        
        //travel option
        if(option == 1){
            int travelOption = player.travel();         //checks where a player traveled too
            cout << endl;
            
            //checks for wild pokemon near the player in a 2 square radius
            for(int pos = 0; pos < 24; pos++){                                                          //loops for all positions in radius
                for(int arrPos = 0; arrPos < 20; arrPos++){                                             //loops for all wild pokemon
                    if(wilds[arrPos].getLocation() == (player.getLocation() + twoByTwo[pos])){          //checks if there is a wild pokemon in the radius
                        
                        int wildOutcome = player.wildBattle(wilds[arrPos]);                                         //player battles the wild pokemon
                        if(wildOutcome == -1){                                                                      //checks if the player loses all their pokemon in the battle
                            player.setLocation(player.findPokeCenter());                                            //teleports player to nearest center
                            player.center();                                                                        //runs the pokemon center function
                        }else if(wildOutcome == 0){                                                                     //checks if the player runs from the wild pokemon
                            bool possiblePokemonTravel = false;                                                         //teleports the wild pokemon to a random suitable location
                            while(!possiblePokemonTravel){
                                int locationNumber = rand() % 682 + 1;
                                possiblePokemonTravel = randomLocation.possiblePokeTravel(locationNumber);
                                if(possiblePokemonTravel){
                                    wilds[arrPos].setLocation(locationNumber);
                                }
                            }
                        }else if(wildOutcome == 1){                                                                 //checks if the player beats the wild pokemon
                            wilds[arrPos].setLocation(1);                                                           //sends the pokemon to the "grave"
                        }
                    }
                }
            }
            if(travelOption == 2){              //checks if the player traveled to a pokemon center position
                player.center();                //runs the pokemon center function
            }else if(travelOption == 3){                                                                    //checks if the player traveled to a gym position
                for(int pos = 0; pos < 15; pos++){                                                          //loops for all gyms
                    if(gyms[pos].getLocation() == player.getLocation() && gyms[pos].getBadges() > 0){       //finds the matching gym leader
                        int gymOutcome = player.gym(gyms[pos]);                                             //runs the gym battle function between player and gym leader
                        if(gymOutcome == 0){                                                                    //checks if the player lost to the gym
                            player.setLocation(player.findPokeCenter());                                        //teleports player to nearest pokemon center
                            player.center();                                                                    //runs the pokemon center function
                        }else{                                                                              //if the player beats the gym
                            gyms[pos].setBadges(0);                                                         //sets the gym badge to 0 signaling the gym can't be battled again
                        }
                    }
                }
            }
            
        }else if(option == 2){          //checks if the player decided to rest
            player.rest();              //runs the rest function
            
        }else if(option == 3){          //checks if the player chose to try their luck
            bool found = false;                                                                                 //initializatioin of bool if pokemon was found
            for(int pos = 0; pos < 48; pos++){                                                                  //loops for all positions in 3 by 3 radius
                for(int arrPos = 0; arrPos < 20; arrPos++){                                                     //loops for all wild pokemon
                    if(wilds[arrPos].getLocation() == (player.getLocation() + threeByThree[pos])){              //checks if there is a wild pokemon in the radius
                        int luckOutcome = player.tryLuck(wilds[arrPos]);                                            //runs the tryLuck function
                        if(luckOutcome == 0){                                                                       //if the catch was unsuccessful
                            bool possiblePokemonTravel = false;                                                     //teleports pokemon to random location
                            while(!possiblePokemonTravel){
                                int locationNumber = rand() % 682 + 1;
                                possiblePokemonTravel = randomLocation.possiblePokeTravel(locationNumber);
                                if(possiblePokemonTravel){
                                    wilds[arrPos].setLocation(locationNumber);
                                }
                            }
                        }else{                                                                                      //if the pokemon was caught
                            wilds[arrPos].setLocation(1);                                                           //the original is sent to the "grave"
                        }
                        found = true;           //sets the bool true
                        break;                  //breaks out of loop so only one pokemon is found in tryLuck
                    }
                }
                if(found){                      //breaks out of loop so only one pokemon is found in tryLuck
                    break;
                }
            }
            if(!found){                                                                 //checks if no pokemon were found
                cout << "There were no pokemon near you. Bad luck!" << endl;            //output message
            }
        }else if(option == 4){          //checks if player chose to quit
            break;                      //breaks out of while loop
        }
        
        //moves wild pokemon one space
        int oneMovement[4] = {-22, 22, 1, -1};                                  //array with positions relative to the current position for cardinal directions
        for(int pos = 0; pos < 20; pos++){                                      //loops for all wild pokemon
            if(wilds[pos].getLocation() > 1){                                   //checks if the pokemon are not in the "grave"
                bool possiblePokemonTravel = false;                                                 //bool if a pokemon can travel in a certain position
                for(int arrPos = 0; arrPos < 4; arrPos++){                                          //loops for all cardinal directions
                    int locationNumber = wilds[pos].getLocation() + oneMovement[arrPos];            //sets the locationi if it suitable for a pokemon to move there
                    possiblePokemonTravel = randomLocation.possiblePokeTravel(locationNumber);
                    if(possiblePokemonTravel){
                        wilds[arrPos].setLocation(locationNumber);
                        break;
                    }
                }
            }
        }
        
        player.random();            //runs the random events
    }
    player.endGame("resultsPokemon.txt", username);         //after win conditions are met or the user quits, game results are written to a file and the game ends
}