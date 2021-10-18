#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <tr1/unordered_map>

#include "traffic_controller.hpp"

class street {
  public: 
    // constructor 
    street(uint32_t, uint32_t, std::pair<double,double>, std::pair<double,double>);

    // getters 
    std::string get_street_name();
    uint32_t get_capacity(); 
    const uint32_t get_sp_cnn(); 
    const uint32_t get_d_cnn(); 
    bool get_is_destination(); 
    uint32_t get_lookup_key(); 
    double get_distance(); 
    double get_time_needed(); 

    // member functions 
    uint32_t compute_lookup_key(uint32_t cnn1, uint32_t cnn2);

    double compute_distance(const std::pair<double, double>& point1,
                            const std::pair<double, double>& point2);

    double compute_time(const double distance, const uint32_t speed);

    string obtain_street_name(  );  

  private: 
    std::string street_name; 
    uint32_t capacity; 
    const uint32_t start_point_cnn; 
    const uint32_t dest_point_cnn; 
    bool is_destination; 
    uint32_t lookup_key; 
    std::pair<double> coordinates; 
    double distance; 
    double time_needed; 
}; 

