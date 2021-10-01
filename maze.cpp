#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Function prototypes
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
  ifstream inputsFile; // Input stream for inputs file

  inputsFile.open(file2Name); // Open inputs file

  if (!inputsFile.is_open()) { // Check that inputs file opened correctly
    cerr << "Could not open the inputs file." << endl;
  }

  while (inputsFile >> currCommand) { // ?CONFUSED ABOUT DIFFERENCE BTW .fail(), ,eof(), etc.?
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
            cout << "You can't move there."; // and that the desired spot isn't a wall
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
