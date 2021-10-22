/*
Based on Sagar’s sample hw1 solution
*/ 

#pragma once

#include <fstream>
#include <string>

#include "color.hpp"

namespace controller {
// models a street light at any intersection
class traffic_light {
public:
    // initialize with the name of the street
    traffic_light(const std::string& name);

    // overloaded constructor for synchronization
    traffic_light(const std::string& name, bool synchronize);

    // red -> green, green -> yellow, yellow -> red
    // return the new color
    COLOR next_color();
    // retrun green_time
    uint32_t get_green_time() const;

    // return name
    std::string get_name() const;
    // return color
    COLOR get_color() const;
    void set_color(COLOR); 
    void set_green_time(uint32_t); 

    // print to csv file
    void print_csv(std::ofstream& fout) const;

    // time for which any light will be yellow
    static const uint32_t yellow_time;
    // total number of lights
    // used to determine the green time
    static uint32_t total_lights;

private:
    // name of the street
    const std::string name;
    // color of the light
    COLOR color = COLOR::RED;
    // time for which the light will be green
    uint32_t green_time;
    // whether or not the light is synchronized, defaulted to false 
    bool is_synchronized=false; 
};

}  // namespace controller
