#include <iostream>
#include "TrafficIntersection.hpp"
#include "constants.hpp"

// intersection object map
std::map<int, std::shared_ptr<AlertEvent>> intersections;

// Column AI in TrafficSignals.csv
const int POS = 34;  

// Constructor for TrafficIntersection Object
TrafficIntersection::TrafficIntersection (const csvRow& myRow, 
  std::shared_ptr<std::vector<std::shared_ptr<TrafficLight>>>& myLights) 
    : isSync(false), myRow(myRow), pos(myRow[POS]), myLights(myLights) 
{
    /*
    In order to create a traffic intersection object, you must pass in the 
    current csv row and the corresponding traffic light objects of that row (in 
    vector form). The data row is assigned to the row member member variable and 
    the traffic lights are assigned to the lights vector member variable. The 
    sync flag is defaulted to false, and the position of the intersection is 
    derived using the POS column of the inputted row. No constructor body code 
    needed. 
    */
}

// Getter for traffic intersection object pointer 
TrafficIntersection* TrafficIntersection::getIntersection(const int cnn) {
    /*
    The intersections vector is a global vector across modules that holds all 
    of the traffic controller objects. The get() method is a built-in method 
    for the shared_ptr data structure. 
    */ 
    return static_cast<TrafficIntersection*>(intersections[cnn].get());
}

// Event processor for traffic controller 
void TrafficIntersection::event(const std::shared_ptr<AlertEvent>& myHandle, const int now) {
    auto tl = (*myLights.get())[activeStreet];
    switch(tl->currentColor) {
        case TrafficLight::Color::red:
            tl->setColor(TrafficLight::Color::green);
            if(isSync)
                scheduleMe(myHandle, tl->isSynchronized ? (myGreenTime + now) : (UNSYNCSTAYSGREEN + now));
            else
                scheduleMe(myHandle, myGreenTime + now);
            break;
        case TrafficLight::Color::green:
            tl->setColor(TrafficLight::Color::yellow);
            scheduleMe(myHandle, YELLOWDURATION + now);
            break;
        case TrafficLight::Color::yellow:
            tl->setColor(TrafficLight::red);
            activeStreet = (activeStreet + 1) % myLights->size();
            auto tl = (*myLights.get())[activeStreet];
            tl->setColor(TrafficLight::Color::green);
            scheduleMe(myHandle, myGreenTime + now);
            break;
    }
}

// Resets entire traffic controller as if it were not initialized 
void TrafficIntersection::reset() {
    for(auto& tiae : intersections) {
        auto ti = static_cast<TrafficIntersection*>(tiae.second.get());
        ti->myGreenTime = 0;
        ti->activeStreet = 0;
        ti->isInitialized = false;
    }
}

// Sets the time for the upcoming event 
void TrafficIntersection::setTimer(const std::shared_ptr<AlertEvent>& myHandle, int gt, const int turnGreenAt, const std::string streetName, bool iss) {
    // Figure out which traffic light this corresponds to
    int initialActiveStreet = 0;
    for(auto tl : *myLights)
        if(tl->myStreet == streetName)
            break;
        else
            ++initialActiveStreet;
    initialActiveStreet %= myLights->size();
    myGreenTime = gt;

    int remainingGYTime;
    if(turnGreenAt > 0) {
        // In this case, some other light is initially green... let's figure it out!
        remainingGYTime = turnGreenAt;
        while(remainingGYTime > myGreenTime + YELLOWDURATION) {
            remainingGYTime -= myGreenTime + YELLOWDURATION;
            if(--initialActiveStreet < 0)
                initialActiveStreet += myLights->size();
        }
    } else
        remainingGYTime = myGreenTime + YELLOWDURATION;
    activeStreet = initialActiveStreet;
    isInitialized = true;
    isSync = iss;
    scheduleMe(myHandle, 0);
}
