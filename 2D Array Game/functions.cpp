//Evan Delanty

#include "header.h"

/*
Function displayBoard()
Takes a 2D array as a parameter along with the size of the rows and colums. Also takes in the players current position coords.
Displays the player location and board that has character values already decided. Prints the values of the 2D to the screen using a nested for loop creating a board.
returns void
*/
void displayBoard(char board[][BOARD_SIZE], int rows, int cols, int currRow, int currCol)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
      board[currRow][currCol] = '@';
			cout << board[i][j];
		}
		cout << endl;
	}
}

/*
Function generateTile()
Uses a constant array of characters to decide what the value of a certain tile is in a 2D array is.
returns void
*/
char generateTile(void) {
  int randNum = rand() % NUM_TILE_TYPES;
  return TILE_TYPES[randNum];
}

/*
Function initBoard()
Requires a 2D array, the size of each row and column in the 2D array, and the players current position as a char
Draws out a mass of characters in the area of the 2D array, sends back the current position of the player (top left) back through as a new character on the array and the previous character tile
*/
void initBoard(char board[][BOARD_SIZE], int rows, int cols, char& currPos) {
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			board[i][j] = generateTile();
		}
	}
	currPos = board[0][0];
	board[0][0] = '@';
}

/*
Function menuPrompt()
Displays the players option of movement or interaction.
returns their choice as a character which interacts with the switch statement in the main function
*/
char menuPrompt(void) {
	char choice = '\0';
	cout << "Pick a direction to move in:" << endl;
	cout << "Directions: (u)p, (d)own, (l)eft, (r)ight " << endl;
	cout << "Actions: (s)earch tile, (c)lear tile" << endl;
	cout << "Options: (i)nventory, (q)uit" << endl;
	cin >> choice;
	return choice;
}

/*
Function playerStatistics()
Takes an array of player stats (health, attack, defense) and displays them onto the screen
returns void
*/
void playerStatistics (double pStats[]) {
	cout << "Health - " << pStats[0] << " | Attack - " << pStats[1] << " | Defense - " << pStats[2] << " |" << endl;
}

/*
Function currTile()
Outputs the current tile your player is on to the terminal
returns void
*/
void currTile (char currPos) {
	cout << "Current Tile: " << currPos << endl;
}

/*
Function pressAnyKey()
Outputs press enter to cont. Uses cin.ignore() to clear the buffer and uses cin.get() to grab something
returns void
*/
void pressAnyKey() {
  cout << "Press enter to continue. . . ";
  cin.ignore(256, '\n');
  cin.get();
}

/*
Function clearTile()
Takes a 90% chance to clear the tile (replace the character value of the 2d array with a space) and to update the game score and tally of cleared tiles
if the 10% chance occurs it will call the function monsterFight() if this function results to true it will clear the tile like usual, and update the gamescore and tally
If the monster fight returns true, there will be an 80% chance of a player item breaking through the function itemBreak()
returns a true or false to decide if the monster fight was won inside this function
*/
bool clearTile(char board[][BOARD_SIZE], char& currPos, int currRow, int currCol, double pStats[], int& gameScore, int playerCurrentInventoryStats[][2], string inventoryDescription[], int& tally) {
  if (currPos != CLEAR_VALUE) {
    if ((rand() % 100) < 90) {
      board[currRow][currCol] = CLEAR_VALUE;
      currPos = CLEAR_VALUE;
      cout << "Tile Cleared" << endl;
      tally++;
      gameScore = gameScore + 5;
      return false;
    } else {
      if (monsterFight(pStats)) {
        board[currRow][currCol] = CLEAR_VALUE;
        currPos = CLEAR_VALUE;
        cout << "Tile Cleared" << endl;
        tally++;
        gameScore = gameScore + 5;

        //Chance of Item Breaking
        if ((rand() % 100) < 80) {
          itemBreak(pStats, playerCurrentInventoryStats, inventoryDescription);
        }
        return false;
      } else {
        return true;
      }
    }
  } else {
    cout << "You've Already Cleared This Tile" << endl;
    return false;
  }
}

