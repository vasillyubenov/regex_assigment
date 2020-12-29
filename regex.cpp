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
int Min_regex_Size(const std::string Regex) {
	int counter = 0;
	for (int i = 0; i < Size(Regex); i++)
	{
		if (Regex[i] == '\\') counter++;
	}
	return Size(Regex) - counter;
}
//seach through the Regex if the is one of the special symbols like (?,* and +)
int Special_Symbol (const std::string Regex, char &special) {
  for(int i=1;i<Size(Regex);i++) {
    if(Regex[i]=='\*' || Regex[i]=='\?' || Regex[i]=='\+' && Regex[i-1]!='\\') {
      special=Regex[i];
      return i;
    }
  }
  return 0;
}
bool basic_search(const std::string Line, const std::string Regex){
  bool match = false;
  for (size_t line_pos = 0; line_pos <= Size(Line) - Min_regex_Size(Regex); line_pos++) {
    int curr_line = line_pos;
    match = false;
    for (size_t curr_reg = 0; curr_reg < Min_regex_Size(Regex); curr_reg++) {
      switch(Regex[curr_reg]){
        case '\\':{
          if(curr_reg == Size(Regex) - 1 ) {
            //std::cout<<"Missuese of the \'\\\' symbol!"
          return false;
          }
          char next = Regex[curr_reg + 1];
          if (next!='\\' && next !='\+' && next != '\*' && next != '\?' && next !='\^' && next!='\.') {
            //std::cout<<"Missuese of the \'\\\' symbol!"
            return false;
          }
          if (next==Line[curr_line]) {
            match = true;
            curr_line++;
            curr_reg++;
          }
          else {
            match = false;
            break;
          }
          break;
        }

        case '\^': {
          if (curr_reg!=0) {
            return false;
          }
          match = true;
        }

        case '\.': {
          if (curr_reg > Size(Line) - 1){
            break;
          }
          curr_line++;
          match = true;
          break;
        }

        default : {
          if (Regex[curr_reg]==Line[curr_line]){
             curr_line++;
             match = true;
          }
          else {
            match = false;
            break;
          }
        }
      }
  if (match == true && curr_reg == Size(Regex) - 1) return true;
  if (match == false) break;
    }
  }
return false;
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
    std::cout<<"File could not open properly!";
    return -1;
  }
  while(getline(MyFile,Line))
  {
    if(basic_search(Line, Regex)==true) std::cout<<Line<<"\n";
  }
  return 0;
}
