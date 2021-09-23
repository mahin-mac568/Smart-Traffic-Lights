#pragma once
#include <string>
#include <tuple>

using namespace std; 


class TrafficLight {

  public: 
    TrafficLight(string stname, int stnum, int k, char color='r');   // Constructor 
    void setColor(char);                              // Setter for current color 

  private:
    string streetName;    // the name of the street
    int streetNumber;     // either STREET1, STREET2, STREET3, or STREET4
    char currentColor;    // what the light color currently is 

    int cycleTime;        // the green-light-cycle for this traffic light 
                          // cycleTime is not passed into the constructor 
}; 


class TrafficController {

  public: 
    TrafficController(string, string, string, string); 
    void cycleLight(); 

  private:
    tuple<string, char> street1;
    tuple<string, char> street2;
    tuple<string, char> street3;
    tuple<string, char> street4;

}; 