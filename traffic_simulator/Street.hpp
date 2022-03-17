#pragma once
#include <map>
#include <memory>
#include <string>

class Street {
public:
    // street constructor  
    Street(const int, const int, const int, const std::string&, const bool, const bool);

    // member variables 
    int additionalCapacity;       // amount of remaining capacity on the street 
    int initialCapacity;          // amount of total capacity on the street 
    int fromCNN;                  // starting intersection CNN 
    int toCNN;                    // ending intersection CNN 
    bool isSynchronized;          // sync flag for this street 
    std::string myName;           // name of this street 
    bool isDestination;           // destination flag 
};

// global map of streets defined across all modules 
extern std::map<int64_t, std::shared_ptr<Street>> streets;
