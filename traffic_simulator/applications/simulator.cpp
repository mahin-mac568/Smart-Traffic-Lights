#include <fstream>
#include <iostream>
#include <queue>
#include <cmath>
#include <utility>
#include <tuple>
#include <tr1/unordered_map>

#include "controller/traffic_controller.hpp"
#include "csv/csv_reader.hpp"
#include "event.hpp"
#include "movement/street.hpp"
#include "movement/car.hpp"


// HOMEWORK 1 GLOBAL FUNCTION DECLARATIONS  

std::vector<controller::traffic_controller> initialize_controllers
  (const std::string& csv_file_name);

std::priority_queue<event> create_events(const uint32_t total_events); 

void print_kml_header(std::ofstream& fout);
void print_icons(std::ofstream& fout);
void print_kml_footer(std::ofstream& fout);


// HOMEWORK 2 GLOBAL FUNCTION DECLARATIONS  

/* Creates a 2-dimensional vector out of the input csv data */
std::vector< std::vector<std::string> > create_2d_table
  (const std::string& csv_file_name); 

/* Creates a dictionary that maps cnn values to (latitude, longitude) coordinates */
std::tr1::unordered_map<uint32_t, std::pair<double, double>> create_coords_map
  (std::vector<std::vector<std::string>> tssf_table);  

/* Creates a dictionary that maps cnn values to vectors of street names */
std::tr1::unordered_map<uint32_t, std::vector<std::string>> create_s_names_map
  (std::vector<std::vector<std::string>> tssf_table); 

/* Derives the shared street name based on the streets of two intersections */
std::string obtain_street_name
  (std::vector<std::string> cnn0_snames, 
   std::vector<std::string> cnn1_snames, 
   std::string string_cnn0, std::string string_cnn1); 

/* Instantiates street objects and accumulates them to a vector */
std::vector<street> initialize_streets
  (std::vector<std::vector<std::string>> sc_table, 
   std::tr1::unordered_map<uint32_t, std::pair<double, double>> coords_map,
   std::tr1::unordered_map<uint32_t, std::vector<std::string>> s_names_map, 
   uint32_t speed); 

/* Creates a dictionary that maps lookup keys to street objects */
std::tr1::unordered_map<uint32_t, street> create_street_map
  (std::vector<street> streets); 

/* Instantiates car objects and accumulates them to a vector */
std::vector<car> initialize_cars 
  (std::vector<std::vector<std::string>> sc_table,
   std::tr1::unordered_map<uint32_t, std::vector<std::string>> s_names_map,
   uint32_t speed); 
   

