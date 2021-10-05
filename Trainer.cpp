#include "Trainer.h"
#include "Pokemon.h"
#include "Location.h"
#include "Pokedex.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;


int split3(string phrase, char del, string words[], int size){
    if(phrase.length() == 0){                                   //checks if string input is empty
        return 0;
    }
    
    string piece = "";                                          //initialization of the string that will represent the pieces of the string
    int arrpos = 0;                                             //initialization of the position of the words array to store the piece in
    
    for(int pos = 0; pos < phrase.length(); pos++){             //loop continues until all positions of the original string has been checked
        if(phrase[pos] != del){                                 //checks if the position of the string is the delimeter
            piece = piece + phrase[pos];                        //adds the character of the position to the string piece
        }else{
            if(pos != 0 && pos != (phrase.length() - 1)){       //checks if the delimeter is not present in the first or last position of the string
                words[arrpos] = piece;                          //sets the string piece into an element of the words array
                piece = "";                                     //resets the string piece
                arrpos++;                                       //makes the next string piece to be in the next element in the words array
                
                int check = pos + 1;                            //initialization of a position next to the delimeter
                if(phrase[check] == del){                       //checks if there are back to back delimeters
                    pos++;                                      //skips the position on the second delimeter
                }
            }else{                                              //code for delimeters in the first or last position of the string
                if(pos == (phrase.length() - 1)){               //checks for delimeter in the last position
                    pos++;                                      //ends the for loop and skips the last delimeter
                }
            }
        }
    }
    words[arrpos] = piece;                                      //sets the most recent string piece into the array
    
    int count = arrpos + 1;                                     //initialization of the number of elements in the words array
    if(count > size){                                           //checks if the number of elements in the words array is larger than the array size
        return -1;
    }
    return count;                                               //returns the number of elements in words array
}

//default constructor
Trainer::Trainer(){
    points = 0;
    badges = 0;
    pokeballs = 10;
    map.updateAll(209);
    pc;
    party;
}

//parameterized constructor
Trainer::Trainer(int playerPoints, int playerBadges, int playerPokeballs, int playerMap){
    points = playerPoints;
    badges = playerBadges;
    pokeballs = playerPokeballs;
    map.updateAll(playerMap);
}


//getter functions
int Trainer::getPoints(){
    return points;
}

int Trainer::getBadges(){
    return badges;
}

int Trainer::getPokeballs(){
    return pokeballs;
}

int Trainer::getLocation(){
    return map.getPosition();
}

int Trainer::getPartySize(){
    return party.size();
}

Pokemon Trainer::getWholePokemon(int index){
    return party[index];
}

string Trainer::getPokemonName(int index){
    return party[index].getName();
}

int Trainer::getPokemonNumber(int index){
    return party[index].getNumber();
}

int Trainer::getPokemonHp(int index){
    return party[index].getHp();
}

int Trainer::getPokemonFullHp(int index){
    return party[index].getFullHp();
}

int Trainer::getPokemonAtk(int index){
    return party[index].getAtk();
}

int Trainer::getPokemonDef(int index){
    return party[index].getDef();
}

int Trainer::getPokemonSpeed(int index){
    return party[index].getSpeed();
}

int Trainer::getPokemonMax(int index){
    return party[index].getMax();
}

int Trainer::getNumPokemon(){
    return party.size();
}


//setter functions
void Trainer::setPoints(int playerPoints){
    points = playerPoints;
}

void Trainer::setBadges(int playerBadges){
    badges = playerBadges;
}

void Trainer::setPokeballs(int playerPokeballs){
    pokeballs = playerPokeballs;
}

void Trainer::setLocation(int playerMap){
    map.updateAll(playerMap);
}

void Trainer::updatePokemon(){
    for(int pos = 0; pos < party.size(); pos++){
        party[pos].setLocation(getLocation());
    }
    for(int pos = 0; pos < pc.getDexSize(); pos++){
        pc.updatePokedex(getLocation());
    }
}

void Trainer::setPokemonHp(int index, int newStat){
    party[index].setHp(newStat);
}

void Trainer::setPokemonFullHp(int index, int newStat){
    party[index].setFullHp(newStat);
}

void Trainer::setPokemonAtk(int index, int newStat){
    party[index].setAtk(newStat);
}

void Trainer::setPokemonDef(int index, int newStat){
    party[index].setDef(newStat);
}

void Trainer::setPokemonSpeed(int index, int newStat){
    party[index].setSpeed(newStat);
}

void Trainer::pokemonLevelUp(int index){
    party[index].levelUp();
}



//helper functions

//finds the nearest pokecenter
int Trainer::findPokeCenter(){
    return map.findCenter();
}

//displays a 7x7 map around your current location
void Trainer::displayMap(){
    map.readMap("mapPoke.txt");
    map.displayMap();
}

