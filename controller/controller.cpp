#include "controller.hpp"
#include "rapidcsv.h"
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <bits/stdc++.h>

using namespace std; 

// Constant values 
const int yellowCycle = 10; 

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

// // Setter for traffic light's street name   
// void TrafficLight::setStreetName(string stname) {
//   streetName = stname; 
// }

// // Setter for traffic light's street number  
// void TrafficLight::setStreetNumber(int stnum) {
//   streetNumber = stnum; 
// }

// void TrafficLight::setCount(int)

// Setter for the traffic light's current color 
void TrafficLight::setColor(char color) {
  currentColor = color; 
}

TrafficController::TrafficController(TrafficLight tL1,TrafficLight tL2)
                                    : trafficLight1(tL1), trafficLight2(tL2) 
{
  intersection.push_back(tL1); 
  intersection.push_back(tL2); 
}


TrafficController::TrafficController(TrafficLight tL1, TrafficLight tL2, 
                                     TrafficLight tL3) 
                                     : trafficLight1(tL1), trafficLight2(tL2), 
                                       trafficLight3(tL3) 
{ 
  intersection.push_back(tL1); 
  intersection.push_back(tL2);
  intersection.push_back(tL3);
}

TrafficController::TrafficController(TrafficLight tL1, TrafficLight tL2, 
                                     TrafficLight tL3, TrafficLight tL4) 
                                     : trafficLight1(tL1), trafficLight2(tL2), 
                                       trafficLight3(tL3), trafficLight4(tL4)
{
  intersection.push_back(tL1); 
  intersection.push_back(tL2);
  intersection.push_back(tL3);
  intersection.push_back(tL4);
}

int TrafficController::cycleLights(int t) {
  int len = sizeof(intersection); 
  
  if (len == 2) {
    // change street 1 to green at t=0 
    if (trafficLight1.getCurrentColor()=='r' &&  
        trafficLight2.getCurrentColor()=='r') 
    {
      trafficLight1.setColor('g'); 
      return t + trafficLight1.getGreenCycle(); 
    }
    // change street 1 to yellow
    else if (trafficLight1.getCurrentColor() == 'g') {
      trafficLight1.setColor('y');
      return t + yellowCycle; 
    }
    // change street 1 to red, street 2 to green 
    else if (trafficLight1.getCurrentColor() == 'y') {
      trafficLight1.setColor('r');
      trafficLight2.setColor('g');
      return t + trafficLight2.getGreenCycle(); 
    }
    // change street 2 to yellow
    else if (trafficLight2.getCurrentColor() == 'g') {
      trafficLight2.setColor('y');
      return t + yellowCycle; 
    }
    // change street 2 to red, street 1 back to green 
    else if (trafficLight2.getCurrentColor() == 'y') {
      trafficLight2.setColor('r');
      trafficLight1.setColor('g');
      return t + trafficLight1.getGreenCycle(); 
    }
    else {
      cout << "Traffic Controller has incorrect number of lights" << endl; 
      return 1; 
    }
  }

  else if (len == 3) {
    // change street 1 to green at t=0 
    if (trafficLight1.getCurrentColor()=='r' &&  
        trafficLight2.getCurrentColor()=='r' && 
        trafficLight3.getCurrentColor()=='r') 
    {
      trafficLight1.setColor('g');
      return t + trafficLight1.getGreenCycle(); 
    }
    else if (trafficLight1.getCurrentColor() == 'g') {
      trafficLight1.setColor('y');
      return t + yellowCycle; 
    }
    else if (trafficLight1.getCurrentColor() == 'y') {
      trafficLight1.setColor('r');
      trafficLight2.setColor('g');
      return t + trafficLight2.getGreenCycle(); 
    }
    else if (trafficLight2.getCurrentColor() == 'g') {
      trafficLight2.setColor('y');
      return t + yellowCycle; 
    }
    else if (trafficLight2.getCurrentColor() == 'y') {
      trafficLight2.setColor('r');
      trafficLight3.setColor('g');
      return t + trafficLight3.getGreenCycle(); 
    }
    else if (trafficLight3.getCurrentColor() == 'g') {
      trafficLight3.setColor('y');
      return t + yellowCycle; 
    }
    else if (trafficLight3.getCurrentColor() == 'y') {
      trafficLight3.setColor('r');
      trafficLight1.setColor('g');
      return t + trafficLight1.getGreenCycle(); 
    }
    else {
      cout << "Traffic Controller has incorrect number of lights" << endl; 
      return 1; 
    }
  }

  else if (len == 4) {
    // change street 1 to green at t=0 
    if (trafficLight1.getCurrentColor()=='r' &&  
        trafficLight2.getCurrentColor()=='r' && 
        trafficLight3.getCurrentColor()=='r' &&
        trafficLight4.getCurrentColor()=='r') 
    {
      trafficLight1.setColor('g');
      return t + trafficLight1.getGreenCycle(); 
    }
    else if (trafficLight1.getCurrentColor() == 'g') {
      trafficLight1.setColor('y');
      return t + yellowCycle; 
    }
    else if (trafficLight1.getCurrentColor() == 'y') {
      trafficLight1.setColor('r');
      trafficLight2.setColor('g');
      return t + trafficLight2.getGreenCycle(); 
    }
    else if (trafficLight2.getCurrentColor() == 'g') {
      trafficLight2.setColor('y');
      return t + yellowCycle; 
    }
    else if (trafficLight2.getCurrentColor() == 'y') {
      trafficLight2.setColor('r');
      trafficLight3.setColor('g');
      return t + trafficLight3.getGreenCycle(); 
    }
    else if (trafficLight3.getCurrentColor() == 'g') {
      trafficLight3.setColor('y');
      return t + yellowCycle; 
    }
    else if (trafficLight3.getCurrentColor() == 'y') {
      trafficLight3.setColor('r');
      trafficLight4.setColor('g');
      return t + trafficLight4.getGreenCycle(); 
    }
    else if (trafficLight4.getCurrentColor() == 'g') {
      trafficLight4.setColor('y');
      return t + yellowCycle; 
    }
    else if (trafficLight4.getCurrentColor() == 'y') {
      trafficLight4.setColor('r');
      trafficLight1.setColor('g');
      return t + trafficLight1.getGreenCycle(); 
    }
    else {
      cout << "Traffic Controller has incorrect number of lights" << endl; 
      return 1; 
    }
  }
  else {
    cout << "Traffic Controller has incorrect number of lights" << endl; 
    return 1; 
  }
}

// Getter for time until next event 
int Event::getTime() {
  return time; 
}

// Getter for event traffic controller
TrafficController* Event::getTC() {
  return tc; 
}