#pragma once

#include <string>
#include <vector>
#include <utility>
#include <tr1/unordered_map>

#include "street.hpp"


class car {
  public:
    // constructor 
    car(std::string, std::vector<std::string>, uint32_t); 

    // getters 
    uint32_t get_current_intersection(); 
    uint32_t get_next_intersection();
    std::string get_street_name(); 
    uint32_t get_time_elapsed(); 
    std::vector<std::string> get_all_intersections();  
    uint32_t get_car_speed(); 

    // member functions 
    double compute_time(const double, const uint32_t);
    void update_time_elapsed(double, uint32_t); 
    void move_to_next_intersection();  // update distance traveled 
                                       // perhaps update time elapsed here too 
                                       // update the current and next intsxns

  // member variables 
  private:
    uint32_t current_intersection; 
    uint32_t next_intersection; 
    std::string street_name; 
    uint32_t time_elapsed; 
    std::vector<std::string> all_intersections; 
    double distance_traveled; 
    uint32_t car_speed;
}; 