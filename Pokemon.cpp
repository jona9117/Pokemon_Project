#include "Pokemon.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int split2(string phrase, char del, string words[], int size){
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
Pokemon::Pokemon(){
    name = "q";
    number = 0;
    hp = 0;
    fullHp = hp;
    atk = 0;
    def = 0;
    speed = 0;
    max = 0;
    current.updateAll(209);
    types;
}


//getter functions
int Pokemon::getNumber(){
    return number;
}

string Pokemon::getName(){
    return name;
}

int Pokemon::getHp(){
    return hp;
}

int Pokemon::getFullHp(){
    return fullHp;
}

int Pokemon::getAtk(){
    return atk;
}

int Pokemon::getDef(){
    return def;
}

int Pokemon::getSpeed(){
    return speed;
}

int Pokemon::getMax(){
    return max;
}

int Pokemon::getLocation(){
    return current.getPosition();
}

int Pokemon::getNumTypes(){
    return types.size();
}

string Pokemon::getTypes(int number){
    if(number == 1){
        return types.at(0);
    }else if(number == 2 && types.size() == 2){
        return types.at(1);
    }
}


//setter functions
void Pokemon::setNumber(int pokeNum){
    number = pokeNum;
}

void Pokemon::setName(string pokeName){
    name = pokeName;
}

void Pokemon::setHp(int pokeHp){
    hp = pokeHp;
}

void Pokemon::setFullHp(int pokeFullHp){
    fullHp = pokeFullHp;
}

void Pokemon::setAtk(int pokeAtk){
    atk = pokeAtk;
}

void Pokemon::setDef(int pokeDef){
    def = pokeDef;
}

void Pokemon::setSpeed(int pokeSpeed){
    speed = pokeSpeed;
}

void Pokemon::setMax(int pokeMax){
    max = pokeMax;
}

void Pokemon::setLocation(int pokeCurrent){
    current.updateAll(pokeCurrent);
}

void Pokemon::setType(string pokeType){
    types.push_back(pokeType);
}


//reads the pokemon file and stores all the stats of the 151 pokemon
void Pokemon::readKanto(string text, Pokemon kanto[]){
    ifstream file;                                              //initialization of file
    file.open(text);                                            //call to open the file
    
    if(file.is_open()){                                         //checks if file can open
        string line = "";                                       //initialization of empty string to take lines from outside file
        string sort[9];                                         //initialization of string array to sort between pokemon attributes
        int count = 0;                                          //initialization of counting array position
        int check = 0;                                          //initialization of integer to check if the first line is read
        
        while(getline(file, line)){                             //loops for every line in the file
            if(line.length() != 0 && check > 0){                //checks if the line is not empty
                split2(line, ',', sort, 9);                      //uses the split function to split pokemon attributes
                
                kanto[count].setNumber(stoi(sort[0]));          //sets the pokemon number
                kanto[count].setName(sort[1]);                  //sets the pokemon name
                kanto[count].setHp(stoi(sort[2]));              //sets the pokemon hp
                kanto[count].setFullHp(stoi(sort[2]));          //sets the pokemon full hp
                kanto[count].setAtk(stoi(sort[3]));             //sets the pokemon atk
                kanto[count].setDef(stoi(sort[4]));             //sets the pokemon def
                kanto[count].setSpeed(stoi(sort[5]));           //sets the pokemon speed
                kanto[count].setMax(stoi(sort[6]));             //sets the pokemon max
                kanto[count].setType(sort[7]);                  //sets the pokemon type
                
                if(sort[8] != ""){                              //checks if the pokemon has a second type
                    kanto[count].setType(sort[8]);              //sets the pokemon type
                }
                
                count++;                                        //increments the count by 1
                sort[8] = "";                                   //sets the second type to an empty string
            }
            check++;                                            //adds 1 to check
        }
        file.close();                                           //close the file
    }
}

//sets the private data members from a pokemon with the readKanto function
void Pokemon::setPokemon(int index){
    Pokemon kanto[152];
    readKanto("pokemon.txt", kanto);
    
    //sets all pokemon attributes from the outside file
    setNumber(kanto[index].getNumber());
    setName(kanto[index].getName());
    setHp(kanto[index].getHp());
    setFullHp(kanto[index].getHp());
    setAtk(kanto[index].getAtk());
    setDef(kanto[index].getDef());
    setSpeed(kanto[index].getSpeed());
    setMax(kanto[index].getMax());
    setType(kanto[index].getTypes(1));
    if(kanto[index].getNumTypes() == 2){
        setType(kanto[index].getTypes(2));
    }
    
}


void Pokemon::levelUp(){
    int increase;
    
    if(fullHp % 50 == 0){
        increase = (fullHp / 50) + fullHp;
        setHp((fullHp / 50) + hp);
    }else{
        increase = (fullHp / 50) + fullHp + 1;
        setHp((fullHp / 50) + hp + 1);
    }
    setFullHp(increase);
    
    
    if(speed % 50 == 0){
        increase = (speed / 50) + speed;
    }else{
        increase = (speed / 50) + speed + 1;
    }
    setSpeed(increase);
    
    
    if(atk < max){
        if(atk % 50 == 0){
            increase = (atk / 50) + atk;
        }else{
            increase = (atk / 50) + atk + 1;
        }
        setAtk(increase);
    }
    
    
    if(def < max){
        if(def % 50 == 0){
            increase = (def / 50) + def;
        }else{
            increase = (def / 50) + def + 1;
        }
        setDef(increase);
    }
}