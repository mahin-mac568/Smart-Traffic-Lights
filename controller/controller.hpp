#pragma once
#include "Light.hpp"
#include <string>
#include <tuple>
#include <vector>

using namespace std; 

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