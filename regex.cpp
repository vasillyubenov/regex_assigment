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
      std::getline(std::cin,Regex);
  }
  while (defense(Regex) != true);
  std::cout << "The File you want to read from is: ";
  std::cin >> FileName;
  MyFile.open(FileName,std::fstream::in);
  if (!MyFile.good()) {
    std::cout << "File could not open properly!";
    return -1;
  }
  special_pos = Special_Symbol(Regex, multiplier);
  if (special_pos == 0)//there is no special symbol
  {
      while (getline(MyFile, Line))
	  {
          if (Min_regex_Size(Regex) <= Size(Line) && basic_search(Line, Regex) == true)
		        std::cout << Line << "\n";
	  }
  }
  else {
      letter = Regex[special_pos - 1];
	  //eraseing the special symbol and the one whose amouth varies and the one before if if it is an escpaed symbol
	  if (letter == '\\' || letter == '\?' || letter == '\+' || letter == '\*' || letter == '\.' || letter == '\^') {
		  Regex.erase(special_pos - 1, 3);
	  }
	  //eraseing the special symbol and the one whose amouth varies
	  else {
		  Regex.erase(special_pos - 1, 2);
	  }
	  std::string buffer, tmp_Regex;
      while (getline(MyFile, Line)) {
	      tmp_Regex = Regex;
		  buffer = "";
          if (Min_regex_Size(tmp_Regex) <= Size(Line)) {
              switch (multiplier) {
    	          case '\?': {
                      int max = 1;
    	              if (Max_Amounth(Line, letter) >= 1) max = 2;//the times we want the loop to be done
                      for (int quantity = 0; quantity < max; quantity++) {
                          tmp_Regex.insert(special_pos - 1, buffer);
                          if (basic_search(Line, tmp_Regex) == true) {
    			              std::cout << Line<<"\n";
    				          break;
    				      }
    				      buffer += letter;
    			      }
    			      break;
    		      }
    		      case '\*': {
    		          int max = Max_Amounth(Line, letter);
    			      for (int quantity = 0; quantity <= max; quantity++) {
    	                  tmp_Regex.insert(special_pos - 1, buffer);
    			          if (basic_search(Line, tmp_Regex) == true) {
    			              std::cout << Line << "\n";
    				          break;
    			          }
    		              buffer += letter;
    			      }
    			      break;
    		     }
    		      case '\+': {
                      buffer += letter;
        		      int max = Max_Amounth(Line, letter);
    			      for (int quantity = 1; quantity <= max; quantity++) {
    				      tmp_Regex.insert(special_pos - 1, buffer);
    				      if (basic_search(Line, tmp_Regex) == true) {
    				          std::cout << Line << "\n";
    					      break;
    				      }
    				      buffer += letter;
    		          }
    			      break;
    			  }
              }
	      }
	  }
  }
  return 0;
}
