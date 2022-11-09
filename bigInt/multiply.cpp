#include <iostream>
#include <fstream>
#include <cstdlib>
#include "bigint.hpp"

//Until end of file
   //Read two bigints
   //Print them out
   //Multiply them
   //Print out results

 int main() {
   std::ifstream in("data1-2.txt");    // Define stream for input
   if(!in) {                           // Make sure it opened correctly.
     std::cerr << "Could not open data1-2.txt, exiting." << std::endl;
     exit(1);
   }

   bigint bigintOne, bigintTwo, product;

   in >> bigintOne;
   in >> bigintTwo;

   while (!in.eof()) {
     std::cout << "Left Operand:   " << bigintOne << std::endl;
     std::cout << "Right Operand:  " << bigintTwo << std::endl;
     product = bigintOne * bigintTwo;
     std::cout << "Result: " << product << std::endl;
     in >> bigintOne;
     in >> bigintTwo;
   }

   in.close();
   return 0;
 }
