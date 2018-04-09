//Project 1 - Lexer
#ifndef _LEXER_H_
#define _LEXER_H_
#include <iostream> 	//std::cout
#include <string>	//string::string, string::length(), 
#include <fstream>	//ofstrea::ofstream, ifstream::ifstream, open, close
#include <vector>	//for vector, vector::size()
#include <cctype>	//isdigit(), isalpha()
#include <iomanip>	//std::setw() 

using namespace std;

/*--------------------------Token class----------------------------------------------*/

class Lexer{
public:
	string variable;
	string state;
/*--------------------------Lexer cpp Methods----------------------------------------------*/
	void isGenerated();
	void print_list();
};
#endif
