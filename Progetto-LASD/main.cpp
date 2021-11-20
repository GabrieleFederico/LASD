
#include "zlasdtest/test.hpp"

#include "zmytest/test.hpp"

/* ************************************************************************** */

#include <iostream>

/* ************************************************************************** */

int main() {
  std::cout << "Lasd Libraries 2020" << std::endl;
  std::cout << "Choose the test:\n 1-Student tests\n 2-Professor tests\n 0-Esci" << std::endl;
  int choice = 1;

  while(choice){
    std::cin >> choice;
    switch(choice){
      
      case 1:
        myTest();
        return 0;
        break;

      case 2:
        lasdtest(); // To call in the menu of your library test!
        break;

      case 0:
        return 0;
        break;

      default:
        std::cout << "Invalid choice" << std::endl;
    }
  }
  
  return 0;
}
