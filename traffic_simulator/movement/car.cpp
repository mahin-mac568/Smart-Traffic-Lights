#include "street.hpp"
#include "car.hpp"
#include "color.hpp"
#include <cmath>
#include <utility>
#include <tr1/unordered_map>

// CONSTRUCTOR 
car::car(std::string name, std::vector<std::string> car_path, street start_street) 
   : street_name(name), all_intersections(car_path)
{
  current_intersection = std::stoi(all_intersections.at(0)); 
  next_intersection = std::stoi(all_intersections.at(1));
  // time_elapsed = compute_time(distance, speed_limit); 
  car_speed = start_street.get_speed_limit(); 
}


// GETTERS 

uint32_t car::get_current_intersection() {
  return current_intersection; 
}

uint32_t car::get_next_intersection() {
  return next_intersection; 
}

std::string car::get_street_name() {
  return street_name; 
}
    
uint32_t car::get_time_elapsed() {
  return time_elapsed; 
} 

std::vector<std::string> car::get_all_intersections() {
  return all_intersections; 
}

uint32_t car::get_car_speed() {
  return car_speed; 
}


// MEMBER FUNCTIONS 

/*  */
// double car::compute_time(const double distance, const uint32_t speed_limit) {
//   return std::ceil((distance * 3600) / speed_limit);
// }

/*  */
void car::update_time_elapsed(double distance, uint32_t speed) {
  time_elapsed = ceil(distance / speed); 
}

/*  */
void car::move_to_next_intersection() {

}