//the attacking procedure between two pokemon
int Trainer::fight(Pokemon attacker, Pokemon defender){
    srand(time(NULL));
    int atkStat = attacker.getAtk() + 1;
    int attack = rand() % atkStat;                      //attack number is a random number between 1 to the atk stat
    
    int defStat = defender.getDef() + 1;
    int defense = rand() % defStat;                     //defense number is a random number between 1 to the def stat
    
    int damage = attack - defense;                      //total damage dealt is atk - def
    if(damage > 0){
        return damage;                                  //returns the damage dealt
    }else{
        return 0;                                       //returns 0 as damage dealt if number is negative or 0
    }
}

//switch the active pokemon with one in your party
void Trainer::swap(int swap){
    vector<Pokemon> temporary;                                      //temporary vector for new order of party
    
    temporary.push_back(party[swap]);                               //first pokemon in new order is the pokemon being swapped
    for(int pos = 0; pos < party.size(); pos++){                    //loops for all pokemon in party
        if(party[pos].getName() != party[swap].getName()){          //skips the already added swapped pokemon
            temporary.push_back(party[pos]);                        //adds the rest of the pokemon in the vector
        }
    }
    
    while(!party.empty()){                                          //makes the party vector empty
        party.pop_back();
    }
    
    for(int pos = 0; pos < temporary.size(); pos++){                //fills the party vector with the temporary vector with the new order
        party.push_back(temporary[pos]);
    }
}

//checks if a pokemon can run away from a wild pokemon
bool Trainer::run(Pokemon one, Pokemon two, int attempts){
    srand(time(NULL));
    
    //initialization of variables in escape equation
    int A = one.getSpeed();
    int B = two.getSpeed() / 4;
    int C = attempts;
    int final = ((A * 32) / B) + (30 * C);
    
    int random = rand() % 256;          //random number between 0 and 255
    
    if(random < final){                 //if final is bigger than random, the pokemon escapes
        return true;
    }else{                              //if final is smaller than random, the pokemon fails to escape
        return false;
    }
}

//adds a caught pokemon to your party or pokedex
void Trainer::join(Pokemon wild){
    if(party.size() < 6){                       //checks if party is not filled
        party.push_back(wild);                  //adds pokemon to vector
        wild.setLocation(getLocation());        //sets the location to the trainer
    }else{
        //output message for if the party is filled and a pokemon is needed to send to the pc
        cout << wild.getName() << " is trying to join your party but it is full. Which pokemon would you like to send to your pokedex?" << endl;
        for(int pos = 0; pos < party.size(); pos++){
            cout << pos + 1 << ". " << getPokemonName(pos) << endl;
        }
        cout << "7. " << wild.getName() << endl;
        
        //player error prevention
        string option;
        while(option != "1" && option != "2" && option != "3" && option != "4" && option != "5" && option != "6" && option != "7"){
            getline(cin, option);
            if(option == "1" || option == "2" || option == "3" || option == "4" || option == "5" || option == "6" || option == "7"){
                break;
            }
            cout << "Please choose a number 1-7." << endl;
        }
        
        //adds the users choice to the pc
        int number = stoi(option);
        if(number == 7){            //checks if the newly added pokemon is the one sent to the pc
            pc.addDex(wild);
        }else{                      //if the newly added pokemon is added to party and a party pokemon is sent to pc
            pc.addDex(party[number - 1]);       //send the party pokemon to the pc
            
            //the newly cuaght pokemon is added within the party
            vector<Pokemon> temporary;
            for(int pos = 0; pos < party.size(); pos++){
                if(party[pos].getName() != party[number - 1].getName()){
                    temporary.push_back(party[pos]);
                }
            }
            temporary.push_back(wild);
            while(!party.empty()){
                party.pop_back();
            }
            for(int pos = 0; pos < temporary.size(); pos++){
                party.push_back(temporary[pos]);
            }
        }
    }
    wild.setLocation(getLocation());                                            //new pokemon updated position
    if(points > 0){                                                             //for a non gym trainer, the whole party is printed
        cout << "This is your full party now!" << endl;
        for(int pos = 0; pos < party.size(); pos++){
            cout << pos + 1 << ". " << getPokemonName(pos) << endl;
        }
        cout << endl;
    }
}




//Travel options

