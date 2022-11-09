// Tests Character Array Constructor for String class

#include "string.hpp"
#include <cassert>
#include <iostream>

int main() {
  {
    // TEST                                                                                    
    String str("10");

    // VERIFY                                                                                  
    assert(str[0] == '1');
    assert(str[1] == '0');
    assert(str[2] == '\0');
  }

  {
    // TEST
    
    String str("This is my string!");
    
    // VERIFY

    assert (str == "This is my string!");
  }

  {
    // TEST                                                                     

    String str("1234567890!@#$%^&*()");

    // VERIFY                                                                   

    assert (str == "1234567890!@#$%^&*()");
  }

  {
    // TEST                                                                                                                                                 

    String str("I'm currenty testing the string constructor.");

    // VERIFY                                                                  
                                                                          
    assert (str == "I'm currenty testing the string constructor.");
  }

  {
    // TEST

    String str("                                                                                ");

    // VERIFY

    assert (str == "                                                                                ");
  }

  std::cout << "Done testing character array constructor." << std::endl;
}
