#include "Pokemon.h"
#include "Location.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef POKEDEX_H
#define POKEDEX_H

class Pokedex{
    private:
    vector<Pokemon> box;    //private data memeber for the pokemon in the pokedex
    
    public:
    Pokedex();      //default constructor
    
    //getter functions
    int getDexSize();               //gets the size of the pokedex
    string getDexName(int);         //gets the name of an individual pokemon in the pokedex
    Pokemon getPokemon(int);        //gets the whole pokemon from the pokedex
    
    void updatePokedex(int);        //updates the position of the pokemon in the pokedex
    void addDex(Pokemon);           //adds a pokemon to the pokedex
};
#endif