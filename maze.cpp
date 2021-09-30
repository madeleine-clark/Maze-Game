#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// argc stores the count of how many arguments are passed via the command line
// PLUS one for the name of the program

// argv is an array of C-strings where each argument is stored in argv as a C-string

int main(int argc, char * argv[])
{
  /* Need a conditional to check num of argc
     so as to determine if it's meant to be
     user input mode or file input mode OR
     if they didn't enter a filename */

     string boardFile = argv[1]; // board file name is 2nd element of argv
                                 // (executable file is 1st element)

     ifstream inFS; // Create input stream for file
     vector<string> tempBoard; // Temporary vector to hold strings making up board file
     inFS.open(boardFile); // Open file
     if (!inFS.is_open()) { // Check that file opened successfully
       return 1;
     }



     // Construct 2-D array using input board file
     // Must first determine the dimensions


  return 0;
}
