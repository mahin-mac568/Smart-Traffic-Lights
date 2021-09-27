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

// Global   
vector<string> allCNNs = sf.GetColumn<string>("CNN"); 
vector<int> relevantRowNums; 
vector<string> relevantCNNs; 
vector<TrafficController> allTCs; 
int k;  // Counter, increment right before instantiating a traffic light and pass it in 

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

  // Grabbing ahold of the time variable, argv[1] contains "-t=<num>"
  string arg = argv[1];                         
  int t = stoi(arg.substr(arg.find("=")+1)); 

  // Collecting all of the relevant cnn values (to identify relevant rows)
  for (int i=0; i<allCNNs.size(); i++) {
    int rowNum = i+2; 
    auto gpsCell = sf.GetCell<string>("TBC", rowNum);

    if (gpsCell == "GPS") {
      relevantRowNums.push_back(rowNum); 
      relevantCNNs.push_back(allCNNs[i]); 
    }
  } 

  // Iterating through all of the relevant rows to collect street names 
  // Instantiating TrafficLight objects with those stnames, stnums, and count 
  // Using the TrafficLight objects to instantiate TrafficController objects 
  for (int i=0; i<relevantCNNs.size(); i++) {
    // cnn number, convert it from string to int 
    int rowNum = relevantRowNums[i]; 
    string cnn = relevantCNNs[i]; 

    // street strings 
    string street1 = sf.GetCell<string>("STREET1", rowNum);
    string street2 = sf.GetCell<string>("STREET2", rowNum);
    string street3;             // initalize string for street 3 in case it exists 
    string street4;             // initalize string for street 4 in case it exists

    // instantiate traffic light objects 
    TrafficLight trafLight1(cnn, street1, 1, k++); 
    TrafficLight trafLight2(cnn, street2, 2, k++);
    TrafficLight trafLight3;    // initalize object for street 3 in case it exists 
    TrafficLight trafLight4;    // initalize object for street 4 in case it exists
    
    // check if streets 3 and 4 are empty or not 
    // if they are non-empty, assign them, instantiate with them, append 
    if (!(sf.GetCell<string>("STREET3", rowNum)).empty()) {
      street3 = sf.GetCell<string>("STREET3", rowNum);
      trafLight3 = TrafficLight(cnn, street3, 3, k++); 
    } 
    if (!(sf.GetCell<string>("STREET4", rowNum)).empty()) {
      street4 = sf.GetCell<string>("STREET4", rowNum);
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

  // OUTPUT FILES (preparation)
  // Prepare output csv file 
  ofstream csv;
  csv.open("myfile.csv"); 
  csv << "CNN, Street Name, Color,\n"; 

  // Prepare output kml file 
  ofstream kml; 
  kml.open("myfile.kml"); 
  kml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"; 
  kml << "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n"; 
  kml << "<Document>\n"; 

  // Write the final light states to a csv file 
  for (int i; i<allTCs.size(); i++) {
    allTCs[i].writecsv(csv); 
  }  
  csv.close(); 

  // Write the final light states to a km file 
  string prefix = "i"; 
  string suffix = ".png";
  for (int i=0; i<allTCs.size(); i++) {
    string combo; 
    string streetNames; 

    vector<TrafficLight> lights = allTCs[i].getAllLights(); 
    int numLights = lights.size(); 

    for (int j=0; j<numLights; j++) {
      char color = lights[j].getCurrentColor(); 
      combo += color; 
      string name = lights[j].getStreetName(); 
      if (numLights==2 && j==0) {
        streetNames += name + " ";
      }
      else if (numLights==2 && j==1) {
        streetNames += "and " + name; 
      }
      else if (numLights==3 && (j==0 || j==1)) {
        streetNames += name+", "; 
      }
      else if (numLights==3 && j==2) {
        streetNames += "and " + name;
      }
      else if (numLights==4 && (j==0 || j==1 || j==2)) {
        streetNames += name+", "; 
      }
      else if (numLights==4 && j==3) {
        streetNames += "and " + name;
      }
      else {
        cout << "Wrong number of traffic lights"; 
      }
    }
 
    string iconName = prefix + combo; 
    string fileName = prefix + combo + suffix; 

    // kml.open("myfile.kml"); // ?? 
    kml << " <Style id=\"" << iconName << "\">\n"; 
    kml << "  <IconStyle id=\"" << iconName << "\">\n"; 
    kml << "   <Icon>\n"; 
    kml << "    <href>files/" << fileName << "</href>\n"; 
    kml << "    <scale>1.0</scale>\n";  
    kml << "   </Icon>\n"; 
    kml << "  </IconStyle>\n"; 
    kml << " </Style>\n"; 
      
    int rowNum = relevantRowNums[i];
    string cnn = relevantCNNs[i]; 
    auto shapeCell = sf.GetCell<string>("shape", rowNum);
    string coordNums = shapeCell.substr(shapeCell.find("(")+1, shapeCell.find(")")-1); 
    string coord1 = coordNums.substr(0, coordNums.find(" ")); 
    string coord2 = coordNums.substr(coordNums.find(" ")+1); 

    kml << " <Placemark>\n"; 
    kml << "  <name>" + cnn << "</name>\n"; 
    kml << "  <description>" << streetNames << "</description>\n";
    kml << "  <styleUrl>#" << iconName << "</styleUrl>\n"; 
    kml << "  <Point>\n"; 
    kml << "   <coordinates>" << coord1 << "," << coord2 << "</coordinates>\n"; 
    kml << "  </Point>\n"; 
    kml << " </Placemark>"; 
  }

  // Footnotes for kml file, close the file 
  kml << "</Document>\n"; 
  kml << "</kml>\n"; 
  kml.close(); 

  return 0; 
}