#include "Functions.h"

int Size(const std::string &Line)
{
	int counter = 0;
	while (Line[counter] != '\0') {
		counter++;
	}
	return counter;
}
int Min_regex_Size(const std::string &Regex) {
	int counter = 0;
	for (int i = 0; i < Size(Regex); i++) {
		if (Regex[i] == '\\') counter++;
	}
	return Size(Regex) - counter;
}

//seach through the Regex if the is one of the special symbols like (?,* or +)
int Special_Symbol(const std::string &Regex, char &special) {
	for (int i = 1; i < Size(Regex); i++) {
		if (Regex[i] == '*' || Regex[i] == '\?' || Regex[i] == '+') {
			if (Regex[i - 1] != '\\') {
				special = Regex[i];
				return i;
			}
		}
	}
	return 0;
}

//after we know what the multiplying symbol is we want to find what is the maximum amounth of times we have it in the line
int Max_Amounth(const std::string &Line, const char letter) {
	int max = 0, tmp = 0;
	for (int i = 0; i < Size(Line); i++) {
		tmp = 0;
		for (int j = i; j < Size(Line); j++) {
			if (Line[j] == letter) tmp++;
			else break;
		}
		if (tmp > max) max = tmp;
	}
	return max;
}

bool basic_search(const std::string &Line, const std::string &Regex) {
	bool match = false, start_line = false;
	if (Min_regex_Size(Regex) > Size(Line)) return false;
	for (int line_pos = 0; line_pos <= Size(Line) - Min_regex_Size(Regex); line_pos++) {
		int curr_line = line_pos;
		match = false;
		for (int curr_reg = 0; curr_reg < Min_regex_Size(Regex); curr_reg++) {
			switch (Regex[curr_reg]) {
				case '\\': {
					if (curr_reg == Size(Regex) - 1) {
						return false;
					}
					char next = Regex[curr_reg + 1];
					if (next != '\\' && next != '+' && next != '*' && next != '\?' && next != '^' && next != '.') {
						return false;
					}
					if (next == Line[curr_line]) {
						match = true;
						curr_line++;
						curr_reg++;
					}
					else if (start_line == true) {
						return false;
					}
					else {
						match = false;
						break;
					}
					break;
				}
				case '^': {
					if (curr_reg != 0) {
						return false;
					}

					start_line = true;

					if (Regex == "^") {
						return true;
					}
					match = true;
					break;
				}
				case '.': {
					if (curr_reg > Size(Line) - 1) {
						break;
					}
					curr_line++;
					match = true;
					break;
				}
				default: {
					if (Regex[curr_reg] == Line[curr_line]) {
						curr_line++;
						match = true;
					}
					else {
						if (start_line == true) {
							return false;
						}
						match = false;
						break;
					}
				}
			}
			if (match == true && curr_reg == Size(Regex) - 1) {
				return true;
			}
			if (match == false) {
				break;
			}
		}
	}
	return false;
}

bool defense(const std::string &Regex) {
	if (Size(Regex) == 0) {
		return false;
	}
	if (Regex[0] == '+' || Regex[0] == '*' || Regex[0] == '\?' || Regex == "\\") {
		return false;
	}
	if (Regex[Size(Regex) - 1] == '\\') {
		return false;
	}

	int special = 0;

	for (int i = 1; i < Size(Regex); i++) {
		if ((Regex[i] == '*' || Regex[i] == '+' || Regex[i] == '\?') && Regex[i - 1] != '\\') {
			special++;
		}
	}
	if (special >= 2) {
		return false;
	}
	//if there are two or more consecutive multipliers
	for (int i = 1; i < Size(Regex) - 1; i++) {
		if ((Regex[i] == '*' || Regex[i] == '+' || Regex[i] == '\?' || Regex[i] == '.') && Regex[i - 1] != '\\') {
			if (Regex[i + 1] == '*' || Regex[i + 1] == '+' || Regex[i + 1] == '\?' || Regex[i + 1] == '.') {
				return false;
			}
		}
	}

	return true;
}

void Solution(std::string Regex, const std::string &FileName) {
	std::fstream MyFile;
	std::string Line;
	char letter, multiplier;
	int special_pos = 0;

	MyFile.open(FileName, std::fstream::in);

	if (!MyFile.good()) {
		std::cout << "File could not open properly!";
		return;
	}

	special_pos = Special_Symbol(Regex, multiplier);

	//there is no special symbol
	if (special_pos == 0) {
		while (getline(MyFile, Line)) {
			if (Min_regex_Size(Regex) <= Size(Line) && basic_search(Line, Regex) == true) {
				std::cout << Line << "\n";
			}
		}
	}
	else {
		int start_erase_index = special_pos - 1;
		letter = Regex[start_erase_index];

		//eraseing the special symbol and the one whose amouth varies and the one before if if it is an escpaed symbol
		if (letter == '\\' || letter == '\?' || letter == '+' || letter == '*' || letter == '.' || letter == '^') {
			start_erase_index -= 1;
			Regex.erase(start_erase_index, 3);
		}
		//eraseing the special symbol and the one whose amouth varies
		else {
			Regex.erase(start_erase_index, 2);
		}

		std::string buffer = "", tmp_Regex;
		//we will insert the buffer in the erased spaces (depending on the multiplying symbol)
		buffer += letter;

		while (getline(MyFile, Line)) {
			tmp_Regex = Regex;
			if (Min_regex_Size(tmp_Regex) <= Size(Line)) {
				switch (multiplier) {
					case '\?': {
						int max = 1;
						if (Max_Amounth(Line, letter) >= 1) max = 2;

						if (tmp_Regex == "") {
							std::cout << Line << "\n";
							break;
						}
						for (int quantity = 0; quantity < max; quantity++) {
							if (basic_search(Line, tmp_Regex) == true) {
								std::cout << Line << "\n";
								break;
							}
							tmp_Regex.insert(start_erase_index, buffer);
						}
						if (tmp_Regex == "") std::cout << Line << "\n";
						break;
					}
					case '*': {
						int max = Max_Amounth(Line, letter);

						if (tmp_Regex == "") {
							std::cout << Line << "\n";
							break;
						}
						for (int quantity = 0; quantity <= max; quantity++) {
							if (basic_search(Line, tmp_Regex) == true) {
								std::cout << Line << "\n";
								break;
							}
							else {
								tmp_Regex.insert(start_erase_index, buffer);
							}
						}
						break;
					}
					case '+': {
						int max = Max_Amounth(Line, letter);
						for (int quantity = 1; quantity <= max; quantity++) {
							tmp_Regex.insert(start_erase_index, buffer);
							if (basic_search(Line, tmp_Regex) == true) {
								std::cout << Line << "\n";
								break;
							}
						}
						break;
					}
				}
			}
		}
	}
	MyFile.close();
}