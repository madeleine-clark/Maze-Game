#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Function prototypes
void printCurrBoard(char currBoard[], int numRows, int numColumns);
void transform2DArray(vector<string> tempBoard, char& currBoard, int numRows, int numColumns);


int main(int argc, char * argv[])
{
  /* Need a conditional to check num of argc
     so as to determine if it's meant to be
     user input mode or file input mode OR
     if they didn't enter a filename */

     string fileName = argv[1]; // board file name is 2nd element of argv

     // cout << "File name is: " << fileName << endl;

     ifstream boardFile; // Create input stream for file
     vector<string> tempBoard; // Temporary vector to hold strings making up board file
     string currRow;
     boardFile.open(fileName); // Open file
     if (!boardFile.is_open()) { // Check that file opened correctly
       cout << "Encountered an error opening the board file" << endl;
       return 1;
     }
     while (!boardFile.fail()) { // Read in boardFile line by line and store each string line in tempBoard
       getline(boardFile, currRow);
       tempBoard.push_back(currRow);
     }

     // Determine # of rows and # of columns of input board
     int numRows = tempBoard.size();
     int numColumns = tempBoard.at(0).length();

     // Construct 2-D character array using tempBoard
     char currBoard[numRows][numColumns];
     transform2DArray(tempBoard, currBoard, numRows, numColumns);
     printCurrBoard(currBoard, numRows, numColumns);

  return 0;
}

void printCurrBoard(char currBoard[], int numRows, int numColumns) {
  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numColumns; ++j) {
      cout << currBoard[i][j];
    }
    cout << endl;
  }
}

void transform2DArray(vector<string> tempBoard, char& currBoard, int numRows, int numColumns) {
  for (int i = 0; i < numRows; ++i) {
    string rowString = tempBoard.at(0);
    for (int j = 0; j < numColumns; ++j) {
      currBoard[i][j] = rowString.at(j);
    }
  }
}
