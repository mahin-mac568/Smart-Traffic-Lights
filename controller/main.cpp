#include "controller.hpp"
#include "rapidcsv.h"
#include <iostream>
#include <string>

using namespace std; 

// READING THE CSV FILE PROVIDED BY SAN FRANCISCO (using rapidcsv.h) 
rapidcsv::Document sf("/home/mac568/Smart-Traffic-Lights/controller/Traffic_Signals_SF.csv");

// List of all CNNS, list of relevant CNNS, and list of traffic light objects 
vector<string> allCNNs = sf.GetColumn<string>("CNN"); 
vector<string> relevantCNNs; 
vector<TrafficLight> allTLs; 

int main() {

  // Collecting all of the relevant cnn values 
  for (int i=0; i<sizeof(allCNNs); i++) {
    auto gpsCell = sf.GetCell<string>("TBC", allCNNs[i]);
    if (gpsCell == "GPS") {
      relevantCNNs.push_back(allCNNs[i]); 
    }
  } 

  // Iterating through all of the relevant rows to collect street names 
  for (int i=0; i<sizeof(relevantCNNs); i++) {
    string street1 = sf.GetCell<string>("STREET1", relevantCNNs[i]);
    string street2 = sf.GetCell<string>("STREET2", relevantCNNs[i]);
    string street3; 
    string street4; 

    if (!(sf.GetCell<string>("STREET3", relevantCNNs[i])).empty()) {
      street3 = sf.GetCell<string>("STREET3", relevantCNNs[i]);
    } 

    if (!(sf.GetCell<string>("STREET4", relevantCNNs[i])).empty()) {
      street4 = sf.GetCell<string>("STREET4", relevantCNNs[i]);
    } 

    TrafficLight newTL(street1, street2, street3, street4); 
    allTLs.push_back(newTL); 
  }


  return 0; 
}