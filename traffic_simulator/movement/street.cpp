#include "street.hpp"
#include "color.hpp"
#include <cmath>
#include <utility>
#include <tr1/unordered_map>

// Constant values to be used to help determine street object fields 
const uint32_t LIGHT_TRAFFIC_SPEED = 30; 
const uint32_t HEAVY_TRAFFIC_SPEED = 3; 
const uint32_t LIGHT_TRAFFIC_CAPACITY = 20; 
const uint32_t HEAVY_TRAFFIC_CAPACITY = 2; 

// CONSTRUCTOR 
street::street(const uint32_t cnn0, const uint32_t cnn1, 
               std::pair<double,double> coords0, 
               std::pair<double,double> coords1, 
               std::string name, uint32_t speed, uint32_t key)  
      : start_point_cnn(cnn0), end_point_cnn(cnn1), 
        street_name(name), speed_limit(speed), lookup_key(key)
{
  is_destination = (end_point_cnn == 0) ? true : false;
  distance = compute_distance(coords0, coords1); 
  time_needed = compute_time(distance, speed_limit); 
  capacity = (speed_limit == LIGHT_TRAFFIC_SPEED) ? 
    LIGHT_TRAFFIC_CAPACITY : HEAVY_TRAFFIC_CAPACITY; 
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

const uint32_t street::get_ep_cnn() {
  return end_point_cnn; 
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

uint32_t street::get_speed_limit() {
  return speed_limit; 
}


// MEMBER FUNCTIONS 

/* Computes the distance between two intersections (the length of this street) */
double street::compute_distance(const std::pair<double, double>& point1,
                                const std::pair<double, double>& point2) 
{
    const std::pair<double, double> DEGREE_TO_MILES(54.74, 68.97);
    const double long_miles = (point2.first - point1.first) * DEGREE_TO_MILES.first;
    const double lat_miles = (point2.second - point1.second) * DEGREE_TO_MILES.second;

    return std::sqrt(long_miles * long_miles + lat_miles * lat_miles);
}

/* Computes the time it takes to traverse this street depending on the speed limit */
double street::compute_time(const double distance, const uint32_t speed_limit) {
  return std::ceil((distance * 3600) / speed_limit);
}

/* Decreases the capacity of the street by 1; 
   Called when a car object enters this street */
void street::decrease_capacity() {
  capacity -= 1; 
}

/* Increases the capacity of the street by 1; 
   Called when a car object exits this street */
void street::increase_capacity() {
  capacity += 1; 
}