//wild pokemon encounter procedure
int Trainer::wildBattle(Pokemon wild){
    //output message to start battle
    cout << "You ran into a wild pokemon!" << endl;
    cout << wild.getName() << "-  HP:" << wild.getHp() << "  A:" << wild.getAtk() << "  D:" << wild.getDef() << "  S:" << wild.getSpeed() << "  M:" << wild.getMax() << endl;
    cout << "Your active pokemon:" << endl;
    cout << getPokemonName(0) << "-  HP:" << getPokemonHp(0) << "  A:" << getPokemonAtk(0) << "  D:" << getPokemonDef(0) << "  S:" << getPokemonSpeed(0) << "  M:" << getPokemonMax(0) << endl;
    
    int runAttempts = 1;    //intializes variable to count the number of times the user tries to run
    int turnCount = 1;      //count the number of turns in the battle
    
    //loop until the wild pokemon faints or all of the party pokemon faints
    while(wild.getHp() > 0){
        //output messages for user options with player error prevention
        cout << "----------Turn " << turnCount << "----------" << endl;
        cout << "What do you want to do? (pick 1, 2, or 3): " << endl;
        cout << "   1.Fight" << endl << "   2.Switch Active Pokemon" << endl << "   3.Run" << endl;
        string option = "0";
        while(option != "1"){
            getline(cin, option);
            if(option == "1" || option == "2" || option == "3"){
                break;
            }
            cout << "Please enter a number 1-3." << endl;
        }
        cout << endl;
        
        //fight option
        if(option == "1"){
            //case if the wild pokemon is faster
            if(wild.getSpeed() > getPokemonSpeed(0)){
                int damage1 = fight(wild, party[0]);                //finds the amount of damage the wild pokemon does
                cout << wild.getName() << " attacks first. " <<  wild.getName() << " deals " << damage1 << " damage." << endl;
                setPokemonHp(0, getPokemonHp(0) - damage1);         //sets the health of the trainer pokemon according to the damage it received
                if(getPokemonHp(0) < 0){                            //sets the health of the trainer pokemon to 0 if it reaches 0 or below
                    setPokemonHp(0, 0);
                }
                
                if(getPokemonHp(0) > 0){            //checks if the trainer pokemon has hp to fight
                    int damage2 = fight(party[0], wild);            //finds the amount of damage the trainer pokemon does
                    cout << getPokemonName(0) << " attacks back! " << getPokemonName(0) << " deals " << damage2 << " damage." << endl;
                    wild.setHp(wild.getHp() - damage2);             //sets the health of the wild pokemon according to the damage it received
                    if(wild.getHp() < 0){                           //sets the health of the wild pokemon to 0 if it reaches 0 or below
                        wild.setHp(0);
                    }
                }
                cout << endl;
            }
            
            //case if trainer pokemon is faster
            if(wild.getSpeed() <= getPokemonSpeed(0)){
                int damage1 = fight(party[0], wild);
                cout << getPokemonName(0) << " attacks first. " << getPokemonName(0) << " deals " << damage1 << " damage." << endl;
                wild.setHp(wild.getHp() - damage1);
                if(wild.getHp() < 0){
                    wild.setHp(0);
                }
                
                if(wild.getHp() > 0){               //checks if the wild pokemon has hp to fight
                    int damage2 = fight(wild, party[0]);
                    cout << wild.getName() << " attacks back! " << wild.getName() << " deals " << damage2 << " damage." << endl;
                    setPokemonHp(0, getPokemonHp(0) - damage2);
                    if(getPokemonHp(0) < 0){
                        setPokemonHp(0, 0);
                    }
                }
                cout << endl;
            }
            //output messages for the health each pokemon has after dealing damage to each other
            cout << wild.getName() << " has " << wild.getHp() << " HP remaing." << endl;
            cout << getPokemonName(0) << " has " << getPokemonHp(0) << " HP remaing." << endl << endl;
            
        }else if(option == "2"){        //switch option
            if(party.size() > 1){       //checks if there are pokemon to switch to
                //outputs the rest of the party
                cout << "Pick another active pokemon" << endl;
                for(int pos = 1; pos < party.size(); pos++){
                    cout << pos << ". " << getPokemonName(pos) << endl;
                }
                
                //choice of which pokemon to switch to and player error prevention
                string strChoice;
                int numberChoice;
                while(strChoice != "2o3irnf203idf032ifn0329"){
                    getline(cin, strChoice);
                    if(strChoice == "1" || strChoice == "2" || strChoice == "3" || strChoice == "4" || strChoice == "5"){
                        numberChoice = stoi(strChoice);
                        if(numberChoice < party.size() && getPokemonHp(numberChoice) > 0){          //ensures the pokemon to be switched has more than 0 hp
                            break;
                        }
                    }
                    cout << "Please enter a given number for a pokemon who is not fainted" << endl;
                }
                
                //switches active pokemon to the one chosen
                cout << getPokemonName(numberChoice) << " is now your active Pokemon!" << endl;
                swap(numberChoice);
                
                //wild pokemon attacks newly switched pokemon
                int damage1 = fight(wild, party[0]);
                cout << wild.getName() << " attacks. " << wild.getName() << " deals " << damage1 << " damage." << endl;
                setPokemonHp(0, getPokemonHp(0) - damage1);
                if(getPokemonHp(0) < 0){
                    setPokemonHp(0, 0);
                }
                
                cout << wild.getName() << " has " << wild.getHp() << " HP remaing." << endl;
                cout << getPokemonName(0) << " has " << getPokemonHp(0) << " HP remaing." << endl << endl;
                
            }else{          //case if player has only one pokemon in party
                cout << "You have no other pokemon to switch to." << endl;
            }
            
        }else if(option == "3"){        //run option
            bool escape = false;                                                    //initialization of bool to see if escape is successful
            escape = run(party[0], wild, runAttempts);                              //executes the run function
            if(escape){                                                             //checks if escape was successful
                cout << getPokemonName(0) << " ran away." << endl;                  //output message
                return 0;                                                           //exits out of wild battle function
            }else{                                                                  //if escape was not successful
                cout << getPokemonName(0) << " couldn't get away." << endl;         //output message
                runAttempts++;                                                      //increments the run attempts
                
                //wild pokemon attacks
                int damage1 = fight(wild, party[0]);
                cout << wild.getName() << " attacks. " << wild.getName() << " deals " << damage1 << " damage." << endl << endl;
                setPokemonHp(0, getPokemonHp(0) - damage1);
                if(getPokemonHp(0) < 0){
                    setPokemonHp(0, 0);
                }
                
                cout << wild.getName() << " has " << wild.getHp() << " HP remaing." << endl;
                cout << getPokemonName(0) << " has " << getPokemonHp(0) << " HP remaing." << endl << endl;
            }
        }
        
        //checks if active pokemon has 0 hp
        if(getPokemonHp(0) == 0){
            //checks if whole party has 0 hp
            int healthTotal = 0;
            for(int pos = 1; pos < party.size(); pos++){
                healthTotal += getPokemonHp(pos);
            }
            if(healthTotal == 0){               //exits function if the whole party has 0 hp
                cout << "You blacked out! You rush towards the nearest pokemon center..." << endl;
                return -1;
            }
            
            //switch active pokemon
            cout << getPokemonName(0) << " fainted. Please choose another pokemon to battle." << endl;
            for(int pos = 1; pos < party.size(); pos++){
                    cout << pos << ". " << getPokemonName(pos) << endl;
                }
                string strChoice;
                int numberChoice;
                while(strChoice != "209hfewpoifh0239hf"){
                    getline(cin, strChoice);
                    if(strChoice == "1" || strChoice == "2" || strChoice == "3" || strChoice == "4" || strChoice == "5"){
                        numberChoice = stoi(strChoice);
                        if(numberChoice < party.size() && getPokemonHp(numberChoice) > 0){
                            break;
                        }
                    }
                    cout << "Please enter a given number for a pokemon who is not fainted" << endl;
                }
                cout << getPokemonName(numberChoice) << " is now your active Pokemon!" << endl;
                swap(numberChoice);
        }
        turnCount++; //increments number of turns by 1
    }
    
    //checks if the wild pokemon has 0 hp
    if(wild.getHp() == 0){
        cout << "You defeated the wild pokemon! " << wild.getName() << " will now join your party and " << getPokemonName(0) << " will level up." << endl;
        wild.setHp(wild.getFullHp());
        join(wild);
        party[0].levelUp();
        pokeballs--;
        points += 10;
        return 1;
    }
}


