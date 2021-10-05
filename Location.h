#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#ifndef Location_H
#define Location_H

class Location{
    private:
    int position;               //private data member for the single integer position
    int twoByTwo[24];           //private data member that holds all the positions two squares out from the position
    int threeByThree[48];       //private data member that holds all the positions three squares out from the position
    
    int water[153];             //private data member that holds the all the positions of a water space
    int centers[15];            //private data member that holds the all the positions of a Pokemon center space
    int gyms[15];               //private data member that holds the all the positions of a gym space
    int plains[217];            //private data member that holds the all the positions of a plain space
    int bounds[282];            //private data member that holds the all the positions of a space out of bounds
    
    public:
    Location();                     //default constructor
    void readMap(string);           //reads the map layout from a separate file
    int getPosition();              //gets a single number position
    void updateAll(int);            //sets a new position and updates the arrays
    int possibleTravel(int);        //checks if a position is in the water or out of bounds
    bool possiblePokeTravel(int);   //checks if a position is not a plains space
    int findCenter();               //finds the nearest pokemon center from the current location
    void displayMap();              //displays the a 7 by 7 map
    
};
#endif