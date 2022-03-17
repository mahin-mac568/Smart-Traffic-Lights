#pragma once
#include <map>
#include <memory>
#include "csv.hpp"
#include "AlertEvent.hpp"
#include "TrafficLight.hpp"

// TrafficIntersection Class Definition, Extends Class AlertEvent 
class TrafficIntersection : public AlertEvent {

    // member variables associated with Alert Events 
    int numberOfStreets;                              // number of streets for this route                         
    int activeStreet;                                 // current street 
    int myGreenTime;                                  // green time for this street 
    bool isSync;                                      // sync flag 
    csvRow myRow;                                     // current row in csv data 

public:
    // traffic intersection constructor 
    TrafficIntersection(const csvRow&, 
      std::shared_ptr<std::vector<std::shared_ptr<TrafficLight>>>&);

    // traffic intersection member variables
    bool isInitialized;                                                   // init flag 
    std::string pos;                                                      // position of intersection
    std::shared_ptr<std::vector<std::shared_ptr<TrafficLight>>> myLights; // vector of Traffic Lights at this intersection
      
    // traffic intersection member functions 
    virtual void event(const std::shared_ptr<AlertEvent>&, const int);    // event function redefined in this module upon extending AlertEvent 
    static void reset();                                                  // resets this intersection's lights 
    void setTimer(const std::shared_ptr<AlertEvent>&, const int, 
                  const int, std::string, bool isSync);                   // sets event timer based on next action to take 

    static TrafficIntersection* getIntersection(const int);               // getter for intersection pointer 
};

// global map of traffic controllers defined across all modules 
extern std::map<int, std::shared_ptr<AlertEvent>> intersections;
