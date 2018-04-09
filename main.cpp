
#include <iostream> 	//std::cout
#include <string>	//string::string, string::length(), 
#include <fstream>	//ofstrea::ofstream, ifstream::ifstream, open, close
#include <vector>	//for vector, vector::size()
#include <cctype>	//isdigit(), isalpha()
#include <iomanip>	//std::setw() 
#include "lexer.h"

using namespace std;


int main(){
	Lexer lexer;
	lexer.isGenerated();
	return 0;
}