#include <iostream>
#include "TrafficLight.hpp"
#include "constants.hpp"

// Constructor for traffic light Object
TrafficLight::TrafficLight(const int myCNN, const std::string& myStreet) 
    : currentColor(Color::red), myStreet(myStreet), 
      myCNN(myCNN), isSynchronized(false) 
{
    /* 
    In order to create a traffic light object, a CNN value and a street name 
    must be passed in to the constructor call. The values passed in are assigned 
    to the CNN and street name member variables -- hence, the member variable 
    names following the arguments, wrapping the arguments, as well as other
    starting values. The color of the traffic light and the sync flag are set 
    to red and false, by default. No constructor body code needed. 
    */ 
}

// Color setter (number)  
void TrafficLight::setColor(const Color& newColor) {
    currentColor = newColor;
}

// Color resetter 
void TrafficLight::reset() {
    currentColor = Color::red;
}

// Color name (string) 
std::string TrafficLight::cname(const Color& somecolor) {
    switch(somecolor) {
        case Color::red:
            return "red";
        case Color::green:
            return "green";
        case Color::yellow:
            return "yellow";
    }
    return "unknown";
}
