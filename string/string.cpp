//
//  string.cpp
//  Dynamic String
//
//  Created by Andrew Robinson on 10/18/17.
//  Copyright © 2017 Andrew Tennant. All rights reserved.
//

#include "string.hpp"
#include "logentry.hpp"
#include <vector>

// Default Constructor - empty string
//////////////////////////////////////////////////
String::String () {
  stringSize = 1;
  str = new char('\0');
}

//String of capacity n
//////////////////////////////////////////////////
String::String(int n) {
  stringSize = n+1;
  str = new char[stringSize];
  str[0] = '\0';
}

// Constructor for a single character
//////////////////////////////////////////////////
String::String (char ch) {
  stringSize = 2;
  str = new char[2];
  str[0] = ch;
  str[1] = '\0';
}// Get line
//////////////////////////////////////////////////                                                  //
String String::getline(std::istream& in) {
  String line;
  char ch = '\0';

  for (int i = (in.get(ch), 0); (ch != '\n') && (!in.fail()); ++i, in.get(ch)) {
    if (i == ( line.length() ))
      line.resetCapacity(line.length() * 2);
    line = line + ch;
  }

  return line;
}

// String of capacity n and initial value
//////////////////////////////////////////////////
String::String (int n, const char* ch) {
  stringSize = n+1;
  str = new char[stringSize];
  int i = 0;
  while(ch[i] != '\0') {
    str[i] = ch[i];
    ++i;
  }
  str[i] = '\0';
}

// Constructor for an array of characters
//////////////////////////////////////////////////
String::String (const char ch[]) {
  int len = 0; //length of character array
  int i = 0;
  while (ch[i] != '\0') {
    ++len;
    ++i;
  }
  str = new char[len+1];
  int j = 0;
  while(ch[j] != '\0') {
    str[j] = ch[j];
    ++j;
  }
  str[j] = '\0';
  stringSize = j+1;
}

// Convert String to Integer
//////////////////////////////////////////////////
int String::intConvert() {
  int start = length() - 1;
  if (str[start] == '-')
     return 0;

  int result = 0, tens = 1;

  for (int i = start; i >= 0; --i) {
    result = result + (int(str[i] - int('0')) * tens);
    tens *= 10;
  }
  return result;
}

// Copy Constructor
//////////////////////////////////////////////////
String::String (const String& rhs) {
  str = new char [rhs.length()];
  int i = 0;
  while (rhs[i] != '\0') {
    str[i] = rhs[i];
    ++i;
  }
  str[i] = '\0';
  stringSize = i+1;
}

// Destructor
//////////////////////////////////////////////////
String::~String() {
  delete[] str;
}

// length of string
//////////////////////////////////////////////////
int String::length() const {
  int len = 0;
  for (int i = 0; str[i] != '\0'; ++i) {
    ++len;
  }
  return len;
}

// capacity of string
//////////////////////////////////////////////////
int String::capacity() const {
  return stringSize - 1;
}

// Swap
//////////////////////////////////////////////////
void String::swap (String& rhs) {
  char *temp = str;
  str = rhs.str;
  rhs.str = temp;

  int tempSize = stringSize;
  stringSize = rhs.stringSize;
  rhs.stringSize = tempSize;
}

String& String::operator= (String rhs) {
  swap(rhs);
  return *this;
}

// Reset capacity of string
//////////////////////////////////////////////////
void String::resetCapacity(int n) {
  char *temp = new char[n];
  for (int i = 0; i < length(); ++i)
      temp[i] = str[i];
  delete[] str;
  str = temp;
  stringSize = n;
}

// + operator overload (concatenation)
//////////////////////////////////////////////////
String String::operator+(const String& rhs)const
{
  String result(str);
  if((rhs.length()+length()+1)>capacity())
    result.resetCapacity(rhs.length()+length()+1);
  int offset = length();
  int i = 0;

  while(rhs.str[i] != '\0'){
    result.str[offset + i] = rhs.str[i];
    ++i;
  }

  result.str[offset + i] = '\0';
  result.stringSize = offset+i+1;
  return result;
}

