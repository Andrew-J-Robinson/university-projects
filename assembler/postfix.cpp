/*
  Andrew Tennant

  postfix.cpp

  Reads a set of infix expressions from a file and writes the infix and postfix expressions to another file.
*/

#include <iostream>
#include <fstream>
#include "stack.hpp"
#include "utilities.hpp"
//#include "../string/string.hpp"

int main(int argc, char const* argv[]) {
  if (argc < 2) {
    std::cerr << "Input file not found!" << std::endl;
    return 0;
  }

  std::ifstream infix(argv[1]);

  if (!infix) {
    std::cerr << "Infix file not found!" << std::endl;
    return 0;
  }

  std::ofstream postfix(argv[2]);

  if(!postfix) {
    std::cerr << "Can't open output file. Try again!" << std::endl;
    return 0;
  }

  toPostfix(infix, postfix);

  // Print contents of new file.
  std::ifstream in();

  infix.close();
  postfix.close();

  return 0;
}
