#include <iostream>

// test functions that call stoi and stod 
void stoi_tester(std::string test_str, int test_len); 
void stod_tester(std::string test_str, int test_len); 

int main() {
  // number of calls (1 million)
  const int TEST_LENGTH = 1000000; 

  // string to test stoi , string to test stod 
  const std::string TEST_STRING1 = "22585000"; // the first CNN in TS_SF csv 
  const std::string TEST_STRING2 = "122.456505"; // the first coordinate value in TS_SF csv 

  // call the test functions , comment one out at a time to see duration of each one separately 
  stoi_tester(TEST_STRING1, TEST_LENGTH);   
  stod_tester(TEST_STRING2, TEST_LENGTH);   
}

// definition for stoi test function 
void stoi_tester(std::string test_str, int test_len) {
  for (int i=0; i<test_len; i++) {
    std::stoi(test_str); 
  } 
}

// definition for stod test function 
void stod_tester(std::string test_str, int test_len) {
  for (int i=0; i<test_len; i++) {
    std::stod(test_str); 
  } 
}