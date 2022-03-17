#include <cmath>
#include <iostream>
#include <unordered_map>
#include "Car.hpp"
#include "constants.hpp"
#include "csv.hpp"
#include "TrafficIntersection.hpp"

// csv data for Traffic Lights and Sync Cars 
extern csv TL, SC;

// maps that store any stoi/stod values ever introduced to the program 
extern std::unordered_map<std::string,int> stoi_map; 
extern std::unordered_map<int,std::pair<double,double>> stod_map; 

// counts for the number of times stoi and stod are called 
// extern int stoi_count; 
// extern int stod_count; 

// counter helper functions for stoi and stod 
// extern void increment_stoi(); 
// extern void increment_stod(); 

// global variables for the car module 
int Car::active_cars = 0;                        // number of active cars 
int stuckCars = 0;                               // number of cars waiting 
int64_t Car::total_driving_time = 0;             // time elapsed for this car 
std::vector<std::shared_ptr<AlertEvent>> cars;   // vector of Car objects 

// distance helper 
double compute_distance(const std::pair<double, double>& point1, const std::pair<double, double>& point2) {
    const std::pair<double, double> DEGREE_TO_MILES(54.74, 68.97);
    const double long_miles = (point2.first - point1.first) * DEGREE_TO_MILES.first;
    const double lat_miles = (point2.second - point1.second) * DEGREE_TO_MILES.second;
    return std::sqrt(long_miles * long_miles + lat_miles * lat_miles);
}

// time helper 
double compute_time(const double& distance, const uint32_t& speed) {
    return std::ceil((distance * 3600) / speed);
}
const double one_degree_long_miles = 54.74;
const double one_degree_lat_miles = 69.97;

// time spent driving for this car 
int Car::driving_time(const int cnn1, const int cnn2) {
    size_t idx1, idx2;
    std::string long1 = TrafficIntersection::getIntersection(cnn1)->pos;
    std::string long2 = TrafficIntersection::getIntersection(cnn2)->pos;
    long1 = long1.substr(long1.find('-') + 1);
    long2 = long2.substr(long2.find('-') + 1);
    if (!stod_map.contains(cnn1)) {
        double cnn1_long = -stod(long1, &idx1); 
        double cnn1_lat = stod(long1.substr(idx1)); 
        std::pair<double, double> point1(cnn1_long, cnn1_lat);
        stod_map[cnn1] = point1; 
    }
    if (!stod_map.contains(cnn2)) {
        double cnn2_long = -stod(long2, &idx2);
        double cnn2_lat = stod(long2.substr(idx2)); 
        std::pair<double, double> point2(cnn2_long, cnn2_lat);
        stod_map[cnn2] = point2; 
    }
    // double cnn1_long = -stod(long1, &idx1), cnn2_long = -stod(long2, &idx2);
    // increment_stod(); 
    // increment_stod(); 
    // double cnn1_lat = stod(long1.substr(idx1)), cnn2_lat = stod(long2.substr(idx2));
    // increment_stod(); 
    // increment_stod(); 
    // std::pair<double, double> point1(cnn1_long, cnn1_lat);
    // std::pair<double, double> point2(cnn2_long, cnn2_lat);
    double dist = compute_distance(stod_map[cnn1], stod_map[cnn2]);
    double time = compute_time(dist, traffic == LIGHT ? 30.0 : (traffic == MEDIUM ? 10 : 3.0));
    return time;
}

// Constructor for Car Object 
Car::Car(const int car_n, const int start_time, const int traffic) 
   : car_n(car_n), traffic(traffic), currentStreet(nullptr), 
     current_row(SKIPROWS), start_time(start_time), isActive(true), 
     isStuck(false) 
{
    /*
    The arguments passed into the constructor are assigned to the car number, 
    the time it is when this car is instantiated, the traffic type this car is 
    driving in, the street object associated with this car, the data row this
    car is on, the time it is when this car is initiated, the active flag, and
    the stuck flag. 
    */ 
    ++active_cars;
}

// Sets the time for the upcoming event 
void Car::setTimer(const std::shared_ptr<AlertEvent>& myHandle, const int when) {
    scheduleMe(myHandle, when);
}

// Resets car object and its fields 
void Car::reset() {
    total_driving_time = 0;
    stuckCars = 0;
}

// Event processor for car  
void Car::event(const std::shared_ptr<AlertEvent>& myHandle, const int now) {
    if (stoi_map.find(SC[current_row][car_n]) == stoi_map.end()) {
        stoi_map[SC[current_row][car_n]] = stoi(SC[current_row][car_n]);
    }
    int currentCNN = stoi_map[SC[current_row][car_n]];
    // increment_stoi(); 
    auto ti = TrafficIntersection::getIntersection(currentCNN);
    if(isStuck) {
        isStuck = false;
        --stuckCars;
    }
    bool fnd = false;
    if(currentStreet != nullptr) {
        for(uint streetnum = 0; streetnum < ti->myLights->size(); streetnum++)
            if((*ti->myLights)[streetnum]->myStreet == currentStreet->myName) {
                if((*ti->myLights)[streetnum]->currentColor == TrafficLight::Color::red) {
                    scheduleMe(myHandle, now + 1);
                    return;
                }
                fnd = true;
                break;
            }
    }
    if(!fnd) {
        if((*ti->myLights)[0]->currentColor == TrafficLight::Color::red) {
            scheduleMe(myHandle, now + 1);
            return;
        }
        fnd = true;
    }
    if (stoi_map.find(SC[current_row + 1][car_n]) == stoi_map.end()) {
        stoi_map[SC[current_row + 1][car_n]] = stoi(SC[current_row + 1][car_n]);
    }
    int nextCNN = stoi_map[SC[current_row + 1][car_n]];
    // increment_stoi(); 
    if(nextCNN == 0) {
        destReached(now);
        return;
    }
    auto st = streets[((int64_t)currentCNN << 32) | (int64_t)nextCNN];
    if(st == nullptr) {
        std::cerr << "ERROR: Null street pointer from " << currentCNN << " to " << nextCNN << std::endl;
        abort();
    }
    if(st->additionalCapacity == 0) {
        if(++stuckCars == active_cars) {
            std::cerr << "Gridlock detected at time " << now << ", aborting." << std::endl;
            abort();
        }
        isStuck = true;
        scheduleMe(myHandle, now + 1);
        return;
    }
    if(currentStreet != nullptr)
        currentStreet->additionalCapacity++;
    currentStreet = st;
    st->additionalCapacity--;
    current_row++;
    // People drive faster on streets with synchronized lights
    if(st->isSynchronized)
        scheduleMe(myHandle, now + driving_time(st->fromCNN, st->toCNN) * 2 / 3);
    else
        scheduleMe(myHandle, now + driving_time(st->fromCNN, st->toCNN));
}

// determines if this car is at its destination
void Car::destReached(const int now) {
    if(currentStreet != nullptr)
        currentStreet->additionalCapacity++;
    total_driving_time += now - start_time;
    isActive = false;
    --active_cars;
}
