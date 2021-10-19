#pragma once

#include <string>
#include <vector>
#include <utility>
#include <tr1/unordered_map>
#include "street.hpp"


class car {
  public:
    // constructor 
    car(street, std::vector<std::string>); 

    // getters 
    uint32_t get_curr_path_index(); 
    std::string get_curr_street_name(); 
    uint32_t get_current_intersection(); 
    uint32_t get_next_intersection();
    uint32_t get_time_elapsed(); 
    std::vector<std::string> get_path_intersections();  
    uint32_t get_car_speed(); 

    // setters 
    void set_curr_street(street); 

    // member functions 
    void drive_car(); 
 
  private:
    // member variables
    uint32_t current_path_index; 
    street current_street; 
    std::string current_street_name; 
    uint32_t current_intersection; 
    uint32_t next_intersection; 
    std::vector<std::string> path_intersections;  // const 
    uint32_t car_speed;                           // const 
    uint32_t time_elapsed; 
}; 