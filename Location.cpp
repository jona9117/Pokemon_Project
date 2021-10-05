#include "Location.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int split(string phrase, char del, string words[], int size){
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

//reads the map layout from a separate file
void Location::readMap(string text){
    vector<int> w;
    vector<int> c;
    vector<int> g;
    vector<int> p;
    vector<int> b;
    
    ifstream file;                                              //initialization of file
    file.open(text);                                            //call to open the file
    
    if(file.is_open()){                                         //checks if file can open
        string line = "";                                       //initialization of empty string to take lines from outside file
        string sort[22];                                        //initialization of string array to sort between pokemon attributes
        int rowCount = 0;                                       //initialization of counting array position
        
        while(getline(file, line)){                             //loops for every line in the file
            if(line.length() != 0){                             //checks if the line is not empty
                split(line, ',', sort, 22);                     //uses the split function to split pokemon attributes
                for(int pos = 0; pos < 22; pos++){
                    int position = (rowCount * 22) + 1 + pos;
                    if(sort[pos] == "w"){
                        w.push_back(position);
                    }else if(sort[pos] == "C"){
                        c.push_back(position);
                    }else if(sort[pos] == "G"){
                        g.push_back(position);
                    }else if(sort[pos] == "p"){
                        p.push_back(position);
                    }else if(sort[pos] == "/"){
                        b.push_back(position);
                    }
                }
                rowCount++;
            }
        }
        for(int pos = 0; pos < w.size(); pos++){
            water[pos] = w.at(pos);
        }
        for(int pos = 0; pos < c.size(); pos++){
            centers[pos] = c.at(pos);
        }
        for(int pos = 0; pos < g.size(); pos++){
            gyms[pos] = g.at(pos);
        }
        for(int pos = 0; pos < p.size(); pos++){
            plains[pos] = p.at(pos);
        }
        for(int pos = 0; pos < b.size(); pos++){
            bounds[pos] = b.at(pos);
        }
        file.close();                                           //close the file
    }
}


//default constructor
Location::Location(){
    position = 209;
}

//gets a single number position
int Location::getPosition(){
    return position;
}

//sets a new position and updates the arrays
void Location::updateAll(int newPosition){
    position = newPosition;
    int movement[48] = {-69, -68, -67, -66, -65, -64, -63, -47, -46, -45, -44, -43, -42, -41, -25, -24, -23, -22, -21, -20, -19, -3, -2, -1, 1, 2, 3, 19, 20, 21, 22, 23, 24, 25, 41, 42, 43, 44, 45, 46, 47, 63, 64, 65, 66, 67, 68, 69};
    for(int pos = 0; pos < 24; pos++){
        twoByTwo[pos] = position + movement[pos];
    }
    for(int pos = 0; pos < 48; pos++){
        threeByThree[pos] = position + movement[pos];
    }
}

int Location::possibleTravel(int position){
    for(int pos = 0; pos < 153; pos++){
        if(water[pos] == position){
            return -1;
        }
    }
    for(int pos = 0; pos < 282; pos++){
        if(bounds[pos] == position){
            return -1;
        }
    }
    for(int pos = 0; pos < 217; pos++){
        if(plains[pos] == position){
            return 1;
        }
    }
    for(int pos = 0; pos < 15; pos++){
        if(centers[pos] == position){
            return 2;
        }
    }
    for(int pos = 0; pos < 15; pos++){
        if(gyms[pos] == position){
            return 3;
        }
    }
}

bool Location::possiblePokeTravel(int position){
    readMap("mapPoke.txt");
    bool plain = false;
    for(int pos = 0; pos < 217; pos++){
        if(plains[pos] == position){
            plain = true;
        }
    }
    return plain;
}

//finds the nearest pokemon center from the current location
int Location::findCenter(){
    bool foundCenter = false;
    int centerPosition = 365;
    for(int pos = 0; pos < 48; pos++){
        for(int arrPos = 0; arrPos < 15; arrPos++){
            if(threeByThree[pos] == centers[arrPos]){
                centerPosition = centers[arrPos];
                foundCenter = true;
                break;
            }
        }
        if(foundCenter == true){
            break;
        }
    }
    return centerPosition;
}


