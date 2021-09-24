#include "controller.hpp"
#include "rapidcsv.h"
#include <iostream>
#include <string>
#include <queue>

using namespace std; 

// Reading the CSV file provided by San Francisco (using rapidcsv.h) 
rapidcsv::Document sf("/home/mac568/Smart-Traffic-Lights/controller/Traffic_Signals_SF.csv");

// Global Vectors  
vector<string> allCNNs = sf.GetColumn<string>("CNN"); 
vector<string> relevantCNNs; 
vector<TrafficController> allTCs; 

// Counter, increment right before instantiating a traffic light and pass it in 
int k; 

// Priority queue to keep track of the light cycles 
priority_queue<Event> eventQueue; 

// Main function 
int main(int argc, char *argv[]) {

  // Grab ahold of the time variable, argv[1] contains "-t=<num>"
  string arg = argv[1];                               
  int t = std::stoi(arg.substr(arg.find("=")+1)); 

  // Collecting all of the relevant cnn values (to identify relevant rows)
  for (int i=0; i<sizeof(allCNNs); i++) {
    auto gpsCell = sf.GetCell<string>("TBC", allCNNs[i]);
    if (gpsCell == "GPS") {
      relevantCNNs.push_back(allCNNs[i]); 
    }
  } 

  // Iterating through all of the relevant rows to collect street names 
  // Instantiating TrafficLight objects with those stnames, stnums, and count 
  for (int i=0; i<sizeof(relevantCNNs); i++) {
    // street strings 
    string street1 = sf.GetCell<string>("STREET1", relevantCNNs[i]);
    string street2 = sf.GetCell<string>("STREET2", relevantCNNs[i]);
    string street3;   // initalize string for street 3 in case it exists 
    string street4;   // initalize string for street 4 in case it exists

    // instantiate traffic light objects 
    TrafficLight trafLight1(street1, 1, k++); 
    TrafficLight trafLight2(street2, 2, k++);
    TrafficLight trafLight3;    // initalize object for street 3 in case it exists 
    TrafficLight trafLight4;    // initalize object for street 4 in case it exists
    

    // check if streets 3 and 4 are empty or not 
    // if they are non-empty, assign them, instantiate with them, append 
    if (!(sf.GetCell<string>("STREET3", relevantCNNs[i])).empty()) {
      street3 = sf.GetCell<string>("STREET3", relevantCNNs[i]);
      trafLight3 = TrafficLight(street3, 3, k++); 
    } 
    if (!(sf.GetCell<string>("STREET4", relevantCNNs[i])).empty()) {
      street4 = sf.GetCell<string>("STREET4", relevantCNNs[i]);
      trafLight4 = TrafficLight(street4, 4, k++); 
    } 

    // Instantiate the traffic controllers 
    if (!street3.empty() && !street4.empty()) {
      TrafficController tc(trafLight1, trafLight2, trafLight3, trafLight4); 
      allTCs.push_back(tc); 
    }
    else if (!street3.empty()) {
      TrafficController tc(trafLight1, trafLight2, trafLight3); 
      allTCs.push_back(tc); 
    }
    else {
      TrafficController tc(trafLight1, trafLight2); 
      allTCs.push_back(tc); 
    }
  }

  // Push all event objects to the priority queue 
  for (int i=0; i<sizeof(allTCs); i++) {
    vector<int> switchTimes = allTCs[i].nextActionTimes(t); 
    for (int j=0; j<sizeof(switchTimes); j++) {
      Event event(allTCs[i], switchTimes[j]); 
      eventQueue.push(event); 
    }
  }

  // Process the items in the event queue 
  int timeNextAction = eventQueue.top().getTime(); 
  while (t - timeNextAction) > 0) {
      Event poppedEvent = eventQueue.pop(); 
      poppedEvent.getTC().switchLight(); 
      if (eventQueue.top().getTime() != timeNextAction) {
        t -= timeNextAction; 
        timeNextAction = eventQueue.top().getTime(); 
      }
  }

  return 0; 
}