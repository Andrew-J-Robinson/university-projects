#include <iostream>
#include <fstream>
#include <cstdlib>
#include "bigint.hpp"

//Until end of file
   //Read two bigints
   //Print them out
   //Add them together
   //Print out results

int main() {
  std::ifstream in("data1-1.txt");    // Define stream for input
  if(!in) {                           // Make sure it opened correctly.
    std::cerr << "Could not open data1-1.txt, exiting." << std::endl;
    exit(1);
  }

  bigint bigintOne, bigintTwo, sum;

  in >> bigintOne;
  in >> bigintTwo;

  while(!in.eof()){
    std::cout << "Left Operand: " << bigintOne << std::endl;
    std::cout << "Right Operand: " << bigintTwo << std::endl;
    sum = bigintOne + bigintTwo;
    std::cout << "Result: " << sum << std::endl << std::endl;
    in >> bigintOne;
    in >> bigintTwo;
  }

  in.close();
  return 0;
}
