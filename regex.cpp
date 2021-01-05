#include <iostream>
#include <string>
#include <fstream>
#include "Functions.h"

int main() {
  std::fstream MyFile;
  std::string Regex, Line, FileName;
  char letter, multiplier;
  int special_pos = 0;
  std::cout << "The regular expression you want to find is: ";
  do {
      std::getline(std::cin, Regex);
  }
  while (defense(Regex) != true);
  std::cout << "The File you want to read from is: ";
  std::cin >> FileName;

  Solution(Regex, FileName);

  return 0;
}
