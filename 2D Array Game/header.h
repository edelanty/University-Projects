//Evan Delanty

#ifndef HEADER_H
#define HEADER_H

#include <iostream> 
#include <iomanip>
#include <ctime> 
#include <cstdlib>
#include <string>

using namespace std;

const int BOARD_SIZE = 10;
const int NUM_LOOT_ITEMS = 10;
const int MAX_INVENTORY_SIZE = 10;
constexpr int NUM_TILE_TYPES = 5;
const char CLEAR_VALUE = ' ';
const int WIN_TALLY = BOARD_SIZE * BOARD_SIZE;
const int TILE_TYPES[NUM_TILE_TYPES] = {'*', '~', '^', '-', '+'};
const int LOOT_LIST_VALUES[NUM_LOOT_ITEMS][2] = {{10, 0}, {15, 0}, {10, 1}, {15, 1}, {25, 0}, {30, 0}, {25, 1}, {30, 1}, {50, 0}, {50, 1}};
const string LOOT_LIST_DESCRIPTIONS[NUM_LOOT_ITEMS] = {"Straight Sword", "Claymore", "Silver Eagle-Kite Sheild", "Black Knight Shield", "Zweihander", "Greatsword", "Greatshield", "Twin Dragon Greatshield", "Dragonslayer Greataxe", "Havel's Greatshield"};
void displayBoard(char board[][BOARD_SIZE], int rows, int cols, int currRow, int currCol);
char generateTile(void);
void initBoard(char board[][BOARD_SIZE], int rows, int cols, char& currPos);
char menuPrompt(void);
void playerStatistics (double pStats[]);
bool validateMove(char choice, int currRow, int currCol);
void currTile (char currPos);
bool clearTile(char board[][BOARD_SIZE], char& currPos, int currRow, int currCol, double pStats[], int& gameScore, int playerCurrentInventoryStats[][2], string inventoryDescription[], int& tally);
bool monsterFight(double pStats[]);
bool searchTile(char board[][BOARD_SIZE], char& currPos, int currRow, int currCol, double pStats[], string inventoryDescription[], int playerCurrentInventoryStats[][2], int& gameScore, int& tally);
void addLoot(const int LOOT_LIST_VALUES[][2], const string LOOT_LIST_DESCRIPTIONS[], string inventoryDescription[], int playerCurrentInventoryStats[][2], double pStats[]);
void invDisplay(string inventoryDescription[], int playerCurrentInventoryStats[][2]);
bool winCheck(int tally);
void pressAnyKey(void);
void itemBreak(double pStats[], int playerCurrentInventoryStats[][2], string inventoryDescription[]);

#endif