/* MAIN PROGRAM */
int main(int argc, char* argv[]) {
    
    // HOMEWORK 1 

    if(argc < 2) {
        std::cout << "Usage: ./<exec> -t=<time>" << std::endl;
        return 0;
    }

    uint32_t total_time = std::stoi(std::string(argv[1]).substr(3));

    std::vector<controller::traffic_controller> controllers
            = initialize_controllers("Traffic_Signals_SF.csv");

    std::priority_queue<event> events = create_events(controllers.size());

    while(!events.empty()) {
        const event current = events.top();
        events.pop();
        uint32_t next_time = current.get_time() + controllers[current.get_index()].transition();
        if(next_time <= total_time) {
            events.emplace(current.get_index(), next_time);
        }
    }

    {
        std::ofstream fout("myfile.csv");
        fout << "CCN,street name,color\n";
        for(const controller::traffic_controller& controller : controllers) {
            controller.print_csv(fout);
        }
    }

    {
        std::ofstream fout("myfile.kml");
        print_kml_header(fout);
        print_icons(fout);
        for(const controller::traffic_controller& controller : controllers) {
            controller.print_kml(fout);
        }
        print_kml_footer(fout);
    }


    // HOMEWORK 2 

    /* Constant speed values for light or heavy traffic */ 
    const uint32_t LIGHT_TRAFFIC_SPEED = 30; 
    const uint32_t HEAVY_TRAFFIC_SPEED = 3; 

    /* Pairs with the different simulation types */ 
    std::pair<std::string, std::string> traffic_load_types 
      = { "light", "heavy" }; 
    std::pair<std::string, std::string> sync_types 
      = { "synchronized", "unsynchronized" }; 

    /* Initializing the simulation types –– to be cycled as program runs */ 
    std::string traffic_load = traffic_load_types.first; 
    std::string sync_type; 
    
    /* Initializing the car speeds based on the simulation type */ 
    uint32_t simulation_speed; 
    simulation_speed = (traffic_load == "light") ? 
      LIGHT_TRAFFIC_SPEED : HEAVY_TRAFFIC_SPEED; 

    /* Creating 2-dimensional tables out of the two datasets */ 
    std::vector< std::vector<std::string> > tssf_table 
            = create_2d_table("Traffic_Signals_SF.csv"); 
    std::vector< std::vector<std::string> > sc_table 
            = create_2d_table("Sync_And_Cars.csv"); 

    /* Creating the cnn-to-coordinate mappings */ 
    std::tr1::unordered_map<uint32_t, std::pair<double, double>> coords_map
            = create_coords_map(tssf_table);

    /* Creating the cnn-to-street-name mappings */ 
    std::tr1::unordered_map<uint32_t, std::vector<std::string>> s_names_map
            = create_s_names_map(tssf_table); 

    /* Instantiating all of the street objects into a vector */ 
    std::vector<street> streets 
        = initialize_streets(sc_table, coords_map, s_names_map, simulation_speed);

    /* Creating the cnn-to-street-object mappings */ 
    std::tr1::unordered_map<uint32_t, street> street_map 
            = create_street_map(streets); 

    /* Initializing the car objects into a vector */ 
    std::vector<car> cars = initialize_cars(sc_table, s_names_map, simulation_speed); 
}


// HOMEWORK 1 GLOBAL FUNCTION DEFINITIONS 

std::vector<controller::traffic_controller> initialize_controllers
  (const std::string& csv_file_name) 
{
    std::vector<controller::traffic_controller> controllers;

    const uint32_t CNN_INDEX = 0;
    const uint32_t TBC_INDEX = 12;
    const uint32_t STREET1_INDEX = 3;
    const uint32_t STREET2_INDEX = 4;
    const uint32_t STREET3_INDEX = 6;
    const uint32_t STREET4_INDEX = 8;
    const uint32_t SHAPE_INDEX = 34;

    std::ifstream fin(csv_file_name);
    std::string line;
    // read away the header line
    std::getline(fin, line);

    while(std::getline(fin, line)) {
        csv::fields_t fields = csv::parse_csv_fields(line);
        if(fields[TBC_INDEX] == "GPS") {
            std::vector<std::string> street_names;
            street_names.push_back(fields[STREET1_INDEX]);
            street_names.push_back(fields[STREET2_INDEX]);
            if(fields[STREET3_INDEX] != "") {
                street_names.push_back(fields[STREET3_INDEX]);
            }
            if(fields[STREET4_INDEX] != "") {
                street_names.push_back(fields[STREET4_INDEX]);
            }
            controllers.emplace_back(std::stoi(fields[CNN_INDEX]), street_names, fields[SHAPE_INDEX]);
        }
    }
    return controllers;
}

std::priority_queue<event> create_events(const uint32_t total_events) {
    std::priority_queue<event> events;

    for(uint32_t i = 0; i < total_events; ++i) {
        events.emplace(i);
    }
    return events;
}

void print_kml_header(std::ofstream& fout) {
    fout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    fout << "<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n";
    fout << "<Document>\n";
}

void print_icons_helper(std::ofstream& fout,
                        const std::string& id, const std::string& file_name) {
    fout << "  <Style id=\"" << id << "\">\n";
    fout << "    <IconStyle id=\"" << id << "\">\n";
    fout << "      <Icon>\n";
    fout << "        <href>" << file_name << "</href>\n";
    fout << "        <scale>1.0</scale>\n";
    fout << "      </Icon>\n";
    fout << "    </IconStyle>\n";
    fout << "  </Style>\n";
}

