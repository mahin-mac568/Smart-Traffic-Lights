/*
Based on Sagar’s sample hw1 solution
*/ 

#include "traffic_controller.hpp"
#include "color.hpp"

namespace controller {
    
    traffic_controller::traffic_controller(const uint32_t cnn,
                                           const std::vector<std::string>& names,
                                           const std::string& location)
    : cnn(cnn), location(location) 
    {
        for(const std::string& name : names) {
            lights.emplace_back(name);
        }
    }

    // overloaded constructor for synchronization
    traffic_controller::traffic_controller(const uint32_t cnn,
                                           const std::vector<std::string>& names,
                                           const std::string& location,
                                           bool synchronize)
    : cnn(cnn), location(location), is_synchronized(synchronize) 
    // if synchronize is passed in, then it is always passed in as true 
    {
        for(const std::string& name : names) {
            lights.emplace_back(name, is_synchronized);
        }
    }

    uint32_t traffic_controller::transition() {
        COLOR color = lights[cur_light].next_color();

        switch(color) {
            case COLOR::RED:
                cur_light = (cur_light + 1) % lights.size();
                lights[cur_light].next_color();
                return lights[cur_light].get_green_time();
            case COLOR::GREEN:
                return lights[cur_light].get_green_time();
            default:
                return traffic_light::yellow_time;
        }
    }

    void traffic_controller::print_csv(std::ofstream& fout) const {
        for(const traffic_light& light : lights) {
            fout << cnn << ",";
            light.print_csv(fout);
        }
    }

    void traffic_controller::print_kml(std::ofstream& fout) const {
        fout << "  <Placemark>\n";
        fout << "    <name>" << cnn << "</name>\n";

        std::string description;
        std::string icon_name = "i" + std::to_string(lights.size());
        for(uint32_t i = 0; i < lights.size() - 1; ++i) {
            description += lights[i].get_name() + " and ";
            icon_name += SHORT_COLORS[lights[i].get_color()];
        }
        description += lights.back().get_name();
        icon_name += SHORT_COLORS[lights.back().get_color()];

        fout << "    <description>" << description << "</description>\n";
        fout << "    <styleUrl>#" << icon_name << "</styleUrl>\n";

        size_t pos = location.find_first_of(' ', 7);
        std::string coord1 = location.substr(7, pos - 7);
        std::string coord2 = location.substr(pos + 1,
                                            location.find_first_of(')') - pos - 1);
        fout << "    <Point>\n";
        fout << "      <coordinates>" << coord1 << "," << coord2 << "</coordinates>\n";
        fout << "    </Point>\n";

        fout << "  </Placemark>\n";
    }

    std::vector<traffic_light> traffic_controller::get_lights() {
        return lights; 
    }

    // synchronization 
    void traffic_controller::synchronize_green_time(std::string street_name) {
        for (traffic_light& light : lights) {
            if (light.get_name() == street_name) {
                light.set_color(COLOR::GREEN); 
                light.set_green_time(90); 
            }
            else {
                light.set_green_time(90); 
            }
        }
    }


}  // namespace controller
