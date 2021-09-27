#include "Light.hpp"
#include "controller.hpp"
#include "Event.hpp"

using namespace std; 

// Event Constructor 
Event::Event(int i, int t) {
  tcIdx = i;                     
  time = t; 
}

// Getter for event traffic controller's index in allTCs global vector 
int Event::getIdx() {
  return tcIdx; 
}

// Getter for time until next event 
int Event::getTime() {
  return time; 
}