//pokemon center procedure
void Trainer::center(){
    //heals all pokemon to full health
    for(int pos = 0; pos < party.size(); pos++){
        int fullHealth = party[pos].getFullHp();
        party[pos].setHp(fullHealth);
    }
    
    
    //asks to switch party
    string option;
    cout << endl << "Hello, and welcome to the Pokémon Center. We've restored your tired Pokémon to full health." << endl;
    
    //displays all pokemon in party and pc
    cout << "Here are all the pokemon in your party and pokedex:" << endl;
    int count = 1;
    for(int pos = 0; pos < party.size(); pos++){
        cout << count << ". " << getPokemonName(pos) << endl;
        count++;
    }
    for(int pos = 0; pos < pc.getDexSize(); pos++){
        cout << count << ". " << pc.getDexName(pos) << endl;
        count++;
    }
    
    //asks user if they want to change the 6 pokemon in their party with some from the pc
    if(pc.getDexSize() > 0){
        cout << "Would you like to change the members in your party? (Y/N):" << endl;
        
        //player error prevention for choosing to change parties or not
        while(option != "Y" && option != "N"){
            getline(cin, option);
            if(option == "Y" || option == "N"){
                break;
            }
            cout << "Please type Y to switch pokemon in your party or N to keep your party the same." << endl;
        }
        
        //changes party of pokemon
        if(option == "Y"){
            //player error prevention for 6 numbers of the pokemon ther want in their party
            string inputs;
            string partyNumbers[6];
            int numbers[6];
            cout << "Enter 6 numbers for pokemon you want in your party. Separate numbers with spaces." << endl;
            
            bool valid = false;
            while(!valid){
                getline(cin, inputs);
                if(split3(inputs, ' ', partyNumbers, 6) == 6){
                    for(int pos = 0; pos < 6; pos++){
                        int pokeNumber = stoi(partyNumbers[pos]);
                        numbers[pos] = pokeNumber;
                    }
                    break;
                }
                cout << "Please enter only 6 numbers and separate numbers with spaces." << endl;
            }
            
            vector<Pokemon> temporary;                                              //initialization of temporary vector of new party
            for(int pos = 0; pos < 6; pos++){                                       //for loop to add all the pokemon wanted in party
                int chosenNumber = numbers[pos];
                if(chosenNumber <= 6){
                    temporary.push_back(party[chosenNumber - 1]);
                }else{
                    temporary.push_back(pc.getPokemon(chosenNumber - 7));
                }
            }
            while(!party.empty()){
                party.pop_back();
            }
            for(int pos = 0; pos < temporary.size(); pos++){
                party.push_back(temporary[pos]);
            }
        }
        
        //output message to decide which pokemon in new party will be the active pokemon with player error prevention
        cout << "Here is your current party! Please choose which one will be the active pokemon." << endl;
        for(int pos = 0; pos < party.size(); pos++){
            cout << pos + 1 << ". " << getPokemonName(pos) << endl;
        }
        while(option != "1" && option != "2" && option != "3" && option != "4" && option != "5" && option != "6"){
            getline(cin, option);
            if(option == "1" || option == "2" || option == "3" || option == "4" || option == "5" || option == "6"){
                break;
            }
            cout << "Please enter a number 1-6." << endl;
        }
        int activePokemon = stoi(option);
        swap(activePokemon - 1);
        for(int pos = 0; pos < party.size(); pos++){
            cout << pos + 1 << ". " << getPokemonName(pos) << endl;
        }
    }
}

