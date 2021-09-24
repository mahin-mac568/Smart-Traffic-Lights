#include "Light.hpp"
#include "controller.hpp"
#include "Event.hpp"

using namespace std; 

// Event Constructor 
Event::Event(TrafficController* trafCont, int t) {
  tc = trafCont; 
  time = t; 
}

// Getter for time until next event 
int Event::getTime() {
  return time; 
}

// Getter for event traffic controller
TrafficController* Event::getTC() {
  return tc; 
}