#include "controller.hpp"
#include "rapidcsv.h"
#include <iostream>
#include <string>

using namespace std; 

// Reading the CSV file provided by San Francisco (using rapidcsv.h) 
rapidcsv::Document sf("/home/mac568/Smart-Traffic-Lights/controller/Traffic_Signals_SF.csv");

// List of all CNNS, list of relevant CNNS, and list of traffic light objects 
vector<string> allCNNs = sf.GetColumn<string>("CNN"); 
vector<string> relevantCNNs; 
vector<TrafficLight> allTrafLights; // if I want the changes to the controller's vector of lights, 
                                    // I should pass in the reference to the global lights 

// Counter, increment right before instantiating a traffic light and pass it in 
int k; 

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
    // Get streets 1 and 2
    string street1 = sf.GetCell<string>("STREET1", relevantCNNs[i]);
    string street2 = sf.GetCell<string>("STREET2", relevantCNNs[i]);

    // instantiate traffic light objects for streets 1 and 2 
    TrafficLight trafLight1(street1, 1, k++); 
    TrafficLight trafLight2(street2, 2, k++);

    // add the traffic light objects to the traffic lights array   
    allTrafLights.push_back(trafLight1); 
    allTrafLights.push_back(trafLight2); 

    // initalize strings for streets 3 and 4 in case they exist 
    string street3; 
    string street4; 

    // check if streets 3 and 4 are empty or not 
    // if they are non-empty, assign them, instantiate with them, append 
    if (!(sf.GetCell<string>("STREET3", relevantCNNs[i])).empty()) {
      street3 = sf.GetCell<string>("STREET3", relevantCNNs[i]);
      TrafficLight trafLight3(street3, 3, k++); 
      allTrafLights.push_back(trafLight3); 
    } 
    if (!(sf.GetCell<string>("STREET4", relevantCNNs[i])).empty()) {
      street4 = sf.GetCell<string>("STREET4", relevantCNNs[i]);
      TrafficLight trafLight4(street4, 4, k++); 
      allTrafLights.push_back(trafLight4); 
    } 
  }

  // Instantiate the traffic controllers 

  return 0; 
}