//gym procedure
int Trainer::gym(Trainer leader){
    //output messages
    cout << "Welcome to a gym! The gym leader has heard about your adventure and wants to battle you!" << endl;
    cout << "Their active pokemon: " << endl;
    cout << leader.getPokemonName(0) << "-  HP:" << leader.getPokemonHp(0) << "  A:" << leader.getPokemonAtk(0);
    cout << "  D:" << leader.getPokemonDef(0) << "  S:" << leader.getPokemonSpeed(0) << "  M:" << leader.getPokemonMax(0) << endl;
    cout << "Your active pokemon:" << endl;
    cout << getPokemonName(0) << "-  HP:" << getPokemonHp(0) << "  A:" << getPokemonAtk(0) << "  D:" << getPokemonDef(0) << "  S:" << getPokemonSpeed(0) << "  M:" << getPokemonMax(0) << endl;
    
    //intialization of variables
    bool leaderAlive = true;
    bool playerAlive = true;
    int turnCount = 1;
    
    //loops continues until one team has all pokemon fainted
    while(leaderAlive && playerAlive){
        //player option error prevention
        cout << "----------Turn " << turnCount << "----------" << endl;
        cout << "What do you want to do? (pick 1 or 2): " << endl;
        cout << "   1.Fight" << endl << "   2.Switch Active Pokemon" << endl;
        string option = "0";
        while(option != "1"){
            getline(cin, option);
            if(option == "1" || option == "2"){
                break;
            }
            cout << "Please enter a number 1-2." << endl;
        }
        
        //fight option(same as wild pokemon but with a trainer pokemon)
        if(option == "1"){
            if(leader.getPokemonSpeed(0) > getPokemonSpeed(0)){
                int damage1 = fight(leader.getWholePokemon(0), party[0]);
                cout << leader.getPokemonName(0) << " attacks first. " << leader.getPokemonName(0) << " deals " << damage1 << " damage." << endl;
                setPokemonHp(0, getPokemonHp(0) - damage1);
                if(getPokemonHp(0) < 0){
                    setPokemonHp(0, 0);
                }
                
                if(getPokemonHp(0) > 0){
                    int damage2 = fight(party[0], leader.getWholePokemon(0));
                    cout << getPokemonName(0) << " attacks back! " << getPokemonName(0) << " deals " << damage2 << " damage." << endl;
                    leader.setPokemonHp(0, leader.getPokemonHp(0) - damage2);
                    if(leader.getPokemonHp(0) < 0){
                        leader.setPokemonHp(0, 0);
                    }
                }
                cout << endl;
            }
            
            if(leader.getPokemonSpeed(0) <= getPokemonSpeed(0)){
                int damage1 = fight(party[0], leader.getWholePokemon(0));
                cout << getPokemonName(0) << " attacks first. " << getPokemonName(0) << " deals " << damage1 << " damage." << endl;
                leader.setPokemonHp(0, leader.getPokemonHp(0) - damage1);
                if(leader.getPokemonHp(0) < 0){
                    leader.setPokemonHp(0, 0);
                }
                
                if(leader.getPokemonHp(0) > 0){
                    int damage2 = fight(leader.getWholePokemon(0), party[0]);
                    cout << leader.getPokemonName(0) << " attacks back! " << leader.getPokemonName(0) << " deals " << damage2 << " damage." << endl;
                    setPokemonHp(0, getPokemonHp(0) - damage2);
                    if(getPokemonHp(0) < 0){
                        setPokemonHp(0, 0);
                    }
                }
                cout << endl;
            }
            cout << leader.getPokemonName(0) << " has " << leader.getPokemonHp(0) << " HP remaing." << endl;
            cout << getPokemonName(0) << " has " << getPokemonHp(0) << " HP remaing." << endl << endl;
            
        }else if(option == "2"){            //switch pokemon(same as wildBattle function)
            int playerHpTotal = 0;
            for(int pos = 1; pos < party.size(); pos++){
                playerHpTotal += getPokemonHp(pos);
            }
            if(party.size() > 1 && playerHpTotal > 0){
                cout << "Pick another active pokemon" << endl;
                for(int pos = 1; pos < party.size(); pos++){
                    cout << pos << ". " << getPokemonName(pos) << endl;
                }
                string strChoice;
                int numberChoice;
                while(strChoice != "209rj32-9fh32f9h084hf"){
                    getline(cin, strChoice);
                    if(strChoice == "1" || strChoice == "2" || strChoice == "3" || strChoice == "4" || strChoice == "5"){
                        numberChoice = stoi(strChoice);
                        if(numberChoice < party.size() && getPokemonHp(numberChoice) > 0){
                            break;
                        }
                    }
                    cout << "Please enter a given number for a pokemon who is not fainted" << endl;
                }
                cout << getPokemonName(numberChoice) << " is now your active Pokemon!" << endl;
                swap(numberChoice);
                
                int damage1 = fight(leader.getWholePokemon(0), party[0]);
                cout << leader.getPokemonName(0) << " attacks. " << leader.getPokemonName(0) << " deals " << damage1 << " damage." << endl;
                setPokemonHp(0, getPokemonHp(0) - damage1);
                if(getPokemonHp(0) < 0){
                    setPokemonHp(0, 0);
                }
                
                cout << leader.getPokemonName(0) << " has " << leader.getPokemonHp(0) << " HP remaing." << endl;
                cout << getPokemonName(0) << " has " << getPokemonHp(0) << " HP remaing." << endl << endl;
                
            }else{
                cout << "You have no other pokemon to switch to." << endl;
            }
        }
        
        //checks if gym leaders active pokemon has 0 hp
        if(leader.getPokemonHp(0) == 0){
            //checks if the leader has another alive pokemon
            int leaderHpTotal = 0;
            for(int pos = 1; pos < leader.getPartySize(); pos++){
                leaderHpTotal += leader.getPokemonHp(pos);
            }
            if(leaderHpTotal == 0){
                leaderAlive = false;
            }else{          //if there are pokemon still alive
                //sends out first non fainted pokemon in party as the active pokemon
                for(int pos = 0; pos < leader.getPartySize(); pos++){
                    if(leader.getPokemonHp(pos) > 0){
                        cout << leader.getPokemonName(0) << " has fainted. They will now send out " << leader.getPokemonName(pos) << endl;
                        leader.swap(pos);
                        break;
                    }
                }
            }
        }
        
        //checks if player pokemon has 0 hp
        if(getPokemonHp(0) == 0){
            //checks the whole team hp
            int playerHpTotal = 0;
            for(int pos = 1; pos < party.size(); pos++){
                playerHpTotal += getPokemonHp(pos);
            }
            if(playerHpTotal == 0){
                playerAlive = false;
            }else{
                //output message and player error prevention for swapping a pokemon that is alive as the active pokemon
                cout << getPokemonName(0) << " fainted. Please choose another pokemon to battle." << endl;
                for(int pos = 1; pos < party.size(); pos++){
                    cout << pos << ". " << getPokemonName(pos) << endl;
                }
                string strChoice;
                int numberChoice;
                while(strChoice != "209hfewpoifh0239hf"){
                    getline(cin, strChoice);
                    if(strChoice == "1" || strChoice == "2" || strChoice == "3" || strChoice == "4" || strChoice == "5"){
                        numberChoice = stoi(strChoice);
                        if(numberChoice < party.size() && getPokemonHp(numberChoice) > 0){
                            break;
                        }
                    }
                    cout << "Please enter a given number for a pokemon who is not fainted" << endl;
                }
                cout << getPokemonName(numberChoice) << " is now your active Pokemon!" << endl;
                swap(numberChoice);
            }
        }
        turnCount++;
    }
    
    //checks if the leader has no more alive pokemon
    if(!leaderAlive){
        leader.setBadges(0);                        //sets the gyms badges to 0
        setBadges(getBadges() + 1);                 //adds 1 to the players badges
        setPoints(getPoints() + 60);                //adds 60 points to the player
        setPokeballs(getPokeballs() + 5);           //adds 5 pokeballs to the player
        
        cout << "Congratulations! You just beat the gym. You have gained a badge, 60 points, 5 pokeballs, and the gym leader's pokemon." << endl << endl;
        
        //adds all the gyms pokemon to the player party
        for(int pos = 0; pos < leader.getPartySize(); pos++){
            join(leader.getWholePokemon(pos));
        }
        return 1;
    }else if(!playerAlive){     //case if the players team dies first
        cout << "You blacked out! You rush towards the nearest pokemon center..." << endl << endl;
        return 0;
    }
}