//displays the a 7 by 7 map
void Location::displayMap(){
    int countRow = 0;
    
    for(int row = 0; row < 3; row++){
        for(int pos = 0; pos < 7; pos++){
            int coordinate = (7 * countRow) + pos;
            for(int p = 0; p < 153; p++){
                if(water[p] == threeByThree[coordinate]){
                    cout << "~  ";
                    break;
                }
            }
            for(int p = 0; p < 15; p++){
                if(centers[p] == threeByThree[coordinate]){
                    cout << "C  ";
                    break;
                }
            }
            for(int p = 0; p < 15; p++){
                if(gyms[p] == threeByThree[coordinate]){
                    cout << "G  ";
                    break;
                }
            }
            for(int p = 0; p < 217; p++){
                if(plains[p] == threeByThree[coordinate]){
                    cout << "*  ";
                    break;
                }
            }
            for(int p = 0; p < 282; p++){
                if(bounds[p] == threeByThree[coordinate]){
                    cout << "/  ";
                    break;
                }
            }
        }
        countRow++;
        cout << endl;
    }
    
    
    
    for(int pos = 0; pos < 3; pos++){
        int coordinate = (7 * countRow) + pos;
        for(int p = 0; p < 153; p++){
            if(water[p] == threeByThree[coordinate]){
                cout << "~  ";
                break;
            }
        }
        for(int p = 0; p < 15; p++){
            if(centers[p] == threeByThree[coordinate]){
                cout << "C  ";
                break;
            }
        }
        for(int p = 0; p < 15; p++){
            if(gyms[p] == threeByThree[coordinate]){
                cout << "G  ";
                break;
            }
        }
        for(int p = 0; p < 217; p++){
            if(plains[p] == threeByThree[coordinate]){
                cout << "*  ";
                break;
            }
        }
        for(int p = 0; p < 282; p++){
            if(bounds[p] == threeByThree[coordinate]){
                cout << "/  ";
                break;
            }
        }
    }
    cout << "@  ";
    
    for(int pos = 4; pos < 7; pos++){
        int coordinate = (7 * countRow) + pos - 1;
        for(int p = 0; p < 153; p++){
            if(water[p] == threeByThree[coordinate]){
                cout << "~  ";
                break;
            }
        }
        for(int p = 0; p < 15; p++){
            if(centers[p] == threeByThree[coordinate]){
                cout << "C  ";
                break;
            }
        }
        for(int p = 0; p < 15; p++){
            if(gyms[p] == threeByThree[coordinate]){
                cout << "G  ";
                break;
            }
        }
        for(int p = 0; p < 217; p++){
            if(plains[p] == threeByThree[coordinate]){
                cout << "*  ";
                break;
            }
        }
        for(int p = 0; p < 282; p++){
            if(bounds[p] == threeByThree[coordinate]){
                cout << "/  ";
                break;
            }
        }
    }
        
        
    countRow++;
    cout << endl;
    
    for(int row = 0; row < 3; row++){
        for(int pos = 0; pos < 7; pos++){
            int coordinate = (7 * countRow) + pos - 1;
            for(int p = 0; p < 153; p++){
                if(water[p] == threeByThree[coordinate]){
                    cout << "~  ";
                    break;
                }
            }
            for(int p = 0; p < 15; p++){
                if(centers[p] == threeByThree[coordinate]){
                    cout << "C  ";
                    break;
                }
            }
            for(int p = 0; p < 15; p++){
                if(gyms[p] == threeByThree[coordinate]){
                    cout << "G  ";
                    break;
                }
            }
            for(int p = 0; p < 217; p++){
                if(plains[p] == threeByThree[coordinate]){
                    cout << "*  ";
                    break;
                }
            }
            for(int p = 0; p < 282; p++){
                if(bounds[p] == threeByThree[coordinate]){
                    cout << "/  ";
                    break;
                }
            }
        }
        countRow++;
        cout << endl;
    }
}