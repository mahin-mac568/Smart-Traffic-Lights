#pragma once
#include <memory>

class AlertEvent {

public:
    // member variables 
    int when;               // the -t at which this event should occur 
    
    // member functions              
    static void runOne(std::shared_ptr<AlertEvent>);    // processes one event (helper to runAll)
    static void runAll();                               // processes all events 
    static void resetQueue();                           // empties the event queue 

    // instantiates event objects inside of the priority queue with respective time 
    void scheduleMe(const std::shared_ptr<AlertEvent>&, const int);

    // event processor
    virtual void event(const std::shared_ptr<AlertEvent>&, const int) = 0;
};
