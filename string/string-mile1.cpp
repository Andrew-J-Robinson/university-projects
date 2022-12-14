//
//  string.cpp
//  String
//
//  Created by Andrew Robinson on 10/4/17.
//
// Implemetation of string.hpp fucntions
// Constructor should initialize the string with a null terminator at position zero
// Capacity is SIZE - 1

#include "string.hpp"

//---Default Constructor---
String::String(){
  str[0] = '\0';
}

//---Character Constructor---
String::String(char first){
  str[0]=first;
  str[1] = '\0';
}

//---Character Array COnstructor---
String::String(const char charArr[]){
  int length = 0;
  int x = 0;
  do {
    ++length;
  }while(charArr[length]!='\0');
  for(int i = length -1;i >= 0; i++, x++){
    str[x]=int(charArr[i])-int('\0');
  }
}

//---Overload + operator---
String String::operator+(const String& rhs)const{
  int offset = length();
  String result(str);
  int i = 0;
  while (rhs.str[i] != '\0'){
    if ((offset + i) >= (capacity())) break;
    result.str[offset + i] = rhs.str[i];
    ++i;
  }
  result.str[offset + i] = '\0';
  return result;
}

//---Overload += operator---
String& String::operator+=(String rhs){
  int start = length();
  int i = 0;
  while(rhs.str[i] != '\0'){
    if((start+i) >= (capacity())) break;
    str[start+i] = rhs.str[i];
    ++i;
  }
  str[start+i] = '\0';
  return *this;
}

//---Overload == operator---
bool String::operator== (const String& rhs) const {
  if (length() == rhs.length()){
      for (int i=0; str[i] != '\0' && rhs[i] != '\0'; ++i){
	if (str[i] != rhs[i]){
	    return false;
	}
      }
      return true;
  }
  return false;
}

//---Overload < operator---
bool String::operator<(const String& rhs)const{
  int i = 0;
  while ((str[i] != '\0') &&
	 (rhs[i] != '\0') && (str[i] == rhs.str[i])){
    ++i;
  }
  return str[i] < rhs.str[i];
}

//---Overload input---
std::istream& operator>>(std::istream& in, String& rhs){
  in >> rhs.str;
  return in;
}

//---Overload output---
std::ostream& operator << (std::ostream& out, const String& rhs)
{
  for (int i = 0; i < rhs.length(); ++i) {
    out << rhs[i];
  }

  return out;
}

//---Accessor/Modifier---
char& String::operator[](int i){
  return str[i];
}

//---Accessor---
char String::operator[](int i)const{
  return str[i];
}

//---Capacity---
int String::capacity()const{
  return STRING_SIZE -1;
}

//---Length---
int String::length()const{
  int len = 0;
  for(int i=0; str[i]!='\0';++i){
    ++len;
  }
  return len;
}

//---Find Substring---
String String::substr(int start, int end)const{
  String result;
  if(start<0)start=0;
  if(start>end)return result;
  if(end >= length())end=length()-1;
  if(end<0)return String();

  int i;
  for(i=start;i<=end;++i){
    result.str[i-start]=str[i];
  }
  result.str[i-start]='\0';
  return result;
}

//---Find Character---
int String::findch(int pos, char ch)const{
  if(pos<0) pos=0;
  if(pos> length()-1)return -1;

  int i = pos;
  while((str[i]!='\0')){
    if(ch == str[i]) return i;
    ++i;
  }
  return i;
}

//---Find String---
int String::findstr(int pos, const String& s) const {
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

//----------- STRING.HPP FREE FUNCTIONS -------------//

String operator+(const char lhs[], const String& rhs){
  return (String(lhs) + rhs);
}

String operator+(char lhs, const String& rhs){
  return (String(lhs) + rhs);
}

bool operator==(const char lhs[], const String& rhs){
  return (String(lhs) == rhs);
}
bool operator==(char lhs, const String& rhs){
  return (String(lhs) == rhs);
}

bool operator<(const char lhs[], const String& rhs){
  return (String(lhs) < rhs);
}

bool operator<(char lhs, const String& rhs){
  return (String(lhs) < rhs);
}

bool operator<=(const String& lhs, const String& rhs){
  return !(rhs < lhs);
}

bool operator!=(const String& lhs, const String& rhs){
  return !(lhs == rhs);
}

bool operator>=(const String& lhs, const String& rhs){
  return !(lhs < rhs);
}

bool operator>(const String& lhs, const String& rhs){
  return (rhs < lhs);
}
