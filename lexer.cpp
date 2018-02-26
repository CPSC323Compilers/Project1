//Project 1 - Lexer

#include <iostream> 	//std::cout
#include <string>	//string::string, string::length(), 
#include <fstream>	//ofstrea::ofstream, ifstream::ifstream, open, close
#include <vector>	//for vector, vector::size()
#include <cctype>	//isdigit(), isalpha()
#include <iomanip>	//std::setw() 

using namespace std;

/*--------------------------Token struct----------------------------------------------*/
struct Token {
	string variable;
	string state;
};

/*-------------------------Function headers-------------------------------------------*/
void putVector(string original, string state, vector<Token>& tokens);		//A helper function to add element to vector
bool isIdentifier(string original, vector<Token>& tokens);			//Verifies if given word is valid identifier
bool isReal(string original, vector<Token>& tokens);				//Verifies if given word is valid real
bool isInteger(string original, vector<Token>& tokens);				//Verifies if given word is valid integer
bool isValid(string original, vector<Token>& tokens);
void print_list(const vector<Token>& tokens);					//Prints our list out to console and text file


/* ----------Const keywords, operators, and separators--------------------------------*/
const string keywords[] = { "while", "if", "else" };
const string operators[] = { "<", ">", "<=", ">=", "=", "+", "-", "+=", "-=", "*", "/", "*=", "/=" };
const string separators[] = { "(", ")", "{", "}", "[", "]", "," };


/*-----------------------------------Start of main------------------------------------*/
int main(int argc, char** argv) {
  ifstream fs("test1.txt");	//Open file
  //Check that the file is open
  if(!fs.is_open()) {
    cout << "Could not find file. Aborting." << std::endl;
    return -1;
  }
  
  vector<Token> tokens;
  // read until white space, save string into temp
  while(!fs.eof()) {
	  string temp;
	  fs >> temp;
	  isValid(temp, tokens);
  }
  fs.close();
  print_list(tokens);
  return 0;
}
/*-----------------------------------End of main------------------------------------*/

/*------------------------------print function--------------------------------------*/
void print_list(const vector<Token>& tokens) {
	
	const int space = 20;
	filebuf fb;
	fb.open("Tokens.txt", ios::out);
	ostream os(&fb);
	
	cout << " === State ===" << setw(space) << "=== Token ===\n";
	os << " === State ===" << setw(space) << "=== Token ===\n";
	 
	for(int i = 0; i < tokens.size(); i++) {
		int indent = space - tokens[i].state.length();
		cout << right << tokens[i].state << left << setw(indent) << " " << tokens[i].variable << endl;
		os << right << tokens[i].state << left << setw(indent) << " " << tokens[i].variable << endl;
	}
	fb.close();
}

bool isIdentifier(string original, vector<Token>& tokens) {
	for(int i = 0; i < original.length(); i++) {
		// condition checks the strings first character, meets condition if first character is not a digit
		
		//Checks to make sure that the word does not have a symbol in the middle
		if(i != original.length()-1) {
			if(!isalpha(original[i]) && !isdigit(original[i])) { 
				cout << original << " contains a non-alphabet or non-digit.\n";
				return false;
			} 
		}
		
		//Checks the last character of the word to make sure that it ends in either an letter or $
		else {
			if(!isalpha(original[i]) && original[i] != '$') {
				cout << original << " does not end with either an alphabet or a '$'. \n";
				return false;
			}
		}
	}
	
	putVector(original, "Identifier", tokens);
	return true;
}

bool isReal(string original, vector<Token>& tokens) {
	//There must be exactly one dot. Integers must both precede and follow the dot.
	int dotcount = 0;
	
	for(int i = 0; i < original.length(); i++) {
		if(!isdigit(original[i])) {
			if(original[i] == '.') {
				dotcount++;
			}
			else {
				cout << original << " has something other than a dot or digit\n";
				return false;
			}
		}
		if(dotcount == 2) {
			cout << original << " has too many dots for this to be real..." << endl;
			return false;
		}
	}
	
	putVector(original, "Real", tokens);
	return true;
}

bool isInteger(string original, vector<Token>& tokens) {
	for(int i = 0; i < original.length(); i++) {
		if(!isdigit(original[i]) && original[i] != '.') {
			return false;
		}
		else if(original[i] == '.') {
			cout << "Integer found a dot. Testing if it's a real.\n";
			if(isReal(original, tokens)) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	
	putVector(original, "Integer", tokens);
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

bool isValid(string original, vector<Token>& tokens) {
	if(isalpha(original[0])) {
		if(isIdentifier(original, tokens)) {
			//Check if the word is a keyword
			if(isKeyword(original)) {
				tokens.back().state = "Keyword";
			}
			return true;
		}
	}
	else if(isdigit(original[0])) {
		if(isInteger(original, tokens)) {
			return true;
		}
	}
	return false;
}

/*-------------Helper function to pushback to our token vector--------------------*/
void putVector(string var, string state, vector<Token>& tokens) {
	Token token;
	token.variable = var;
	token.state = state;
	tokens.push_back(token);
}
