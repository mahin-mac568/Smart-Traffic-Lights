#pragma once
#include <string>

// TrafficLight Class Definition 
class TrafficLight {

public:
    // enumerate the colors (red, green, yellow) 0 through 2 
    enum Color : int { 
        red = 0,
        green = 1,
        yellow = 2 
    };

    // traffic light constructor 
    TrafficLight(const int, const std::string&);

    // color number, color name, color setter, color resetter,   
    TrafficLight::Color currentColor;
    static std::string cname(const Color&);
    void setColor(const Color&);
    void reset();

    // street name, CNN of intersection, sync flag 
    std::string myStreet;
    int myCNN;
    bool isSynchronized;
};
