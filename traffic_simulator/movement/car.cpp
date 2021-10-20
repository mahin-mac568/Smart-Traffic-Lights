#include <cmath>
#include <string>
#include <vector>
#include <utility>
#include <tr1/unordered_map>
#include "street.hpp"
#include "car.hpp"
#include "color.hpp"

// CONSTRUCTOR 
car::car(street start_street, std::vector<std::string> car_path) 
   : current_street(start_street), path_intersections(car_path)
{
  current_path_index = 0; 
  current_street_name = current_street.get_street_name(); 
  current_intersection = std::stoi(path_intersections.at(0)); 
  next_intersection = std::stoi(path_intersections.at(1));
  car_speed = current_street.get_speed_limit(); 
  time_elapsed = 0; 
}


// GETTERS 

uint32_t car::get_curr_path_index() {
  return current_path_index; 
}

std::string car::get_curr_street_name() {
  return current_street_name; 
}

uint32_t car::get_current_intersection() {
  return current_intersection; 
}

uint32_t car::get_next_intersection() {
  return next_intersection; 
}
    
uint32_t car::get_time_elapsed() {
  return time_elapsed; 
} 

std::vector<std::string> car::get_path_intersections() {
  return path_intersections; 
}

uint32_t car::get_car_speed() {
  return car_speed; 
}


// MEMBER FUNCTIONS 

/* Car moves from the start of its current block to the end of the block.
   The time elapsed is updated as the car moves from */
void car::drive_car() {
  current_intersection = next_intersection; 
  if (next_intersection != 0) {
    next_intersection = std::stoi(path_intersections.at(current_path_index+1)); 
  }
  current_path_index += 1; 
  time_elapsed += ceil(current_street.get_time_needed()); 
}

void car::update_streets(street next_street) {
  current_street.decrease_capacity(); 
  next_street.increase_capacity(); 
  current_street = next_street; 
  current_street_name = next_street.get_street_name();
}