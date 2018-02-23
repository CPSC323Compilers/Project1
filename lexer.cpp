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
  
  cout << " === Token === \t=== State ===\n";
  for(int i = 0; i < variable.size(); i++) {
	  cout << variable[i] << "\t\t" << state[i] << endl;
  }
  
  return 0;
}

bool isIdentifier(string temp, vector<string>& variable, vector<string>& state) {
	for(int i = 0; i < temp.length(); i++) {
		//If our string is does not contain either a digit or letter, we must be
		// at the end of our string AND the last char is either a letter or $
		if(!isalpha(temp[i]) && !isdigit(temp[i])) {
			if(temp[temp.length()-1] != '$' && !isalpha(temp[temp.length()-1])) {
				cout << "End of string is: " << temp[temp.length()-1] << endl;
				cout << "NOT VALID IDENTIFIER\n";
				return false;
			}
		}
	}
	cout << "Pushing back word" << endl;
	variable.push_back(temp);
	state.push_back("identifier");
	return true;
}

/*
bool isReal(string temp) {
	return false;
}

bool isInteger(string temp) {
	return false;
}
*/

bool isValid(string original, vector<string>& variable, vector<string>& state) {
	if(isalpha(original[0])) {
		cout << "Is identifier " << endl;
		isIdentifier(original, variable, state);
	}
}
