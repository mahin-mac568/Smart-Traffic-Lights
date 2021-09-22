#pragma once
#include <string>
using namespace std; 


class TrafficLight {

  public: 
    TrafficLight(string, string, string, string); 
    void cycleLight(char); 

  private:
    char currentLight; 
    string street1; 
    string street2; 
    string street3; 
    string street4; 

}; 


class TrafficController {

  public:


  private:

}; 