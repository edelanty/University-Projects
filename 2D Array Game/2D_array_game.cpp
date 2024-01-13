/*
Evan Delanty
11/15/22
2D Array Game
Uses 2D arrays, 1D arrays, functions, loops, and if-else statements to create a working adventure game
*/

#include "header.h"

int main() {
	char board[BOARD_SIZE][BOARD_SIZE];
	char choice = '\0', currPos = '\0';
  string inventoryDescription[MAX_INVENTORY_SIZE];
  int playerCurrentInventoryStats[MAX_INVENTORY_SIZE][2] = {0};
  int currRow = 0, currCol = 0, gameScore = 0;
  double pStats[3] = {100.0, 50.0, 0.0};
  bool monsterLossCheck = false;
  int tally = 0;

	srand(time(0));
	
	//initialize our game board with randomly generated tiles
	initBoard(board, BOARD_SIZE, BOARD_SIZE, currPos);

	do {
    cout << "Current Score: " << gameScore << endl;
    playerStatistics(pStats);
		displayBoard(board, BOARD_SIZE, BOARD_SIZE, currRow, currCol);

    board[currRow][currCol] = currPos;
  
    currTile(currPos);
		choice = menuPrompt();

    if (winCheck(tally)) {
      cout << "You Win!" << endl;
	    cout << "Final Score: " << gameScore << endl;

      return -1;
    }

		switch (choice) {
		case 'u':
      if (validateMove(choice, currRow, currCol) == false) {
        cout << "Cannot Move Here" << endl;
        pressAnyKey();
        break;
      }

			currRow = currRow - 1;
      currPos = board[currRow][currCol];
			break;
		case 'd':
      if (validateMove(choice, currRow, currCol) == false) {
        cout << "Cannot Move Here" << endl;
        break;
      }
      
			currRow = currRow + 1;
      currPos = board[currRow][currCol];
			break;
		case 'l':
      if (validateMove(choice, currRow, currCol) == false) {
        cout << "Cannot Move Here" << endl;
        break;
      }

			currCol = currCol - 1;
      currPos = board[currRow][currCol];
			break;
		case 'r':
      if (validateMove(choice, currRow, currCol) == false) {
        cout << "Cannot Move Here" << endl;
        break;
      }

			currCol = currCol + 1;
      currPos = board[currRow][currCol];
			break;
		case 'i':
			invDisplay(inventoryDescription, playerCurrentInventoryStats);

      pressAnyKey();
			break;
		case 's':
			monsterLossCheck = searchTile(board, currPos, currRow, currCol, pStats, inventoryDescription, playerCurrentInventoryStats, gameScore, tally);
      
      if (monsterLossCheck) {
        choice = 'q';
      }

      pressAnyKey();
			break;
		case 'c':
			monsterLossCheck = clearTile(board, currPos, currRow, currCol, pStats, gameScore, playerCurrentInventoryStats, inventoryDescription, tally);
      
      if (monsterLossCheck) {
        choice = 'q';
      }

      pressAnyKey();
			break;
		default:
			break;
		}
	} while (choice != 'q');

	//DISPLAY GAME RESULTS
	cout << "Game Over!" << endl;
	cout << "Score: " << gameScore << endl;

	return 0;
}