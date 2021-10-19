#pragma once

#include <string>
#include <vector>
#include <utility>
#include <tr1/unordered_map>

class street {
  public: 
    // constructor 
    street(uint32_t, uint32_t, std::pair<double,double>, 
           std::pair<double,double>, std::string, uint32_t, uint32_t);

    // getters 
    std::string get_street_name();
    uint32_t get_capacity(); 
    const uint32_t get_sp_cnn(); 
    const uint32_t get_ep_cnn(); 
    bool get_is_destination(); 
    uint32_t get_lookup_key(); 
    double get_distance(); 
    double get_time_needed(); 
    uint32_t get_speed_limit(); 

    // member functions 
    double compute_distance(const std::pair<double,double>& point1,
                            const std::pair<double,double>& point2);

    double compute_time(const double distance, const uint32_t speed_limit);

    void decrease_capacity(); 
    void increase_capacity(); 

  private: 
    // member variables
    std::string street_name; 
    uint32_t capacity; 
    const uint32_t start_point_cnn; 
    const uint32_t end_point_cnn; 
    bool is_destination; 
    uint32_t lookup_key; 
    double distance; 
    double time_needed; 
    uint32_t speed_limit; 
}; 

