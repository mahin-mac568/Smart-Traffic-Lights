#include "controller.hpp"
#include "rapidcsv.h"
#include <iostream>
#include <string>

using namespace std; 

TrafficLight::TrafficLight(string st1="", string st2="", 
                           string st3="", string st4="") {
  currentLight = 'r'; 
  street1 = st1; 
  street2 = st2; 
  street3 = st3; 
  street4 = st4; 
}

// void TrafficLight::cycleLight(char )





  // std::cout << "Read " << col.size() << " values." << std::endl;