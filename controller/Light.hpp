#pragma once
#include <string>
#include <tuple>
#include <vector>
#include <fstream>

using namespace std; 

// Traffic Light for one street 
class TrafficLight {

  public: 
    // CONSTRUCTORS 
    TrafficLight(); 
    TrafficLight(string id, string stname, int stnum, int k, char color='r');  

    // GETTERS 
    string getCNN();            // Getter for traffic light's id number 
    string getStreetName();     // Getter for traffic light's street name   
    int getStreetNumber();      // Getter for traffic light's street number   
    char getCurrentColor();     // Getter for traffic light's current color 
    int getGreenCycle();        // Getter for traffic light's cycle time   

    // SETTERS 
    void setColor(char);     // Setter for traffic light's current color 

    // METHODS 
    void csv_helper(ofstream&); 

  private:
    string cnn;              // the id number for the street 
    string streetName;       // the name of the street
    int streetNumber;        // either STREET1, STREET2, STREET3, or STREET4
    char currentColor;       // what the light color currently is 

    int greenCycle;          // the green-cycle for this traffic light 
                             // greenCycle is not passed into the constructor 
}; 