//
//  bigint.hpp
//  Big Int
//
//  Created by Andrew Robinson on 9/13/17.
//

#ifndef BIGINT_HPP_
#define BIGINT_HPP_

#include <iostream>
#include <cassert>
#include <fstream>
#include <cstdlib>

const int SIZE = 255;

class bigint {
public:

  // Constructors
  bigint();
  bigint(int);
  bigint(const char[]);
  void fillZero();

  // Operations
  void debugPrint(std::ostream&) const;
  void output(std::ostream&) const;
  bigint timesDigit(int) const;
  bigint times10(int) const;

  // Overloaded Operators
  bigint operator*(bigint) const;
  bigint operator+(bigint) const;
  bool operator==(const bigint&);
  int operator[](int) const;

  friend std::ostream& operator<<(std::ostream&, bigint&);
  friend std::istream& operator >> (std::istream&, bigint&);

private:
  int bigintArr[SIZE];
};

#endif /* BIGINT_HPP_ */
