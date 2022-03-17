#include <iostream>
#include "Street.hpp"
#include "constants.hpp"

// global map of street objects 
std::map<int64_t, std::shared_ptr<Street>> streets;

// Constructor for Street Object 
Street::Street(const int additionalCapacity, const int fromCNN, 
               const int toCNN, const std::string& myName, 
               const bool isDestination, const bool isSynchronized) 
      : additionalCapacity(additionalCapacity), 
        initialCapacity(additionalCapacity), 
        fromCNN(fromCNN), toCNN(toCNN), isSynchronized(isSynchronized), 
        myName(myName), isDestination(isDestination) 
{
    /*
    All member variables are assigned via the arguments passed in. 
    The initial capacity variable is the same as the remaining capacity 
    to begin with. 
    */
}