//menu options

//moves the trainer location to a new location
int Trainer::travel(){
    //player error prevention for picking direction to travel in
    bool posTravel = false;
    while(!posTravel){
        cout << "Would you like to travel North, East, South, or West? (N, E, S, W)" << endl;
        string option = "0";
        while(option != "N"){
            getline(cin, option);
            if(option == "N" || option == "E" || option == "S" || option == "W"){
                break;
            }
            cout << "Please enter N, E, S, or W." << endl;
        }
        
        //reads the user's option to travel and checks if it is a possible position a player can travel to
        map.readMap("mapPoke.txt");
        if(option == "N"){
            int possiblePos = map.getPosition() - 22;
            if(map.possibleTravel(possiblePos) != -1){
                map.updateAll(possiblePos);
                updatePokemon();
                posTravel = true;
            }
        }else if(option == "E"){
            int possiblePos = map.getPosition() + 1;
            if(map.possibleTravel(possiblePos) != -1){
                map.updateAll(possiblePos);
                updatePokemon();
                posTravel = true;
            }
        }else if(option == "S"){
            int possiblePos = map.getPosition() + 22;
            if(map.possibleTravel(possiblePos) != -1){
                map.updateAll(possiblePos);
                updatePokemon();
                posTravel = true;
            }
        }else if(option == "W"){
            int possiblePos = map.getPosition() - 1;
            if(map.possibleTravel(possiblePos) != -1){
                map.updateAll(possiblePos);
                updatePokemon();
                posTravel = true;
            }
        }
        
        if(!posTravel){
            cout << "You cannot travel in this direction. Please choose another direction." << endl;
        }
    }
    return map.possibleTravel(getLocation());       //returns an integer to represent the type of space the player is in
}

