//Vasil Lyubenov course assigment
#include <iostream>
#include <fstream>
#include <string>
int Size(const std::string Line)
{
  int counter=0;
  while(Line[counter]!='\0'){
    counter++;
  }
  return counter;
}
int main(){
  std::fstream MyFile;
  std::string Regex, Line, FileName;
  std::cout<<"The File you want to read from is: ";
  std::cin>>FileName;
  std::cout<<"The regular expression you want to find is: ";
  std::cin>>Regex;
  MyFile.open(FileName,std::fstream::in);
  if(!MyFile.good()) {
    std::cout<<"File was not found!";
    return -1;
  }
  while(getline(MyFile,Line))
  {
    std::cout<<Line;
  }
  return 0;
}