// Overload += operator
//////////////////////////////////////////////////
String& String::operator+=(String rhs){
  if((rhs.length()+length()+1)>capacity())
    resetCapacity(rhs.length()+length()+1);
 int start = length();
  int i = 0;
  while(rhs.str[i] != '\0'){
    str[start+i] = rhs.str[i];
    ++i;
  }
  str[start+i] = '\0';
  return *this;
}

//Accessor/Modifier
//////////////////////////////////////////////////
char& String::operator[] (int index) {
  return str[index];
}

//Accessor
//////////////////////////////////////////////////
char String::operator[] (int index) const {
  return str[index];
}

// Overload == operator
//////////////////////////////////////////////////
bool String::operator==(const String& rhs) const {
  int i = 0;
  while ((str[i] != '\0') && (str[i] == rhs.str[i])) {
    ++i;
  }
  return str[i] == rhs.str[i];
}

// overload < operator
//////////////////////////////////////////////////
bool String::operator<(const String& rhs) const {
  int i = 0;
  while ((str[i] != '\0') && (rhs[i] != '\0') && (str[i] == rhs[i])) {
    ++i;
  }
  return str[i] < rhs[i];
}

// Substring
//////////////////////////////////////////////////
String String::substr(int start, int end) const {
  if (start < 0)
    start = 0;
  if (end > capacity())
    end = capacity();
  //--------------------------
  int newSize = 0;
  if (start == end)
    newSize = 2;
  else
    newSize = end - start +1;
  //--------------------------
  char  temp[newSize];
  int i;
  for (i = start; i <= end; ++i) {
    temp[i - start] = str[i];
  }
  temp[i - start] = '\0';
  String result(temp);
  return result;
}

// Find character
//////////////////////////////////////////////////
int String::findch(int pos, char ch) const {
  if (pos < 0) {
    pos = 0;
  }
  if (pos > length() - 1) {
    return -1;
  }
  int i = pos;
  while(str[i] != '\0') {
    if (ch == str[i]) {
      return i;
    }
    ++i;
  }
  return -1;
}

// Find String
//////////////////////////////////////////////////
int String::findstr(int pos, String const& s) const {
  if (pos < 0) {
    pos = 0;
  }
  if (pos > length() - s.length()) {
    return -1;
  }
  int len = s.length();
  int i = pos;
  while (str[i] != '\0') {
    if (substr(i, i + len - 1) == s) {
      return i;
    }
    ++i;
  }
  return -1;
}

// Overload << operator
//////////////////////////////////////////////////
std::ostream& operator<<(std::ostream& out, const String& rhs) {
  out << rhs.str;
  return out;
}

// Overload >> operator
//////////////////////////////////////////////////
std::istream& operator>>(std::istream& in, String& rhs) {
  in >> rhs.str;
  return in;
}

// Split
/////////////////////////////////////////////////
std::vector<String> String::split(char ch) const {
  std::vector<String> result;

  if (ch == '\0') {
    for (int i = 0; i < length(); ++i){
      result.push_back(str[i]);
    }
    return result;
  }

  String temp;

  for (int i = 0; i < length(); ++i){
    if (str[i] != ch) {
      temp = temp + str[i];
    }else{
      result.push_back(temp);
      if (str[i+1] != str[i]){
	temp = str[++i];
      }else{
	String temp2;
	temp = temp2;
      }
    }
  }
  return (result.push_back(temp), result);
}

// Free Functions
//////////////////////////////////////////////////
bool operator== (const char lhs[],  const String& rhs) {
  return String(lhs) == rhs;
}

// overload > operator
bool operator> (const String& lhs, const String& rhs) {
  return (rhs < lhs);
}

// overload <= operator
bool operator<= (const String& lhs, const String& rhs) {
  return !(rhs < lhs);
}

// overload != operator
bool operator != (const String& lhs, const String& rhs) {
  return !(lhs == rhs);
}

// overload >= operator
bool operator>= (const String& lhs, const String& rhs) {
  return (rhs < lhs);
}

// overload < operator
bool operator< (const char lhs, const String& rhs) {
  return String(lhs) < rhs;
}

bool operator< (const char lhs[], const String& rhs) {
  return String(lhs) < rhs;
}

// overload + operator
String operator+ (char lhs, const String& rhs) {
  return String(lhs) + rhs;
}

String operator+ (const char lhs[], const String& rhs) {
  return String(lhs) + rhs;
}
