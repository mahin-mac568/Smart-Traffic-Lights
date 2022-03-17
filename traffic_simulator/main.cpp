#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <unordered_map>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "AlertEvent.hpp"
#include "Car.hpp"
#include "Street.hpp"
#include "TrafficIntersection.hpp"
#include "TrafficLight.hpp"
#include "constants.hpp"
#include "csv.hpp"

csv TL, SC;

// the length of the event vector 
const int LENGTH = 20000; 

// extern std::queue<std::pair<int, AlertEvent*>> myPriorityQueue;
extern std::vector<std::vector<std::shared_ptr<AlertEvent>>> eventVector;
extern std::map<int64_t, std::shared_ptr<Street>> streets;
extern std::vector<std::shared_ptr<AlertEvent>> cars;

// maps that store any stoi/stod values ever introduced to the program 
std::unordered_map<std::string,int> stoi_map; 
std::unordered_map<int,double> stod_map; 

// number of columns constant 
const int SYNC_COLS = 2;

// initialize empty event lists in the Event Vector 
// void initialize_event_lists
//   (std::vector<std::vector<std::shared_ptr<AlertEvent>>> eventVector); 

// counts for the number of times stoi and stod are called 
// int stoi_count = 0; 
// int stod_count = 0; 

// counter helper functions for stoi and stod (with definition)
// void increment_stoi(); 
// void increment_stod(); 

csv read_csv(const std::string& filename) {
    std::string line;
    csv the_csv;
    std::ifstream input_file(filename);
    if(!input_file.is_open()) {
        std::cerr << "Could not open the file - '" << filename << "'" << std::endl;
        return the_csv;
    }

    int nfields = -1, line_count = 0;

    while(std::getline(input_file, line)) {
        size_t idx = line.find('\r');
        if(idx != std::string::npos)
            line = line.substr(0, idx);
        ++line_count;
        std::vector<std::string> parsed;
        while((idx = line.find(',')) != std::string::npos) {
            parsed.push_back(line.substr(0, idx));
            line = line.substr(idx + 1);
        }
        parsed.push_back(line);
        the_csv.push_back(parsed);
        if(nfields == -1)
            nfields = parsed.size();
        else if(nfields != (int)parsed.size())
            std::cerr << "Error: The first line had " << nfields << " fields, but line " << line_count << " had " << parsed.size() << " fields!" << std::endl;
    }

    input_file.close();
    return the_csv;
}

std::string getStreet(csv TL, const std::vector<int>& col, const std::string& cnn1, const std::string& cnn2) {
  if(cnn1 == "0") {
        std::cerr << "ERROR! Using 0 as the origin for a street" << std::endl;
        return "ERROR";
    }
  if(cnn2 == "0")
        return "DESTINATION";
    int row1 = -1, row2 = -1;
    for(uint n = 1; (row1 == -1 || row2 == -1) && n < TL.size(); n++) {
        if(cnn1 == TL[n][0])
            row1 = n;
        if(cnn2 == TL[n][0])
            row2 = n;
    }
    if(row1 == -1 || row2 == -1) {
        return "UNKNOWN CNN";
    }
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(TL[row1][col[i]].size() > 0 && TL[row1][col[i]] == TL[row2][col[j]])
                return (TL[row1][col[i]]);
    return "UNKNOWN";
}

