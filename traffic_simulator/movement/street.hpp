#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>

#include "traffic_controller.hpp"

class street {
  public: 
    // constructor 
    street(uint32_t, uint32_t);

    // getters 
    uint32_t get_capacity(); 
    const uint32_t get_sp_cnn(); 
    const uint32_t get_d_cnn(); 
    bool get_is_destination(); 
    uint32_t get_lookup_key(); 
    double get_distance(); 

    // member functions 
    uint32_t compute_lookup_key(uint32_t cnn1, uint32_t cnn2);

    double compute_distance(const std::pair<double, double>& point1,
                            const std::pair<double, double>& point2);

    double compute_time(const double distance, const uint32_t speed); 

  private: 
    uint32_t capacity; 
    const uint32_t start_point_cnn; 
    const uint32_t dest_point_cnn; 
    bool is_destination; 
    uint32_t lookup_key; 
    double distance; 
    double time_needed; 
}; 