void print_icons(std::ofstream& fout) {
    for(const std::string& color1 : controller::SHORT_COLORS) {
        for(const std::string& color2 : controller::SHORT_COLORS) {
            std::string id = "i2" + color1 + color2;
            std::string file_name = "files/i2" + color1 + color2 + ".png";
            print_icons_helper(fout, id, file_name);

            for(const std::string& color3 : controller::SHORT_COLORS) {
                std::string id = "i3" + color1 + color2 + color3;
                std::string file_name = "files/i3" + color1 + color2 + color3 + ".png";
                print_icons_helper(fout, id, file_name);

                for(const std::string& color4 : controller::SHORT_COLORS) {
                    std::string id = "i4" + color1 + color2 + color3 + color4;
                    std::string file_name = "files/i4" + color1 + color2 + color3 + color4 + ".png";
                    print_icons_helper(fout, id, file_name);
                }
            }
        }
    }
}

void print_kml_footer(std::ofstream& fout) {
    fout << "</Document>\n";
    fout << "</kml>\n";
}


// HOMEWORK 2 GLOBAL FUNCTION DEFINITIONS 

/* Creates a 2-dimensional vector out of the input csv data */
std::vector< std::vector<std::string> > create_2d_table
  (const std::string& csv_file_name) 
{
    std::vector< std::vector<std::string> > table; 

    std::ifstream fin(csv_file_name);   // input file 
    std::string line;                   // declare the header string
    std::getline(fin, line);            // read and pipe in the header line
    
    uint32_t i = 0; 

    while(std::getline(fin, line)) {
        if (csv_file_name == "Traffic_Signals_SF.csv") {
            if (i == 0) {
                i++; 
                continue; 
            }
        }
        else {  // if the csv file name is "Sync_And_Cars.csv"
            if (i < 2) {
                i++; 
                continue; 
            }
        }
        csv::fields_t fields = csv::parse_csv_fields(line);
        table.push_back(fields); 
        i++; 
    }
    return table; 
}

/* Creates a dictionary that maps cnn values to (latitude, longitude) coordinates */ 
std::tr1::unordered_map<uint32_t, std::pair<double, double>> create_coords_map
  (std::vector<std::vector<std::string>> tssf_table) 
{
    std::tr1::unordered_map<uint32_t, std::pair<double, double>> coords_map; 
    
    const uint32_t CNN_INDEX = 0;
    const uint32_t SHAPE_INDEX = 34;

    for (int i=0; i<tssf_table.at(CNN_INDEX).size(); i++) {
        uint32_t cnn = std::stoi(tssf_table.at(CNN_INDEX).at(i)); 
        std::string str_coords = tssf_table.at(SHAPE_INDEX).at(i); 
        uint32_t fstIdx = str_coords.find("(")+1; 
        uint32_t sndIdx = str_coords.find(")"); 
        uint32_t len = sndIdx - fstIdx; 
        std::string coordNums = str_coords.substr(str_coords.find("(")+1, len); 
        std::string latitude = coordNums.substr(0, coordNums.find(" ")); 
        std::string longitude = coordNums.substr(coordNums.find(" ")+1); 
        std::pair<double, double> coords(std::stod(latitude), std::stod(longitude)); 
        coords_map.insert({ cnn, coords });
    }
    return coords_map; 
}

/* Creates a dictionary that maps cnn values to vectors of street names */ 
std::tr1::unordered_map<uint32_t, std::vector<std::string>> create_s_names_map
  (std::vector<std::vector<std::string>> tssf_table) 
{
    std::tr1::unordered_map<uint32_t, std::vector<std::string>> s_names_map; 

    const uint32_t CNN_INDEX = 0;
    const uint32_t STREET1_INDEX = 3;
    const uint32_t STREET2_INDEX = 4;
    const uint32_t STREET3_INDEX = 6;
    const uint32_t STREET4_INDEX = 8;

    for (int i=0; i<tssf_table.at(CNN_INDEX).size(); i++) {
        uint32_t cnn = std::stoi(tssf_table.at(CNN_INDEX).at(i)); 
        std::string street1_name = tssf_table.at(STREET1_INDEX).at(i); 
        std::string street2_name = tssf_table.at(STREET2_INDEX).at(i); 
        std::string street3_name = tssf_table.at(STREET3_INDEX).at(i); 
        std::string street4_name = tssf_table.at(STREET4_INDEX).at(i); 

        std::vector<std::string> street_names
          { street1_name, street2_name, street3_name, street4_name }; 

        s_names_map.insert({ cnn, street_names });
    }
    return s_names_map; 
}

