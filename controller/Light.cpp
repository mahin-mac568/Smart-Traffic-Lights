#include "Light.hpp" 
#include <iostream>
#include <string>
#include <vector>
#include <tuple>

using namespace std; 

// Constructs one traffic light, 
TrafficLight::TrafficLight() {}

// Constructs one traffic light, 
// Has street name, number, count, cycle time, and current light color 
TrafficLight::TrafficLight(string stname, int stnum, int k, char color) {
  streetName = stname;    
  streetNumber = stnum;   // the order of the street at its intersection 
  currentColor = color;   // defaults to red, will change as cycling occurs 

  if ((k%25) == 0) {
    greenCycle = 90; 
  }
  else if ((k%25) < 15) {
    greenCycle = 60;
  }
  else {
    greenCycle = 30; 
  }

  if (streetNumber == 1) {  // may or may not need this, leave it for now 
    currentColor = 'g'; 
  }
}

// Getter for traffic light's street name 
string TrafficLight::getStreetName() {
  return streetName; 
}

// Getter for traffic light's street number 
int TrafficLight::getStreetNumber() {
  return streetNumber; 
}

// Getter for traffic light's current color  
char TrafficLight::getCurrentColor() {
  return currentColor; 
}

// Getter for traffic light's cycle time  
int TrafficLight::getGreenCycle() {
  return greenCycle; 
}

// Setter for the traffic light's current color 
void TrafficLight::setColor(char color) {
  currentColor = color; 
}