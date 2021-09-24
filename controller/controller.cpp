#include "Light.hpp"
#include "controller.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std; 

// Constant values 
const int yellowCycle = 10; 

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