#include "street.hpp"
#include "color.hpp"
#include <cmath>
#include <utility>
#include <tr1/unordered_map>

// CONSTRUCTOR 
street::street(const uint32_t cnn0, const uint32_t cnn1, 
               std::pair<double,double> coords0, 
               std::pair<double,double> coords1, 
               std::string name, uint32_t speed) 
      : start_point_cnn(cnn0), dest_point_cnn(cnn1), 
        street_name(name), speed(speed)
{
  is_destination = (dest_point_cnn == 0) ? true : false;
  lookup_key = compute_lookup_key(cnn0, cnn1); 
  distance = compute_distance(coords0, coords1); 
  time_needed = compute_time(distance, speed); 
}


// GETTER FUNCTIONS 

std::string street::get_street_name() {
  return street_name; 
}

uint32_t street::get_capacity() {
  return capacity; 
}
const uint32_t street::get_sp_cnn() {
  return start_point_cnn; 
}

const uint32_t street::get_d_cnn() {
  return dest_point_cnn; 
}

bool street::get_is_destination() {
  return is_destination; 
}

uint32_t street::get_lookup_key() {
  return lookup_key; 
}

double street::get_distance() {
  return distance; 
} 

double street::get_time_needed() {
  return time_needed; 
}

uint32_t street::get_speed() {
  return speed; 
}


// MEMBER FUNCTIONS 

uint32_t compute_lookup_key(uint32_t cnn0, uint32_t cnn1, double coords) {
    uint32_t cnn0_shifted = (cnn0 << 32); 
    return cnn0_shifted | cnn1; 
}

double street::compute_distance(const std::pair<double, double>& point1,
                                const std::pair<double, double>& point2) 
{
    const std::pair<double, double> DEGREE_TO_MILES(54.74, 68.97);
    const double long_miles = (point2.first - point1.first) * DEGREE_TO_MILES.first;
    const double lat_miles = (point2.second - point1.second) * DEGREE_TO_MILES.second;

    return std::sqrt(long_miles * long_miles + lat_miles * lat_miles);
}

double street::compute_time(const double distance, const uint32_t speed) {
  return std::ceil((distance * 3600) / speed);
}