/*
Function searchTile()
Takes a 50% chance to clear the tile (replace the character value of the 2d array with a space) and to update the game score and tally of cleared tiles
if the other 50% chance occurs it will call the function monsterFight() if this function results to true it will clear the tile like usual, and update the gamescore and tally
If the monster fight returns true, there will be an 35% chance of a player item breaking through the function itemBreak()
if the monster fight was won, it will call the function addLoot() which adds items with values into the player inventory
returns a true or false to decide if the monster fight was won inside this function
*/
bool searchTile(char board[][BOARD_SIZE], char& currPos, int currRow, int currCol, double pStats[], string inventoryDescription[], int playerCurrentInventoryStats[][2], int& gameScore, int& tally) {
    if (currPos != CLEAR_VALUE) {
      if ((rand() % 100) < 50) {
        addLoot(LOOT_LIST_VALUES, LOOT_LIST_DESCRIPTIONS, inventoryDescription, playerCurrentInventoryStats, pStats);

        gameScore = gameScore + 15;
        board[currRow][currCol] = CLEAR_VALUE;
        currPos = CLEAR_VALUE;
        cout << "Tile Cleared" << endl;
        tally++;
        return false;
    } else {
      if (monsterFight(pStats)) {
        addLoot(LOOT_LIST_VALUES, LOOT_LIST_DESCRIPTIONS, inventoryDescription, playerCurrentInventoryStats, pStats);

        gameScore = gameScore + 15;
        board[currRow][currCol] = CLEAR_VALUE;
        currPos = CLEAR_VALUE;
        cout << "Tile Cleared" << endl;
        tally++;

        //Chance of Item Breaking
        if ((rand() % 100) < 35) {
          itemBreak(pStats, playerCurrentInventoryStats, inventoryDescription);
        }
        return false;
      } else {
        return true;
      }
    }
  } else {
      cout << "You've Already Cleared This Tile" << endl;
      return false;
  }
}

/*
Function monsterFight()
When called outputs to the console the stats of the player and monster, if the player attack is higher than the monster health, the player wins and the functino returns true
if the player loses the fight (monster attack greater than p health) the function returns false which ends the switch statement (ending the game)
Does calculations to the value pStats to update correctly
returns a true or false deciding if the player won or loss
*/
bool monsterFight(double pStats[]) {
  double monsterHealth = 0.0;
  double monsterAttack = 0.0;
  double defenseSub = 0.0;
  double randomNum = (rand() % 15 + 1) / 10.0;

  monsterHealth = pStats[0] * randomNum;
  monsterAttack = pStats[1] * randomNum;

  cout << "A MONSTER APPEARED!" << endl
  << "Player Health: " << pStats[0] << endl
  << "Player Attack/Defense " << pStats[1] << "/" << pStats[2] << endl
  << "Monster Health: " << monsterHealth << endl
  << "Monster Attack: " << monsterAttack << endl
  << "Result:" << endl;

  if (pStats[1] >= monsterHealth) {
    cout << "Player attacks for " << pStats[1] << " damage, you killed it!" << endl;
    return true;
  } else {
    cout << "Player attacks for " << pStats[1] << " damage, it's unfazed!" << endl;
  }

  defenseSub = pStats[2] - monsterAttack;
  
  if (defenseSub <= 0) {
    pStats[0] = pStats[0] - abs(defenseSub);
    pStats[2] = 0;
  }

  if (pStats[0] <= 0) {
    cout << "The monster attacks for " << monsterAttack << " damage, it killed you!" << endl;
    return false;
  } else {
    cout << "The monster attacks for " << monsterAttack << " damage, that hurt..." << endl;
    if (pStats[2] != 0) {
      pStats[2] = pStats[2] - monsterAttack;
    }
    return true;
  }
}

