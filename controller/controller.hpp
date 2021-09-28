#pragma once
#include "Light.hpp"
#include <string>
#include <tuple>
#include <vector>
#include <fstream>

using namespace std; 

// Controls all traffic lights for one intersection 
class TrafficController {

  public:     
    // CONSTRUCTORS
    TrafficController(TrafficLight, 
                      TrafficLight); 

    TrafficController(TrafficLight, 
                      TrafficLight, 
                      TrafficLight); 

    TrafficController(TrafficLight, 
                      TrafficLight, 
                      TrafficLight, 
                      TrafficLight); 

    // GETTERS 
    TrafficLight getTL1(); 
    TrafficLight getTL2(); 
    TrafficLight getTL3(); 
    TrafficLight getTL4(); 
    vector<TrafficLight> getAllLights(); 

    // Light update function 
    int cycleLights(int); 

    // Write traffic light states for this intersection to the csv 
    void writecsv(ofstream&); 

  private:
    TrafficLight trafficLight1; 
    TrafficLight trafficLight2; 
    TrafficLight trafficLight3; 
    TrafficLight trafficLight4; 
    vector<TrafficLight> intersection; 
}; 