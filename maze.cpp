#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Function prototypes
void printCurrBoard(vector<vector<char>> currBoard, int numRows, int numColumns);

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
     int numRows = tempBoard.size() - 1; // Need to subtract 1 for some reason; something wrong with file reading

     int numColumns = tempBoard.at(0).length();

     // Construct 2-D vector array using tempBoard
     vector<vector<char>> currBoard;

     currBoard.resize(numRows, vector<char>(numColumns, '.'));
     int currR;
     int currC;
     bool gameDone = false;

     for (int i = 0; i < numRows; ++i) { // I want to be able to do this in a function
       string rowString = tempBoard.at(i); // But I was having difficulties passing the 2-D vector by reference
       for (int j = 0; j < numColumns; ++j) {
         currBoard[i][j] = rowString.at(j);
         if (rowString.at(j) == '@') { // Determine starting position in vector array
           currR = i;
           currC = j;
         }
       }
     }

     // USER INPUT
     while (!(gameDone)) {

       // Variables
       int prevR;
       int prevC;

       // 1) Display current board
       printCurrBoard(currBoard, numRows, numColumns);

       // 2) Get user's directional command
       char userMove;
       cout << "> ";
       cin >> userMove;

       // 3) Process move
       if (userMove == 'a') { // Move left
         if ((currC == 0) || (currBoard[currR][currC - 1] == '#')) { // Check that the player isn't in the leftmost column
           cout << "You can't move there.";                         // and that the desired spot isn't a wall
         }
         else {
           prevC = currC;
           currC = currC - 1;
           currBoard[currR][currC] = '@';
           currBoard[currR][prevC] = '.';
         }
       }
       else if (userMove == 'w') { // Move up
         if ((currR == 0) || (currBoard[currR - 1][currC] == '#')) { // Check that the player isn't in the first row
           cout << "You can't move there." << endl;;                         // and that the desired spot isn't a wall
         }
         else {
           prevR = currR;
           currR = currR - 1;
           currBoard[currR][currC] = '@';
           currBoard[prevR][currC] = '.';
         }
       }
       else if (userMove == 'd') { // Move right
         if ((currC == numColumns - 1) || (currBoard[currR][currC + 1] == '#')) { // Check that the player isn't in the rightmost column
           cout << "You can't move there." << endl;;                               // and that the desired spot isn't a wall
         }
         else {
           prevC = currC;
           currC = currC + 1;
           currBoard[currR][currC] = '@';
           currBoard[currR][prevC] = '.';
         }
       }
       else if (userMove == 's') { // Move down
         if ((currR == numRows - 1) || (currBoard[currR + 1][currC] == '#')) { // Check that the player isn't in the first row
           cout << "You can't move there." << endl;                         // and that the desired spot isn't a wall
         }
         else {
           prevR = currR;
           currR = currR + 1;
           currBoard[currR][currC] = '@';
           currBoard[prevR][currC] = '.';
         }
       }
       else if (userMove == 'q') { // Quit the game
         cout << "Game quit." << endl;
         gameDone = true;
       }
       else {
         cout << "Not a valid command.";
       }

     }

  return 0;
}

void printCurrBoard(vector<vector<char>> currBoard, int numRows, int numColumns) {
  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numColumns; ++j) {
      cout << currBoard[i][j];
    }
    cout << endl;
  }
}
