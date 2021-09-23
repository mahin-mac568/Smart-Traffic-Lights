#include "controller.hpp"
#include "rapidcsv.h"
#include <iostream>
#include <string>
#include <tuple>

using namespace std; 

// Constructs one traffic light, 
// Has street name, number, count, cycle time, and current light color 
TrafficLight::TrafficLight(string stname, int stnum, int k, char color) {
  streetName = stname;    
  streetNumber = stnum;   // the order of the street at its intersection 
  currentColor = color;   // defaults to red, will change as cycling occurs 

  if ((k%25) == 0) {
    cycleTime = 90; 
  }
  else if ((k%25) < 15) {
    cycleTime = 60;
  }
  else {
    cycleTime = 30; 
  }

  if (streetNumber == 1) {  // may or may not need this, leave it for now 
    currentColor = 'g'; 
  }
}

// Setter for the traffic light's current color 
void TrafficLight::setColor(char color) {
  currentColor = color; 
}

TrafficController::TrafficController(string st1="", string st2="", 
                                     string st3="", string st4="") {
  street1 = make_tuple(st1, 'r'); 
  street2 = make_tuple(st2, 'r'); 
  street3 = make_tuple(st3, 'r'); 
  street4 = make_tuple(st4, 'r'); 
}