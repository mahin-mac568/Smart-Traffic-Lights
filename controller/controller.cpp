#include "controller.hpp"
#include "rapidcsv.h"
#include <iostream>
#include <string>

int main()
    {
      rapidcsv::Document doc("examples/colhdr.csv");

      std::vector<float> col = doc.GetColumn<float>("Close");
      std::cout << "Read " << col.size() << " values." << std::endl;
    }
