//Johnson Lien
//CPSC323 Project 1 - Lexer
#include <stdio.h>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>

//identifier - starts with letter, can end with 
//real - integer followed by a "." and integer
//integer - sequence of decimal digits

//const std::string keywords[] = {"if", "else", "while", "for"};
//const std::string separators[] = {'{', '}', '[', ']', '(', ')'}

using namespace std;

bool isValid(string original, vector<string>& variable, vector<string>& state);
void print_list(const vector<string>& variable, const vector<string>& state);

int main(int argc, char** argv) {
  char filename[256];
  //std::cout << "Enter the name of the file you want to parse." << std::endl;
  //std::cin.get(filename,256);
  
  std::ifstream fs("test1.txt");	//Open file
  
  //Check that the file is open
  if(!fs.is_open()) {
    std::cout << "Could not find file. Aborting." << std::endl;
    return -1;
  }
  
  vector<string> variable;
  vector<string> state;
  
  while(!fs.eof()) {
	  string temp;
	  fs >> temp;
	  if(isValid(temp, variable, state)) {
		  
	  }
  }
  fs.close();
  
  print_list(variable, state);
  
  return 0;
}

void print_list(const vector<string>& variable, const vector<string>& state) {
	cout << " === Token === \t=== State ===\n";
	for(int i = 0; i < variable.size(); i++) {
	  cout << variable[i] << "\t\t" << state[i] << endl;
	}
}

bool isIdentifier(string temp, vector<string>& variable, vector<string>& state) {
	for(int i = 0; i < temp.length(); i++) {
		//If our string is does not contain either a digit or letter, we must be
		// at the end of our string AND the last char is either a letter or $
		if(!isalpha(temp[i]) && !isdigit(temp[i])) {
			if(temp[temp.length()-1] != '$' && !isalpha(temp[temp.length()-1])) {
				cout << temp << " is not a valid identifier." << endl;
				return false;
			}
		}
	}
	variable.push_back(temp);
	state.push_back("Identifier");
	return true;
}

bool isReal(string temp, vector<string>& variable, vector<string>& state) {
	//There must be exactly one dot. Integers must both precede and follow the dot.
	int dotcount = 0;
	
	for(int i = 0; i < temp.length(); i++) {
		if(!isdigit(temp[i])) {
			if(temp[i] == '.') {
				dotcount++;
			}
			else {
				cout << "Found something other than a dot or digit\n";
				return false;
			}
		}
		if(dotcount == 2) {
			cout << "Too many dots for this to be real..." << endl;
			return false;
		}
	}
	
	variable.push_back(temp);
	state.push_back("Real");
	return true;
}

bool isInteger(string temp, vector<string>& variable, vector<string>& state) {
	for(int i = 0; i < temp.length(); i++) {
		if(!isdigit(temp[i]) && temp[i] != '.') {
			return false;
		}
		else if(temp[i] == '.') {
			cout << "Integer found a dot. Testing if it's a real.\n";
			if(isReal(temp, variable, state)) {
				return true;
			}
			else {
				cout << temp << " was tested as a real and did not pass. " << endl;
				return false;
			}
		}
	}
	
	variable.push_back(temp);
	state.push_back("Integer");
	return true;
}

bool isValid(string original, vector<string>& variable, vector<string>& state) {
	if(isalpha(original[0])) {
		if(isIdentifier(original, variable, state)) {
			return true;
		}
	}
	else if(isdigit(original[0])) {
		if(isInteger(original, variable, state)) {
			return true;
		}
	}
	return false;
}
