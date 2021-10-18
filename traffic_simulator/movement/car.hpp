#pragma once

#include <string>
#include <vector>
#include <utility>
#include <tr1/unordered_map>

#include "street.hpp"


class car {
  public:
    // constructor 
    car(std::string, std::vector<std::string>); 

    // getters 
    uint32_t get_current_intersection(); 
    uint32_t get_next_intersection();
    std::string get_street_name(); 
    uint32_t get_time_elapsed(); 
    std::vector<std::string> get_all_intersections();  

    // member functions 
    void move_to_next_intersection(); 

  private:
    uint32_t current_intersection; 
    uint32_t next_intersection; 
    std::string street_name; 
    uint32_t time_elapsed; 
    std::vector<std::string> all_intersections; 
}; 