//increases all party pokemon health by 1
void Trainer::rest(){
    pokeballs--;
    for(int pos = 0; pos < party.size(); pos++){
        int currentHealth = party[pos].getHp();
        if(currentHealth < party[pos].getFullHp()){             //heals pokemon by 1 if they don't already have full hp
            party[pos].setHp(currentHealth + 1);
        }
    }
    cout << "Your pokemon have rested a bit." << endl;
}

//checks if a wild pokemon is within a 3x3 area
int Trainer::tryLuck(Pokemon wild){
    cout << wild.getName() << " was found near you. What good luck!" << endl;
    srand(time(NULL));
    int random = rand() % 2;
    if(random == 0){
        cout << "Unfortunately you were not able to catch " << wild.getName() << endl;
        return 0;
    }else if(random == 1){
        cout << "You were able to catch " << wild.getName() << " for free!" << endl;
        pokeballs--;
        join(wild);
        return 1;
    }
}

//provides the user with options to choose
int Trainer::options(){
    cout << endl;
    map.readMap("mapPoke.txt");
    map.displayMap();
    cout << "Here are your stats! You have " << getPokeballs() << " pokeballs left. ";
    cout << "You also have " << getBadges() << " badges and " << getPoints() << " points." << endl;
    cout << "Here are your Pokemon party's stats." << endl;
    for(int pos = 0; pos < party.size(); pos++){
        cout << "   " << pos + 1 << ". " << getPokemonName(pos) << "-  HP:" << getPokemonHp(pos) << "  A:" << getPokemonAtk(pos) << "  D:" << getPokemonDef(pos) << "  S:" << getPokemonSpeed(pos) << "  M:" << getPokemonMax(pos) << endl;
    }
    
    cout << "Please choose from the following options:" << endl << "    1.Travel" << endl;
    cout << "    2.Rest" << endl << "    3.Try your luck" << endl << "    4.Quit" << endl;
    
    string option;
    while(option != "1"){
        getline(cin, option);
        if(option == "1" || option == "2" || option == "3" || option == "4"){
            break;
        }
        cout << "Please enter a number 1-4." << endl;
    }
    int number = stoi(option);
    return number;
}


//end of turn checks

