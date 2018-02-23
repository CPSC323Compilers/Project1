#include <cctype>   //isalpha(), isdigit() 
#include <iostream> //cout
#include <string>   //string
#include <fstream>  //file stream

using namespace std;

int main(int argc, char** argv) {
  
  char filename[256];
  
  ifstream fs("test1.txt");   //Open file
  
  //Fheck that the file is open
  if(!fs.is_open()) {
    cout << "Could not find file. Aborting." << endl; 
    return -1;
  }
  
  while(!fs.eof()) {
    string temp;
    fs >> temp;
    if(isValid(temp)) {
      
    }
  }
  
  fs.close();
  return 0;
}
