//Project 1 - Lexer

#include <iostream> //std::cout
#include <string>	//string::string, string::length(), 
#include <fstream>	//ofstrea::ofstream, ifstream::ifstream, open, close
#include <vector>	//for vector, vector::size()
#include <cctype>	//isdigit(), isalpha()
#include <iomanip>	//std::setw() 

using namespace std;

//Function headers
bool isIdentifier(string temp, vector<string>& variable, vector<string>& state);
bool isReal(string temp, vector<string>& variable, vector<string>& state);
bool isInteger(string temp, vector<string>& variable, vector<string>& state);
bool isValid(string original, vector<string>& variable, vector<string>& state);
void print_list(const vector<string>& variable, const vector<string>& state);

//Keywords
const string keywords[] = { "while", "if", "else" };

/*-----------------------------------Start of main------------------------------------*/
int main(int argc, char** argv) {
  ifstream fs("test1.txt");	//Open file
  //Check that the file is open
  if(!fs.is_open()) {
    cout << "Could not find file. Aborting." << std::endl;
    return -1;
  }
  vector<string> variable;
  vector<string> state;
  // read until white space, save string into temp
  while(!fs.eof()) {
	  string temp;
	  fs >> temp;
	  isValid(temp, variable, state);
  }
  fs.close();
  print_list(variable, state);
  return 0;
}
/*-----------------------------------End of main------------------------------------*/

/*------------------------------print function--------------------------------------*/
void print_list(const vector<string>& variable, const vector<string>& state) {
	
	const int space = 20;
	filebuf fb;
	fb.open("Tokens.txt", ios::out);
	ostream os(&fb);
	
	cout << " === Token ===" << setw(space) << "=== State ===\n";
	os << " === Token ===" << setw(space) << "=== State ===\n";
	 
	for(int i = 0; i < variable.size(); i++) {
		int indent = space - state[i].length();
		cout << right << state[i] << left << setw(indent) << " " << variable[i] << endl;
		os << right << state[i] << left << setw(indent) << " " << variable[i] << endl;
	}
	fb.close();
}

bool isIdentifier(string temp, vector<string>& variable, vector<string>& state) {
	for(int i = 0; i < temp.length(); i++) {
		// condition checks the strings first character, meets condition if first character is not a digit
		
		//Checks to make sure that the word does not have a symbol in the middle
		if(i != temp.length()-1) {
			if(!isalpha(temp[i]) && !isdigit(temp[i])) { 
				cout << temp << " contains a non-alphabet or non-digit.\n";
				return false;
			} 
		}
		
		//Checks the last character of the word to make sure that it ends in either an letter or $
		else {
			if(!isalpha(temp[i]) && temp[i] != '$') {
				cout << temp << " does not end with either an alphabet or a '$'. \n";
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
				cout << temp << " has something other than a dot or digit\n";
				return false;
			}
		}
		if(dotcount == 2) {
			cout << temp << " has too many dots for this to be real..." << endl;
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
				return false;
			}
		}
	}
	
	variable.push_back(temp);
	state.push_back("Integer");
	return true;
}

bool isKeyword(string original) {
	for(int i = 0; i < 3; i++) {
		if(original == keywords[i]) {
			return true;
		}
	}
	return false;
}

bool isValid(string original, vector<string>& variable, vector<string>& state) {
	if(isalpha(original[0])) {
		if(isIdentifier(original, variable, state)) {
			//Check if the word is a keyword
			if(isKeyword(original)) {
				state.back() = "Keyword";
			}
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