int main(const int argc, const char** argv) {
    // initialize_event_lists(std::vector<std::vector<std::shared_ptr<AlertEvent>>> eventVector); 

    int run_length = -1;
    for(int arg = 1; arg < argc; arg++) {
        if(argv[arg][0] != '-') {
            std::cerr << "Arguments must start with -" << std::endl;
            return EXIT_FAILURE;
        }
        switch(argv[arg][1]) {
            case 't': {
                run_length = atoi(argv[arg] + 3);
                break;
            }
            default: {
                std::cerr << "Usage: main -t=#" << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    if(run_length == -1) {
        std::cerr << "Usage: main -t=#" << std::endl;
        return EXIT_FAILURE;
    }
    // need to make sure simulation isn't too long, or else cars won't finish 
    if (run_length > LENGTH - 10000) {
        std::cerr << "-t was greater than 10000, please re-enter a smaller time." << std::endl;
        return EXIT_FAILURE;
    }
    TL = read_csv("Traffic_Signals_SF.csv");
    SC = read_csv("Sync_And_Cars.csv");
    std::vector<int> streetColumnIndexes(4);  // Col 0 is never used for STREET
    for(uint n = 0; n < TL[0].size(); n++) {
        // Figure out which columns have street names in them
      if(TL[0][n] == "STREET1")
            streetColumnIndexes[0] = n;
      else if(TL[0][n] == "STREET2")
            streetColumnIndexes[1] = n;
      else if(TL[0][n] == "STREET3")
            streetColumnIndexes[2] = n;
      else if(TL[0][n] == "STREET4")
            streetColumnIndexes[3] = n;
    }
    for(auto& ts : TL) {
      if(ts[0] == "CNN")
            continue; 
        if (!stoi_map.contains(ts[0])) {
            stoi_map[ts[0]] = stoi(ts[0]); 
        }
        auto lights = std::make_shared<std::vector<std::shared_ptr<TrafficLight>>>();
        for(int i = 0; i < 4 && streetColumnIndexes[i] != 0; i++)
            if(ts[streetColumnIndexes[i]].size() != 0) {
                
                lights->push_back(std::make_shared<TrafficLight>(stoi_map[ts[0]], ts[streetColumnIndexes[i]]));
                // increment_stoi(); 
            } 
        auto ti = new TrafficIntersection(ts, lights); 
        intersections.emplace(stoi_map[ts[0]], std::shared_ptr<AlertEvent>(static_cast<AlertEvent*>(ti)));
        // increment_stoi(); 
    }

    int64_t total_runtime[HEAVY + 1][SYNC + 1];
    for(int traffic = LIGHT; traffic <= HEAVY; traffic++) {
        for(int sync = UNSYNC; sync <= SYNC; sync++) {
            for(uint c = 0; c < SC[0].size(); c++)
                for(uint n = SKIPROWS; n < SC.size() - 1; n++) {
                    // Only creates a Street object for streets actually used by our cars
                    if (!stoi_map.contains(SC[n][c])) {
                        stoi_map[SC[n][c]] = stoi(SC[n][c]);
                    }  
                    if (!stoi_map.contains(SC[n + 1][c])) {
                        stoi_map[SC[n + 1][c]] = stoi(SC[n + 1][c]);
                    }  
                    int from = stoi_map[SC[n][c]], to = stoi_map[SC[n + 1][c]];
                    // increment_stoi(); 
                    // increment_stoi(); 
                    long key = ((long)from << 32) | (long)to;
                    std::string name = getStreet(TL, streetColumnIndexes, SC[n][c], SC[n + 1][c]);
                    bool done = SC[n + 1][c] == "0";
                    std::shared_ptr<Street> st;
                    if((st = streets[key]) == nullptr) {
                        st = std::make_shared<Street>(traffic == LIGHT ? 20 : (traffic == MEDIUM ? 5 : 2), from, to, name, done, sync == SYNC && c < SYNC_COLS);
                        streets[key] = st;
                    }
                    if(sync == SYNC && c < SYNC_COLS) {
                        for(auto& ipae : intersections) {
                            auto ti = static_cast<TrafficIntersection*>(ipae.second.get());
                            auto lights = ti->myLights;
                            for(auto& tl : (*lights))
			      if(tl->myStreet == name && (tl->myCNN == from || tl->myCNN == to)) {
                                    tl->isSynchronized = true;
                                }
                        }
                    }
                    if(to == 0)
                        break;
                }
            // Initialize intersections
            int k = 0;
            TrafficIntersection::reset();
            if(sync == SYNC) {
                // Initialize the synchronized intersections (columns A and B)
                for(int c = 0; c <= 1; c++)
		  for(uint n = SKIPROWS; n < SC.size() - 1 && SC[n][c] == "0"; n++) {
                        if (!stoi_map.contains(SC[n][c])) {
                            stoi_map[SC[n][c]] = stoi(SC[n][c]);
                        }  
                        auto itae = intersections[stoi_map[SC[n][c]]];
                        // increment_stoi(); 
                        auto it = static_cast<TrafficIntersection*>(itae.get());
                        int beGreenAt = ((n - 2) * 15) % ((SYNCSTAYSGREEN + YELLOWDURATION) + (it->myLights->size() - 1) * 40);
                        std::string streetName;
                        if(n != SKIPROWS)
                            streetName = getStreet(TL, streetColumnIndexes, SC[n - 1][c], SC[n + 1][c]);
                        else
                            streetName = std::string("UNKNOWN");
                        it->setTimer(itae, SYNCSTAYSGREEN, beGreenAt, streetName, true);
                    }
            }
            // Now initialize all remaining intersections
            for(auto& tiae : intersections) {
                auto ti = static_cast<TrafficIntersection*>(tiae.second.get());
                if(ti->isInitialized)
                    continue;
                if(k % 25 == 0)
                    ti->setTimer(tiae.second, 90, 0, "INIT-STREET1-90", false);
                else if(k % 25 < 15)
                    ti->setTimer(tiae.second, 60, 0, "INIT-STREET1-60", false);
                else
                    ti->setTimer(tiae.second, 30, 0, "INIT-STREET1-30", false);
                ++k;
            }
            // Now create waves of cars, spaced one second out per wave
            int max_cars = SC[0].size();
            for(int sec = 0; sec < run_length; sec++)
                for(int car_n = 0; car_n < max_cars; car_n++) {
                    auto car = new Car(car_n, sec, traffic);
                    auto sc = std::shared_ptr<AlertEvent>(static_cast<AlertEvent*>(car));
                    cars.push_back(sc);
                    car->setTimer(sc, sec);
                }

            // Run simulation as long as there are still some active cars
            while(Car::active_cars > 0) {
                AlertEvent::runAll();
            }

            cars.clear();
            streets.clear();

            total_runtime[traffic][sync] = Car::total_driving_time;
            Car::reset();
            AlertEvent::resetQueue();
        }
    }

    // // Print number of times stoi was called 
    // std::cout << stoi_count << std::endl; 

    // // Print number of times stod was called 
    // std::cout << stod_count << std::endl; 

    // Print output
    std::cout << "		Without synchronization			With synchronization" << std::endl;
    std::cout << "Light traffic		" << std::setw(9) << total_runtime[LIGHT][UNSYNC] << "				" << std::setw(9) << total_runtime[LIGHT][SYNC] << std::endl;
    std::cout << "Medium traffic		" << std::setw(9) << total_runtime[MEDIUM][UNSYNC] << "				" << std::setw(9) << total_runtime[MEDIUM][SYNC] << std::endl;
    std::cout << "Heavy traffic		" << std::setw(9) << total_runtime[HEAVY][UNSYNC] << "				" << std::setw(9) << total_runtime[HEAVY][SYNC] << std::endl;
    return EXIT_SUCCESS;
}


// counter helper functions for stoi and stod (with definition)
// void increment_stoi() {
//     stoi_count++; 
// }
// void increment_stod() {
//     stod_count++; 
// }