#include "Pokemon.h"
#include "Location.h"
#include "Pokedex.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef TRAINER_H
#define TRAINER_H

class Trainer{
    private:
    int points;                         //private data member for the amount of points a trainer has
    int badges;                         //private data member for the amount of badges a trainer has
    int pokeballs;                      //private data member for the amount of pokeballs a trainer has
    Location map;                       //private data member for the location of a trainer
    Pokedex pc;                         //private data member for the pokemon a trainer has in their pokedex
    vector<Pokemon> party;              //private data member for the pokemon in their active party
    
    public:
    //constructors
    Trainer();
    Trainer(int, int, int, int);
    
    
    //getter functions
    int getPoints();
    int getBadges();
    int getPokeballs();
    int getLocation();
    int getPartySize();
    
    Pokemon getWholePokemon(int);
    string getPokemonName(int);
    int getPokemonNumber(int);
    int getPokemonHp(int);
    int getPokemonFullHp(int);
    int getPokemonAtk(int);
    int getPokemonDef(int);
    int getPokemonSpeed(int);
    int getPokemonMax(int);
    int getNumPokemon();
    
    
    //setter functions
    void setPoints(int);
    void setBadges(int);
    void setPokeballs(int);
    void setLocation(int);
    void updatePokemon();
    
    void setPokemonHp(int, int);
    void setPokemonFullHp(int, int);
    void setPokemonAtk(int, int);
    void setPokemonDef(int, int);
    void setPokemonSpeed(int, int);
    void pokemonLevelUp(int);
    
    //helper functions
    int findPokeCenter();                   //finds the nearest pokecenter
    void displayMap();                      //displays a 7x7 map around your current location
    int fight(Pokemon, Pokemon);            //the attacking procedure between two pokemon
    void swap(int);                         //switch the active pokemon with one in your party
    bool run(Pokemon, Pokemon, int);        //checks if a pokemon can run away from a wild pokemon
    void join(Pokemon);                     //adds a caught pokemon to your party or pokedex
    
    
    //Travel options
    int wildBattle(Pokemon);                //wild pokemon encounter procedure
    void center();                          //pokemon center procedure
    int gym(Trainer);                       //gym procedure
    
    
    //menu options
    int options();                          //provides the user with options to choose
    int travel();                           //moves the trainer location to a new location
    void rest();                            //increases all party pokemon health by 1
    int tryLuck(Pokemon);                   //checks if a wild pokemon is within a 3x3 area
    
    
    //end of turn checks
    void random();                          //runs through the random events
    bool checkEnd();                        //checks if any of the win conditions are met
    void endGame(string, string);           //quits the game and displays the high scores
};
#endif