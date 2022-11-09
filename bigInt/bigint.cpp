//
//  bigint.cpp
//  Big Int
//
//  Created by Andrew Robinson on 9/13/17.
//

#include "bigint.hpp"

// Initialize bigint to zero
void bigint::fillZero() {
  for (int i=0; i<SIZE; i++){
    bigintArr[i] = 0;
  }
}

// Default constructor
bigint::bigint(){
  fillZero();
}

// Initialize bigint to an int value
bigint::bigint(int x){
  fillZero();
  for (int i=0; i < SIZE; i++){
    bigintArr[i] = x % 10;
    x /= 10;
  }
}

// Initialize bigint to a constant character array
bigint::bigint(const char x[]){
  fillZero();
  int length = 0;
  int j = 0;
  while (x[length] != '\0'){
    ++length;
  }
  for (int i = (length - 1); i >=0; i--, j++){
    bigintArr[j] = int(x[i]) - int('0');
  }
}

// Prints out each element of bigint
void bigint::debugPrint(std::ostream& out) const{
  int i = SIZE; // array index
  int j = 0;

  while(bigintArr[i] == 0){
    --i;
  }

  while(i >= 0){
    if (j % 50 != 0)
      out << bigintArr[i];
    else
      out << std::endl << bigintArr[i];
    --i;
    ++j;
  }
}

// Compare if two bigints are equal
bool bigint::operator==(const bigint& rhs){
  for (int i=0; i<SIZE; i++){
    if (bigintArr[i] != rhs.bigintArr[i])
      return false;
  }
  return true;
}

// Overload >> operator

std::istream& operator>>(std::istream& in, bigint& bi){
  char charArray[SIZE];
  char tempChar;

  for(int i = 0; i < SIZE; i++){
    in >> tempChar;
    if(tempChar == ';'){
      charArray[i] = '\0';
      break;
    }
    charArray[i] = tempChar;
  }
  bi = bigint(charArray);
  return in;
}

// Write a bigint to a stream
void bigint::output(std::ostream& out) const{
  int temp = SIZE, Output = 0;
  while (temp > 0 && bigintArr[temp] == 0){
    --temp;
  }

  while (temp >= 0){
    if (temp % 50)
      out << bigintArr[temp];
    else
      out << bigintArr[temp] << std::endl;
    --temp, ++Output;
  }
}

// Overload << operator
std::ostream& operator<<(std::ostream& out, bigint& rhs){
  rhs.output(out);
  return out;
}

// Overload + operator
bigint bigint::operator+(bigint rhs) const {
  bigint result;
  int carrier = 0;
  for(int i = 0; i < SIZE; i++){
    int add = bigintArr[i] + rhs.bigintArr[i] + carrier;
    if(add > 9)  // carry 1 to index+1
      carrier = 1;
    else
      carrier = 0;
    result.bigintArr[i] = add % 10;
  }
  return result;
}

// Overload [] operator
int bigint::operator[](int i) const { // change this variable name
  if ((i<0) || (i >= SIZE)) return 0;
  return bigintArr[i];
}

// multiplies a bigint and a single digit integer between 0 and 9
bigint bigint::timesDigit(int digit) const {
  bigint result;
  int product = 0, remainder = 0;
  for (int i = 0; i < SIZE; i++){
    remainder = bigintArr[i] * digit + remainder;
    product = remainder % 10;
    remainder /=10;
    result.bigintArr[i] = product;
  }
  return result;
}
// to multiply a bigint by 10^n with n>0
bigint bigint::times10(int pwr) const{
  bigint result;
  for (int i = SIZE - pwr - 1; i >= 0; i--)
    result.bigintArr[i+pwr] = bigintArr[i];
  for (int j = 0; j < pwr; j++)
    result.bigintArr[j] = 0;
  return result;
}

// Overload operator* to multiply two bigints
bigint bigint::operator*(bigint rhs) const{
  bigint product, temp;
  for(int i = 0; i < SIZE; ++i){
    temp = timesDigit(rhs.bigintArr[i]);
    product = product + temp.times10(i);
  }
  return product;
}
