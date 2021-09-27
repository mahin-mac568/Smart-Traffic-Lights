#pragma once
#include "Light.hpp"
#include "controller.hpp"

using namespace std; 

class Event {
  
  public:
    Event(int, int); 
    int getIdx();           // Getter for TC index in allTCs global vector 
    int getTime();          // Getter for time until next event 

  private: 
    int tcIdx; 
    int time;               // time until next event 
        
}; 