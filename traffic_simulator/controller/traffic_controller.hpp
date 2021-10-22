/*
Based on Sagar’s sample hw1 solution
*/ 

#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "traffic_light.hpp"

namespace controller {
// models an intersection
class traffic_controller {
public:
    // constructor
    traffic_controller(const uint32_t cnn,
                       const std::vector<std::string>& names,
                       const std::string& location);

    // overloaded constructor for synchronization 
    traffic_controller(const uint32_t cnn,
                       const std::vector<std::string>& names,
                       const std::string& location, 
                       bool synchronize);

    // change the street lights according to the circular logic
    uint32_t transition();

    // getter for names 
    std::vector<traffic_light> get_lights(); 

    // print csv info
    void print_csv(std::ofstream& fout) const;
    // print kml info
    void print_kml(std::ofstream& fout) const;

    // synchronization 
    void synchronize_green_time(std::string); 

private:
    // identifier for the controller
    const uint32_t cnn;

    // list of all lights at the controller
    std::vector<traffic_light> lights;

    // current light to operate on for changing colors
    int cur_light = 0;

    // coordinates given in the CSV file
    const std::string location;

    bool is_synchronized=false; 
};
}  // namespace controller
