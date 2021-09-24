#pragma once
#include "Light.hpp"
#include "controller.hpp"

using namespace std; 

class Event {
  
  public:
    Event(TrafficController*, int); // pass reference of TC to the event
    int getTime();                  // Getter for time until next event 
    TrafficController* getTC();     // Getter for event traffic controller  

  private: 
    TrafficController* tc;  // pointer to TC object 
    int time;               // time until next event 
    
}; 