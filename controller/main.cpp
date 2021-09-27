#include "Light.hpp"
#include "controller.hpp"
#include "Event.hpp"
#include "rapidcsv.h"
#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std; 

// Reading the CSV file provided by San Francisco (using rapidcsv.h) 
rapidcsv::Document sf("/home/mac568/Smart-Traffic-Lights/controller/Traffic_Signals_SF.csv");

// Global Vectors  
vector<string> allCNNs = sf.GetColumn<string>("CNN"); 
vector<string> relevantCNNs; 
vector<TrafficController> allTCs; 

// Counter, increment right before instantiating a traffic light and pass it in 
int k; 

// Comparator to pass into the priority queue 
class EventOperator {
  public:
    bool operator() (Event e1, Event e2) {
      return e1.getTime() > e2.getTime(); 
    }
}; 

// Priority queue to keep track of the light cycles 
priority_queue<Event, vector<Event>, EventOperator> eventQueue; 

// Main function 
int main(int argc, char *argv[]) {

  // OUTPUT FILES (preparation)
  // Prepare output csv file 
  ofstream myfile;
  myfile.open("myfile.csv"); 
  myfile << "CNN, Street Name, Color,\n"; 
  myfile.close(); // ??

  // Prepare output kml file 
  ofstream kml; 
  kml.open("myfile.kml"); 
  kml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"; 
  kml << "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n"; 
  kml << "<Document>\n"; 
  kml.close(); // ??

  // Grab ahold of the time variable, argv[1] contains "-t=<num>"
  string arg = argv[1];                               
  int t = std::stoi(arg.substr(arg.find("=")+1)); 

  // Collecting all of the relevant cnn values (to identify relevant rows)
  for (int i=0; i<allCNNs.size(); i++) {
    auto gpsCell = sf.GetCell<string>("TBC", allCNNs[i]);
    if (gpsCell == "GPS") {
      relevantCNNs.push_back(allCNNs[i]); 
    }
  } 

  // Iterating through all of the relevant rows to collect street names 
  // Instantiating TrafficLight objects with those stnames, stnums, and count 
  // Using the TrafficLight objects to instantiate TrafficController objects 
  for (int i=0; i<relevantCNNs.size(); i++) {
    // cnn number, convert it from string to int 
    string cnn = relevantCNNs[i]; 

    // street strings 
    string street1 = sf.GetCell<string>("STREET1", relevantCNNs[i]);
    string street2 = sf.GetCell<string>("STREET2", relevantCNNs[i]);
    string street3;             // initalize string for street 3 in case it exists 
    string street4;             // initalize string for street 4 in case it exists

    // instantiate traffic light objects 
    TrafficLight trafLight1(cnn, street1, 1, k++); 
    TrafficLight trafLight2(cnn, street2, 2, k++);
    TrafficLight trafLight3;    // initalize object for street 3 in case it exists 
    TrafficLight trafLight4;    // initalize object for street 4 in case it exists
    
    // check if streets 3 and 4 are empty or not 
    // if they are non-empty, assign them, instantiate with them, append 
    if (!(sf.GetCell<string>("STREET3", relevantCNNs[i])).empty()) {
      street3 = sf.GetCell<string>("STREET3", relevantCNNs[i]);
      trafLight3 = TrafficLight(cnn, street3, 3, k++); 
    } 
    if (!(sf.GetCell<string>("STREET4", relevantCNNs[i])).empty()) {
      street4 = sf.GetCell<string>("STREET4", relevantCNNs[i]);
      trafLight4 = TrafficLight(cnn, street4, 4, k++); 
    } 

    // Instantiate the traffic controllers, push them to TC vector 
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

  // Instantiate events using all traffic controller, push events to queue 
  for (int i=0; i<allTCs.size(); i++) {
    Event newEvent(i, allTCs[i].cycleLights(0)); 
    eventQueue.push(newEvent); 
  }

  // Simulate time, cycle the lights while popping and pushing to queue appropriately 
  for (int i; i<=t; i++) {
    Event topEvent = eventQueue.top(); 
    if (i == topEvent.getTime()) {
      eventQueue.pop();
      int tcIdx = topEvent.getIdx(); 
      int newActionTime = allTCs[tcIdx].cycleLights(i); 
      Event newEvent(tcIdx, newActionTime); 
      eventQueue.push(newEvent); 
    }
  }

  // Write the final light states to a csv files 
  // for (int i; i<allTCs.size(); i++) {
  //   allTCs[i].writecsv(myfile); 
  // }  

  /* Write the final light states to the kml file 
  * for all TCs 
  *  start a string for the color combo of the intersection 
  *  for all the TLs in the intersection 
  *    check the color of the TL 
  *    concat that string to the color combo 
  *  based on the color combo, create a file name using "i" and ".png"
  *  paste in the template for one pushpin in kml, plug in the file name
  * 
  *  grab the shape cell from the input csv and parse out the numbers 
  *  paste in the coordinate part of the pushpin, plug in the cnn and coords 
  *
  *  write the entire pushpin to the output kml file */ 

  return 0; 
}