//runs through the random events
void Trainer::random(){
    srand(time(NULL));
    
    //random pokemon appearing to catch or release
    int thirtyPercent = rand() % 10;
    int random151 = rand() % 151;
    if(thirtyPercent < 3){
        Pokemon randomPoke;
        randomPoke.setPokemon(random151);
        string option;
        cout << "Suddenly, " << randomPoke.getName() << " appears on your path. Do you want to:" << endl;
        cout << "   1. Catch it" << endl << "   2. Release it" << endl;
        while(option != "1"){
            getline(cin, option);
            if(option == "1" || option == "2"){
                break;
            }
            cout << "Please enter a number 1-2." << endl;
        }
        if(option == "1"){
            pokeballs--;
            join(randomPoke);
        }else if(option == "2"){
            cout << randomPoke.getName() << " was released." << endl;
            randomPoke.setLocation(1);
        }
    }
    
    //hidden treasure chance
    int twentyFivePercent = rand() % 8;
    if(twentyFivePercent < 2){
        //pokeball treasure
        if(twentyFivePercent == 0){
            cout << "You have stumbled upon a hidden treasure of pokeballs!" << endl;
            setPokeballs(getPokeballs() + 2);
            cout << "You now have " << getPokeballs() << " pokeballs." << endl;
        }
        
        //rare candy
        if(twentyFivePercent == 1){
            cout << "You have stumbled upon a rare candy! You can use it to level up one of your pokemon. Which pokemon would you like to choose?" << endl;
            for(int pos = 0; pos < party.size(); pos++){
                cout << "   " << pos + 1 << ". " << getPokemonName(pos) << endl;
            }
            string option;
            int number;
            while(option != "1"){
                getline(cin, option);
                if(option == "1" || option == "2" || option == "3" || option == "4" || option == "5" || option == "6"){
                    number = stoi(option);
                    if(number <= party.size()){
                        break;
                    }
                }
                cout << "Please enter a number 1-" << party.size() << "." << endl;
            }
            party[number - 1].levelUp();
            cout << getPokemonName(number - 1) << " leveled up." << endl;
        }
    }
    
    //random chance of active pokemon getting 0 health
    int twentyPercent = rand() % 5;
    if(twentyPercent == 1){
        if(party.size() > 1){
            cout << getPokemonName(0) << " has randomly been poisoned and has fainted. " << getPokemonName(0) << " now has 0 HP." << endl;
            
            //checks if this is the only pokemon alive
            int totalHealth = 0;
            for(int pos = 1; pos < party.size(); pos++){
                totalHealth += getPokemonHp(pos);
            }
            if(totalHealth == 0){
                cout << "Luckily you found a revive and " << getPokemonName(0) << " is back to health." << endl;
            }else{
                //sets the active pokemon hp to 0 and switches active pokemon
                for(int pos = 1; pos < party.size(); pos++){
                    if(getPokemonHp(pos) > 0){
                        cout << getPokemonName(pos) << " will now be your active Pokemon." << endl;
                        setPokemonHp(0, 0);
                        swap(pos);
                        break;
                    }
                }
            }
        }
    }
}

//checks if any of the win conditions are met
bool Trainer::checkEnd(){
    bool badgeWin = false;
    bool typeWin = false;
    
    //badge win condition
    if(getBadges() >= 6){
        badgeWin = true;
    }
    
    //8 different types win condition
    vector<string> totalTypes;
    for(int pos = 0; pos < party.size(); pos++){
        bool unique = true;
        for(int vecPos = 0; vecPos < totalTypes.size(); vecPos++){
            if(totalTypes[vecPos] == party[pos].getTypes(1)){
                unique = false;
            }
        }
        if(unique){
            totalTypes.push_back(party[pos].getTypes(1));
        }
        if(party[pos].getNumTypes() > 1){
            bool unique2 = true;
            for(int vecPos = 0; vecPos < totalTypes.size(); vecPos++){
                if(totalTypes[vecPos] == party[pos].getTypes(2)){
                    unique2 = false;
                }
            }
            if(unique2){
                totalTypes.push_back(party[pos].getTypes(2));
            }
        }
    }
    
    
    for(int pos = 0; pos < pc.getDexSize(); pos++){
        bool unique = true;
        for(int vecPos = 0; vecPos < totalTypes.size(); vecPos++){
            if(totalTypes[vecPos] == pc.getPokemon(pos).getTypes(1)){
                unique = false;
            }
        }
        if(unique){
            totalTypes.push_back(pc.getPokemon(pos).getTypes(1));
        }
        if(pc.getPokemon(pos).getNumTypes() > 1){
            bool unique2 = true;
            for(int vecPos = 0; vecPos < totalTypes.size(); vecPos++){
                if(totalTypes[vecPos] == pc.getPokemon(pos).getTypes(2)){
                    unique2 = false;
                }
            }
            if(unique2){
                totalTypes.push_back(pc.getPokemon(pos).getTypes(2));
            }
        }
    }
    
    int totalPokemon = party.size() + pc.getDexSize();
    if(totalTypes.size() >= 8 && totalPokemon >= 8){
        typeWin = true;
    }
    
    //if either conditions are met, return true
    if(typeWin || badgeWin){
        return true;
    }else{
        return false;
    }
}

//quits the game and displays the high scores
void Trainer::endGame(string text, string name){
    bool win = false;
    if(checkEnd() == true){
        win = true;
    }
    
    //writing score to a results file
    if(win){
        cout << name << "! Congratulations on your successful journey throughout the C++ region. You win!" << endl;
        cout << "You ended with " << points << " points." << endl;
        ofstream file;
        file.open(text, ios::app);
        
        if(file.is_open()){
            file << name;
            if(name.length() < 18){
                for(int space = 0; space < 17 - name.length(); space++){
                    file << " ";
                }
            }else{
                file << " ";
            }
            file << "Y" << "       " << points << endl;
            file.close();
        }else{
            cout << "Can't open file." << endl;
        }
    }else{
        cout << "Come journey through the C++ region again later! You ended with " << points << " points." << endl;
        
        ofstream file;
        file.open(text, ios::app);
        
        if(file.is_open()){
            file << name;
            if(name.length() < 18){
                for(int space = 0; space < 17 - name.length(); space++){
                    file << " ";
                }
            }else{
                file << " ";
            }
            file << "N" << "       " << points << endl;
            file.close();
        }else{
            cout << "Can't open file." << endl;
        }
    }
}