/*  */ 
std::string obtain_street_name
  (std::vector<std::string> cnn0_s_names, std::vector<std::string> cnn1_s_names,
   std::string string_cnn0, std::string string_cnn1) 
{
    std::string shared_street; 
    std::string street_name; 

    for (std::string cnn0_street_name : cnn0_s_names) {
        for (std::string cnn1_street_name : cnn1_s_names) {
            if (cnn0_street_name == cnn1_street_name) {
                shared_street = cnn0_street_name; 
            }
        }
    }

    if (shared_street == "") {
        street_name = "UNKNOWN FROM " + string_cnn0 + " TO " + string_cnn1; 
    }
    else {
        street_name = shared_street + " FROM " + string_cnn0 + " TO " + string_cnn1;
    }

    return shared_street; 
}

/* Derives the shared street name based on the streets of two intersections */ 
std::vector<street> initialize_streets
  (std::vector<std::vector<std::string>> sc_table, 
   std::tr1::unordered_map<uint32_t, std::pair<double, double>> coords_map,
   std::tr1::unordered_map<uint32_t, std::vector<std::string>> s_names_map, 
   uint32_t speed) 
{
    std::vector<street> streets;

    for (int i=0; i<sc_table.size(); i++) {
        for (int j=0; j<sc_table.at(i).size()-1; j++) {
            std::string string_cnn0 = sc_table.at(i).at(j); 
            std::string string_cnn1 = sc_table.at(i).at(j+1); 
            uint32_t cnn0 = std::stoi(string_cnn0); 
            uint32_t cnn1 = std::stoi(string_cnn1); 
            std::pair<double,double> coords0 = coords_map[cnn0];
            std::pair<double,double> coords1 = coords_map[cnn1];
            std::vector<std::string> cnn0_s_names = s_names_map[cnn0]; 
            std::vector<std::string> cnn1_s_names = s_names_map[cnn1]; 
            std::string street_name = obtain_street_name
              (cnn0_s_names, cnn1_s_names, string_cnn0, string_cnn1); 
            street st(cnn0, cnn1, coords0, coords1, street_name, speed); 
            streets.push_back(st); 
        }
    }
    return streets; 
}

/* Creates a dictionary that maps lookup keys to street objects */ 
std::tr1::unordered_map<uint32_t, street> create_street_map(std::vector<street> streets) {
    std::tr1::unordered_map<uint32_t, street> street_map; 
    
    for(street& st : streets) {
        street_map.insert({ st.get_lookup_key(), st });
    }
    return street_map; 
}

/* Instantiates car objects and accumulates them to a vector */ 
std::vector<car> initialize_cars 
  (std::vector<std::vector<std::string>> sc_table,
   std::tr1::unordered_map<uint32_t, std::vector<std::string>> s_names_map, 
   uint32_t speed)
{
    std::vector<car> cars; 

    for (int i=0; i<sc_table.size(); i++) {
        std::vector<std::string> car_path = sc_table.at(i);
        std::string string_cnn0 = car_path.at(0);
        std::string string_cnn1 = car_path.at(1);
        uint32_t cnn0 = std::stoi(string_cnn0); 
        uint32_t cnn1 = std::stoi(string_cnn1); 
        std::vector<std::string> cnn0_street_names = s_names_map[cnn0]; 
        std::vector<std::string> cnn1_street_names = s_names_map[cnn1]; 
        std::string street_name = obtain_street_name
          (cnn0_street_names, cnn1_street_names, string_cnn0, string_cnn1);
        car c(street_name, car_path, speed); 
        cars.push_back(c); 
    }

    return cars; 
}