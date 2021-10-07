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
void processMove(vector<vector<char>> &currBoard, char currCommand, int numRows, int numColumns, int &currR, int &currC, int &prevR, int &prevC, bool &gameWon, bool &hitWall, bool &invalidInput);


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
    cerr << "Could not open board file." << endl;
    return 1;
  }

  while (getline(boardFile, currLine)) {
    tempBoard.push_back(currLine);
  }

  // 3) Build 2-D vector array of characters to store current board
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

void processMove(vector<vector<char>> &currBoard, char currCommand, int numRows, int numColumns, int &currR, int &currC, int &prevR, int &prevC, bool &gameWon, bool &hitWall, bool &invalidInput) {

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
  }
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
    cerr << "Could not open inputs file." << endl;
  }

  while (inputsFile >> currCommand) {
    int prevR;
    int prevC;

    processMove(currBoard, currCommand, numRows, numColumns, currR, currC, prevR, prevC, gameWon, hitWall, invalidInput);

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

  bool gameWon = false;
  bool hitWall = false;
  bool invalidInput = false;

  while (!(gameWon)) {
    int prevR;
    int prevC;

    printCurrBoard(currBoard, numRows, numColumns);

    char currCommand;
    cout << "> ";
    cin >> currCommand;

    if (currCommand == 'q') {
      cout << "You quit the game." << endl;
      break;
    }

    processMove(currBoard, currCommand, numRows, numColumns, currR, currC, prevR, prevC, gameWon, hitWall, invalidInput);

    if (gameWon) {
      printCurrBoard(currBoard, numRows, numColumns);
      cout << "You won the game." << endl;
    }
    else if (hitWall) {
      cout << "You can't move there." << endl;
      hitWall = false;
    }
    else if (invalidInput) {
      cout << "Invalid input." << endl;
      invalidInput = false;
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

void printCurrBoard(vector<vector<char>> currBoard, int numRows, int numColumns) {

  cout << setfill('-') << setw(numColumns + 2) << '-' << endl;

  for (int i = 0; i < numRows; ++i) {
    cout << "|";
    for (int j = 0; j < numColumns; ++j) {
      cout << currBoard[i][j];
    }
    cout << "|" << endl;
  }

  cout << setfill('-') << setw(numColumns + 2) << '-' << endl;

}
