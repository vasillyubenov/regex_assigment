#pragma once 

#include <iostream>
#include <string>
#include <fstream>

int Size(const std::string Line);

int Min_regex_Size(const std::string Regex);

int Special_Symbol(const std::string Regex, char &special);

int Max_Amounth(const std::string Line, const char letter);

bool basic_search(const std::string Line, const std::string Regex);

bool defense(const std::string Regex);

void Solution(std::string Regex, const std::string FileName);