#include "controller.hpp"
#include "rapidcsv.h"
#include <iostream>
#include <string>
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
int TrafficLight::getCycleTime() {
  return cycleTime; 
}

// // Setter for traffic light's street name   
void TrafficLight::setStreetName(string stname) {
  streetName = stname; 
}

// Setter for traffic light's street number  
void TrafficLight::setStreetNumber(int stnum) {
  streetNumber = stnum; 
}

// Setter for the traffic light's current color 
void TrafficLight::setColor(char color) {
  currentColor = color; 
}

TrafficController::TrafficController(TrafficLight tL1,TrafficLight tL2)
                                    : trafficLight1(tL1), trafficLight2(tL2) 
{
}


TrafficController::TrafficController(TrafficLight tL1, 
                                     TrafficLight tL2, 
                                     TrafficLight tL3) 
                                     : trafficLight1(tL1), trafficLight2(tL2), trafficLight3(tL3)
{ 
}

TrafficController::TrafficController(TrafficLight tL1, 
                                     TrafficLight tL2, 
                                     TrafficLight tL3,
                                     TrafficLight tL4) 
{
  trafficLight1 = tL1; 
  trafficLight1 = tL2; 
  trafficLight1 = tL3;  
  trafficLight1 = tL4; 
}