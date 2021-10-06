#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Function declarations
void printCurrBoard(vector<vector<char>> currBoard, int numRows, int numColumns);
void buildBoard(vector<string> tempBoard, vector<vector<char>> &currBoard, int numRows, int numColumns, int &currR, int &currC);
void playUserInputMode(vector<vector<char>> currBoard, int numRows, int numColumns, int currR, int currC);
void playFileInputMode(string file2Name, vector<vector<char>> currBoard, int numRows, int numColumns, int currR, int currC);

int main(int argc, char * argv[]) {
  // Two possible modes: user input mode and file input mode
  bool userInputMode = false;

  // 1) Check number of command line arguments
  if (argc == 2) {
    userInputMode = true;
  }
  else if (argc != 3) {
    cerr << "Wrong number of arguments." << endl;
    return 1;
  }

  // 2) Open board file and temporarily store as vector array of strings
  vector<string> tempBoard;
  string currLine;

  string file1Name = argv[1];
  ifstream boardFile;

  boardFile.open(file1Name);

  if (!boardFile.is_open()) {
    cerr << "Could not open the board file." << endl;
    return 1;
  }

  while (getline(boardFile, currLine)) {
    tempBoard.push_back(currLine);
  }

  // 3) Build 2-D vector array of characters to represent the board
  int numRows = tempBoard.size();
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
    playFileInputMode(argv[2], currBoard, numRows, numColumns, currR, currC);
  }

  return 0;
}

void playFileInputMode(string file2Name, vector<vector<char>> currBoard, int numRows, int numColumns, int currR, int currC) {

  // Ending circumstances
  bool gameWon = false;
  bool hitWall = false;
  bool invalidInput = false;

  char currCommand;
  ifstream inputsFile;

  inputsFile.open(file2Name);

  if (!inputsFile.is_open()) {
    cerr << "Could not open the inputs file." << endl;
  }

  while (inputsFile >> currCommand) {
    int prevR;
    int prevC;

    switch (currCommand) {
      case 'a': // Move left
          if ((currC == 0) || (currBoard[currR][currC - 1] == '#')) { // Check that the player isn't in the leftmost column
            hitWall = true;
          }
          else {
            prevC = currC;
            currC = currC - 1;

            if (currBoard[currR][currC] == '$') {
              gameWon = true;
            }

            currBoard[currR][currC] = '@';
            currBoard[currR][prevC] = '.';
          }
          break;
      case 'w': // Move up
          if ((currR == 0) || (currBoard[currR - 1][currC] == '#')) { // Check that the player isn't in the first row
            hitWall = true;                         // and that the desired spot isn't a wall
          }
          else {
            prevR = currR;
            currR = currR - 1;

            if (currBoard[currR][currC] == '$') {
              gameWon = true;
            }

            currBoard[currR][currC] = '@';
            currBoard[prevR][currC] = '.';
          }
          break;
      case 'd': // Move right
          if ((currC == numColumns - 1) || (currBoard[currR][currC + 1] == '#')) { // Check that the player isn't in the rightmost column
            hitWall = true;                              // and that the desired spot isn't a wall
          }
          else {
            prevC = currC;
            currC = currC + 1;

            if (currBoard[currR][currC] == '$') {
              gameWon = true;
            }

            currBoard[currR][currC] = '@';
            currBoard[currR][prevC] = '.';
          }
          break;
      case 's': // Move down
          if ((currR == numRows - 1) || (currBoard[currR + 1][currC] == '#')) { // Check that the player isn't in the first row
            hitWall = true;                         // and that the desired spot isn't a wall
          }
          else {
            prevR = currR;
            currR = currR + 1;

            if (currBoard[currR][currC] == '$') {
              gameWon = true;
            }

            currBoard[currR][currC] = '@';
            currBoard[prevR][currC] = '.';
          }
          break;
      default:  // Invalid command
          invalidInput = true;
          break;
    }

    if (gameWon) {
      cout << "That input results in a victory." << endl;
      break;
    }
    else if (hitWall) {
      cout << "Hit wall." << endl;
      break;
    }
    else if (invalidInput) {
      cout << "Invalid input encountered in input sequence." << endl;
      break;
    }
  }

  if (!(gameWon) && !(hitWall) && !(invalidInput)) {
    cout << "That input does not reach the end." << endl;
  }
}

void playUserInputMode(vector<vector<char>> currBoard, int numRows, int numColumns, int currR, int currC) {
  bool gameDone = false;
  bool gameWon = false;

  while (!(gameDone) && !(gameWon)) {
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
            cout << "You can't move there." << endl; // and that the desired spot isn't a wall
          }
          else {
            prevC = currC;
            currC = currC - 1;

            if (currBoard[currR][currC] == '$') {
              gameWon = true;
            }

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

            if (currBoard[currR][currC] == '$') {
              gameWon = true;
            }

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

            if (currBoard[currR][currC] == '$') {
              gameWon = true;
            }

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

            if (currBoard[currR][currC] == '$') {
              gameWon = true;
            }

            currBoard[currR][currC] = '@';
            currBoard[prevR][currC] = '.';
          }
          break;
      case 'q': // Quit the game
          cout << "You quit the game." << endl;
          gameDone = true;
          break;
      default:  // Invalid command
          cout << "Invalid input." << endl;
          break;
    }

    if (gameWon) {
      printCurrBoard(currBoard, numRows, numColumns);
      cout << "You won the game." << endl;
    }
  }
}

void buildBoard(vector<string> tempBoard, vector<vector<char>> &currBoard, int numRows, int numColumns, int &currR, int &currC) { // currBoard, currR, and currC are all pass by reference
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

  for (int a = 0; a < numColumns + 2; ++a) {
    cout << "-";
  }

  cout << endl;

  for (int i = 0; i < numRows; ++i) {
    cout << "|";
    for (int j = 0; j < numColumns; ++j) {
      cout << currBoard[i][j];
    }
    cout << "|" << endl;
  }

  for (int b = 0; b < numColumns + 2; ++b) {
    cout << "-";
  }

  cout << endl;


}
