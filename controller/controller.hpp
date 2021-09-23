#pragma once
#include <string>
using namespace std; 


class TrafficLight {

  public: 
    TrafficLight(string, int, char); 

  private:
    string streetName; 
    int streetNumber; 
    char lightColor; 

}; 


class TrafficController {

  public: 
    TrafficController(string, string, string, string); 
    void cycleLight(); 

  private:
    tuple <string, char> street1;
    tuple <string, char> street2;
    tuple <string, char> street3;
    tuple <string, char> street4;

}; 