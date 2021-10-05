#include "Location.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#ifndef Pokemon_H
#define Pokemon_H

class Pokemon{
    private:
    string name;                    //private data member for the pokemon name
    int number;                     //private data member for the pokemon number
    int hp;                         //private data member for the pokemon hp
    int fullHp;                     //private data member for the pokemon hp at full health
    int atk;                        //private data member for the pokemon atk
    int def;                        //private data member for the pokemon def
    int speed;                      //private data member for the pokemon speed
    int max;                        //private data member for the pokemon max
    Location current;               //private data member for the location of the pokemon
    vector<string> types;           //private data member for the pokemon's types
    
    public:
    //constructors
    Pokemon();                      //default constructor
    
    //getter functions
    int getNumber();
    string getName();
    int getHp();
    int getFullHp();
    int getAtk();
    int getDef();
    int getSpeed();
    int getMax();
    int getLocation();
    int getNumTypes();
    string getTypes(int);          //returns the types of a pokemon
    
    //setter functions
    void setNumber(int);
    void setName(string);
    void setHp(int);
    void setFullHp(int);
    void setAtk(int);
    void setDef(int);
    void setSpeed(int);
    void setMax(int);
    void setLocation(int);
    void setType(string);
    
    void readKanto(string, Pokemon kanto[]);            //reads the pokemon file of all the kanto pokemon
    void setPokemon(int);                               //sets most private data members of a pokemon from the file
    void levelUp();
    
};
#endif