#pragma once
#include <map>
#include <memory>
#include <string>
#include "AlertEvent.hpp"
#include "Street.hpp"

class Car : public AlertEvent {
    // member variables associated with alert events 
    int car_n;                                           // car number 
    int traffic;                                         // traffic type (light, med, heavy)
    std::shared_ptr<Street> currentStreet;               // the current street (object) that this car is on 
    int current_row;                                     // the current csv row  
    int start_time;                                      // the time it is when this car is spawned
    bool isActive;                                       // active flag  
    bool isStuck;                                        // stuck flag 

    // member functions associated with alert events 
    void destReached(const int);                     // determines if this car is at its destination 
    int driving_time(const int, const int);          // determines the time elapsed for this car 

public:
    // Car constructor 
    Car(const int, const int, const int);

    // Car member variables 
    static int64_t total_driving_time;
    static int active_cars;

    // Car member functions 
    static void reset();
    virtual void event(const std::shared_ptr<AlertEvent>&, const int);
    void setTimer(const std::shared_ptr<AlertEvent>&, const int);
};
