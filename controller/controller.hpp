#pragma once
#include <string>
#include <tuple>
#include <vector>

using namespace std; 

// Traffic Light for one street 
class TrafficLight {

  public: 
    // CONSTRUCTOR  
    TrafficLight(); 
    TrafficLight(string stname, int stnum, int k, char color='r');  

    // GETTERS 
    string getStreetName();  // Getter for traffic light's street name   
    int getStreetNumber();   // Getter for traffic light's street number   
    char getCurrentColor();  // Getter for traffic light's current color 
    int getGreenCycle();      // Getter for traffic light's cycle time   

    // SETTERS 
    // void setStreetName(string);  // Setter for traffic light's street name   
    // void setStreetNumber(int);   // Setter for traffic light's street number  
    // void setCount(int);          // Setter for traffic light's current color
    void setColor(char);         // Setter for traffic light's current color 

  private:
    string streetName;    // the name of the street
    int streetNumber;     // either STREET1, STREET2, STREET3, or STREET4
    char currentColor;    // what the light color currently is 

    int greenCycle;        // the green-cycle for this traffic light 
                          // greenCycle is not passed into the constructor 
}; 

// Controls all traffic lights for one intersection 
class TrafficController {

  public:     
    TrafficController(TrafficLight, 
                      TrafficLight); 

    TrafficController(TrafficLight, 
                      TrafficLight, 
                      TrafficLight); 

    TrafficController(TrafficLight, 
                      TrafficLight, 
                      TrafficLight,
                      TrafficLight); 

    int cycleLights(int); 

  private:
    TrafficLight trafficLight1; 
    TrafficLight trafficLight2; 
    TrafficLight trafficLight3; 
    TrafficLight trafficLight4; 
    vector<TrafficLight> intersection; 
}; 

class Event {
  
  public:
    Event(TrafficController*, int); // pass reference of TC to the event
    int getTime();                  // Getter for time until next event 
    TrafficController* getTC();     // Getter for event traffic controller  

  private: 
    TrafficController* tc;  // pointer to TC object 
    int time;               // time until next event 
    
}; 