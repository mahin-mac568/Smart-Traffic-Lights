#include <iostream>
#include <queue>
#include "AlertEvent.hpp"
#include "Car.hpp"
#include "constants.hpp"

extern const int LENGTH = 20000; 

// Comparator for Event Queue 
class compareAE {
public:
    bool operator()(const std::shared_ptr<AlertEvent>& lhs, const std::shared_ptr<AlertEvent>& rhs) const {
        return lhs->when > rhs->when;
    }
};

// Event Queue for AlertEvents 
// std::priority_queue<std::shared_ptr<AlertEvent>, std::vector<std::shared_ptr<AlertEvent>>, compareAE> myPriorityQueue;
std::vector<std::vector<std::shared_ptr<AlertEvent>>> eventVector(LENGTH);

// Instantiates event objects inside of the event vector with respective time 
void AlertEvent::scheduleMe(const std::shared_ptr<AlertEvent>& ae, const int when) {
    int currentSize = eventVector.size(); 

    while (when >= currentSize) {
        eventVector.resize(2 * eventVector.size()); 
        currentSize = eventVector.size(); 
    }

    ae->when = when;
    // myPriorityQueue.emplace(ae);

    eventVector[when].push_back(ae); 
}

// Processes all events 
void AlertEvent::runAll() {
    // while(!myPriorityQueue.empty() && Car::active_cars > 0)
    //     AlertEvent::runOne();

    int eventIdx = 0; 
    while (eventIdx < int(eventVector.size()) && Car::active_cars > 0) {
        for (std::shared_ptr<AlertEvent>& ae : eventVector.at(eventIdx)) {
            AlertEvent::runOne(ae);
        }
        eventVector.at(eventIdx).clear(); 
        eventIdx++; 
    } 
}

// Processes one event (helper to runAll)
void AlertEvent::runOne(std::shared_ptr<AlertEvent> ev) {
    // auto ev = myPriorityQueue.top();
    // myPriorityQueue.pop();

    ev->event(ev, ev->when);
}

// Empties the event queue's event lists 
void AlertEvent::resetQueue() {
    // while(!myPriorityQueue.empty())
    //     myPriorityQueue.pop();

    for (std::vector<std::shared_ptr<AlertEvent>>& eventList : eventVector) {
        eventList.clear(); 
    }
}