/*
Function addLoot()
Uses multiple 2d arrays assigned with predetirmined names and values to add to the player inventory (another 2d array and a single array for desc) 
Determines if the player inventory is full by looping through each value and finding if it has a value different than 0
*/
void addLoot(const int LOOT_LIST_VALUES[][2], const string LOOT_LIST_DESCRIPTIONS[], string inventoryDescription[], int playerCurrentInventoryStats[][2], double pStats[]) {
  int randNum = 0;
  bool cap = false;
  randNum = rand() % MAX_INVENTORY_SIZE;

  for (int i = 0; i < MAX_INVENTORY_SIZE && cap != true; i++) {
    if (playerCurrentInventoryStats[i][0] == 0) {
      playerCurrentInventoryStats[i][0] = LOOT_LIST_VALUES[randNum][0];
      playerCurrentInventoryStats[i][1] = LOOT_LIST_VALUES[randNum][1];
      inventoryDescription[i] = LOOT_LIST_DESCRIPTIONS[randNum];

      break;
  }
    if (i == MAX_INVENTORY_SIZE - 1) {
      cap = true;
      cout << "Inventory Is Full" << endl;
      return;
    }
}

  cout << "You searched the tile and picked up a " << LOOT_LIST_DESCRIPTIONS[randNum] << "." << endl
  << "(strength: " << LOOT_LIST_VALUES[randNum][0] << ", Defensive? ";

  if (LOOT_LIST_VALUES[randNum][1]) {
    cout << "Yes)" << endl;
    pStats[2] = pStats[2] + LOOT_LIST_VALUES[randNum][0];
  } else {
    cout << "No)" << endl;
    pStats[1] = pStats[1] + LOOT_LIST_VALUES[randNum][0];
  }
}

/*
Function itemBreak()
Deletes a random index of an item from your inventory, and subtracts the strength of that certain item to the array pStats[] if the subtraction reduces the players defense below 0
resets the value to 0
*/
void itemBreak(double pStats[], int playerCurrentInventoryStats[][2], string inventoryDescription[]) {
  int randNum = rand() % MAX_INVENTORY_SIZE;

  while (playerCurrentInventoryStats[randNum][0] == 0) {
    randNum = rand() % MAX_INVENTORY_SIZE;
  }

  cout << "Oh no... your " << inventoryDescription[randNum] << " broke... Fragile I guess." << endl;

  if (playerCurrentInventoryStats[randNum][1] == 1) {
    pStats[2] = pStats[2] - playerCurrentInventoryStats[randNum][0];

    if (pStats[2] < 0) {
      pStats[2] = 0;
    }
  } else {
    pStats[1] = pStats[1] - playerCurrentInventoryStats[randNum][0];
  }

  playerCurrentInventoryStats[randNum][0] = 0;
  playerCurrentInventoryStats[randNum][1] = 0;
}

/*
Function validateMove()
Uses a switch statement to take in the players choice from the menu prompt, and calculates if the new position in teh 2d array will go outside its limits
if it does, it will output to the console that you cannot move there.
*/
bool validateMove(char choice, int currRow, int currCol) {
  switch (choice) {
		case 'u':
      return !(currRow - 1 < 0);
		case 'd':
			return !(currRow + 1 > 9);
		case 'l':
			return !(currCol - 1 < 0);
		case 'r':
		  return !(currCol + 1 > 9);
		default:
			break;
	}
  return 0;
}

/*
Function winCheck()
Finds if the amount of space characters equals the area of the 2d arary (board) if it does equal that, you have won the game and your score is outputted through the main fucntion to the console
*/
bool winCheck(int tally) {
  if (tally == WIN_TALLY) {
    return true;
  } else {
    return false;
  }
}

/*
Displays your inventory only when certain items have values using a loop and static numbers relating to values inside 2D arrays
*/
void invDisplay(string inventoryDescription[], int playerCurrentInventoryStats[][2]) {
  for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
    if (playerCurrentInventoryStats[i][0] != 0) {
      cout << "Item " << i + 1 << ": " << inventoryDescription[i] << " - strength: " << playerCurrentInventoryStats[i][0] << "   Defensive: ";
      if (playerCurrentInventoryStats[i][1]) {
        cout << "Yes" << endl << endl;
      } else {
        cout << "No" << endl << endl;
      }
    }
  }
}