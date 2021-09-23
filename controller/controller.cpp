#include "controller.hpp"
#include "rapidcsv.h"
#include <iostream>
#include <string>
#include <tuple>

using namespace std; 

TrafficLight::TrafficLight(string name, int num, char color='r') {
  streetName = name; 
  streetNumber = num; 

  switch (streetNumber) {
    case 1:
      // color = 'g'; 
    case 2: 
      // color = 'r'; 
    case 3:
      
    case 4: 
  }
}

TrafficController::TrafficController(string st1="", string st2="", 
                                     string st3="", string st4="") {
  street1 = make_tuple(st1, 'r'); 
  street2 = make_tuple(st2, 'r'); 
  street3 = make_tuple(st3, 'r'); 
  street4 = make_tuple(st4, 'r'); 
}