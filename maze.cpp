#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Function prototypes
void printCurrBoard(vector<vector<char>> currBoard, int numRows, int numColumns);
void buildBoard(vector<string> tempBoard, vector<vector<char>> &currBoard, int numRows, int numColumns, int &currR, int &currC);
void playUserInputMode(vector<vector<char>> currBoard, int numRows, int numColumns, int currR, int currC);

int main(int argc, char * argv[]) {
  // Two possible modes: user input mode and file input mode
  bool userInputMode = false;

  // 1) Check number of command line arguments
  if (argc == 2) {
    userInputMode = true;
  }
  else if (argc != 3) {
    cerr << "Wrong number of arguments." << endl;
    return 1; // ?CAN I HAVE MULTIPLE RETURN STATEMENTS IN MAIN?
  }

  // 2) Open and process board text file
  vector<string> tempBoard;
  string currLine;

  string file1Name = argv[1]; // Board file name is 2nd element of argv
  ifstream boardFile; // Input stream for board file

  boardFile.open(file1Name); // Open board file

  if (!boardFile.is_open()) { // Check that  board file opened correctly
    cerr << "Could not open the board file." << endl;
    return 1;
  }

  while (!boardFile.fail()) { // ?CONFUSED ABOUT DIFFERENCE BTW .fail(), ,eof(), etc.?
    getline(boardFile, currLine);
    tempBoard.push_back(currLine);
  }

  // 3) Build 2-D vector array to store board
  int numRows = tempBoard.size() - 1; // ?WHY IS NUMROWS OVER BY 1?
  int numColumns = tempBoard.at(0).size();
  int currR;
  int currC;
  vector<vector<char>> currBoard;
  buildBoard(tempBoard, currBoard, numRows, numColumns, currR, currC);

  // 4) Begin game in the correct mode
  if (userInputMode) {
    playUserInputMode(currBoard, numRows, numColumns, currR, currC);
  }
  else {
    // NEED TO WRITE CODE FOR INPUT FILE MODE
    cout << "Need to write code for file input mode." << endl;
  }

  return 0;
}

void playUserInputMode(vector<vector<char>> currBoard, int numRows, int numColumns, int currR, int currC) {
  bool gameDone = false;

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
    // NEED TO ADD WHAT HAPPENDS WHEN THEY WIN
    switch (userMove) {
      case 'a': // Move left
          if ((currC == 0) || (currBoard[currR][currC - 1] == '#')) { // Check that the player isn't in the leftmost column
            cout << "You can't move there."; // and that the desired spot isn't a wall
          }
          else {
            prevC = currC;
            currC = currC - 1;
            currBoard[currR][currC] = '@';
            currBoard[currR][prevC] = '.';
          }
          break;
      case 'w': // Move up
          if ((currR == 0) || (currBoard[currR - 1][currC] == '#')) { // Check that the player isn't in the first row
            cout << "You can't move there." << endl;;                         // and that the desired spot isn't a wall
          }
          else {
            prevR = currR;
            currR = currR - 1;
            currBoard[currR][currC] = '@';
            currBoard[prevR][currC] = '.';
          }
          break;
      case 'd': // Move right
          if ((currC == numColumns - 1) || (currBoard[currR][currC + 1] == '#')) { // Check that the player isn't in the rightmost column
            cout << "You can't move there." << endl;                               // and that the desired spot isn't a wall
          }
          else {
            prevC = currC;
            currC = currC + 1;
            currBoard[currR][currC] = '@';
            currBoard[currR][prevC] = '.';
          }
          break;
      case 's': // Move down
          if ((currR == numRows - 1) || (currBoard[currR + 1][currC] == '#')) { // Check that the player isn't in the first row
            cout << "You can't move there." << endl;                         // and that the desired spot isn't a wall
          }
          else {
            prevR = currR;
            currR = currR + 1;
            currBoard[currR][currC] = '@';
            currBoard[prevR][currC] = '.';
          }
          break;
      case 'q': // Quit the game
          cout << "Game quit." << endl;
          gameDone = true;
          break;
      default:  // Invalid command
          cout << "Not a valid command.";
          break;
    }
  }
}

void buildBoard(vector<string> tempBoard, vector<vector<char>> &currBoard, int numRows, int numColumns, int &currR, int &currC) {
  currBoard.resize(numRows, vector<char>(numColumns, '.'));

  for (int i = 0; i < numRows; ++i) {
    string rowString = tempBoard.at(i);
    for (int j = 0; j < numColumns; ++j) {
      currBoard[i][j] = rowString.at(j);
      if (rowString.at(j) == '@') { // Determine starting position in vector array
        currR = i;
        currC = j;
      }
    }
  }
}

void printCurrBoard(vector<vector<char>> currBoard, int numRows, int numColumns) { // NEED TO PRINT OUT BORDERS STILL
  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numColumns; ++j) {
      cout << currBoard[i][j];
    }
    cout << endl;
  }
}
