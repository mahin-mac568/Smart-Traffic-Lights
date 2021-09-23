#pragma once
#include <string>
#include <tuple>

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
    int getCycleTime();      // Getter for traffic light's cycle time   

    // SETTERS 
    void setStreetName(string);  // Setter for traffic light's street name   
    void setStreetNumber(int);   // Setter for traffic light's street number  
    void setCount(int);          // Setter for traffic light's current color
    void setColor(char);         // Setter for traffic light's current color 

  private:
    string streetName;    // the name of the street
    int streetNumber;     // either STREET1, STREET2, STREET3, or STREET4
    char currentColor;    // what the light color currently is 

    int cycleTime;        // the green-cycle for this traffic light 
                          // cycleTime is not passed into the constructor 
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

    void cycleLight(); 

  private:
    TrafficLight trafficLight1; 
    TrafficLight trafficLight2; 
    TrafficLight trafficLight3; 
    TrafficLight trafficLight4; 

}; 