#include "Trainer.h"
#include "Pokedex.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//default constructor
Pokedex::Pokedex(){
    box;
}

//gets the size of the pokedex
int Pokedex::getDexSize(){
    return box.size();
}

//gets the name of an individual pokemon in the pokedex
string Pokedex::getDexName(int index){
    if(index < box.size()){
        return box[index].getName();
    }else{
        return "ERROR";
    }
}

//gets the whole pokemon from the pokedex
Pokemon Pokedex::getPokemon(int index){
    return box[index];
}


//updates the position of the pokemon in the pokedex
void Pokedex::updatePokedex(int position){
    for(int pos = 0; pos < box.size(); pos++){
        box[pos].setLocation(position);
    }
}

//adds a pokemon to the pokedex
void Pokedex::addDex(Pokemon add){
    box.push_back(add);
}