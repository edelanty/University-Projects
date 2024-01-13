/*
Evan Delanty
3/29/23
Linked Lists
*/

#include "Header.h"

void displayMenu() {
	cout << endl << "Welcome to the Music Manager!!" << endl;
	cout << "Please choose from the following options: " << endl;
	cout << "1) Load library" << endl;
	cout << "2) Store library" << endl;
	cout << "3) Display library" << endl;
	cout << "4) Sort library" << endl;
	cout << "5) Search library" << endl;
	cout << "6) Insert song in order" << endl;
	cout << "7) Remove song" << endl;
	cout << "8) Edit song" << endl;
	cout << "9) Exit" << endl;
}

int getValidChoice() {
	int choice = -1;
	string temp;
	do {
		cout << "Choice: ";
		cin >> choice;
		if (choice < FIRST_OPTION || choice > LAST_OPTION) {
			cout << "That is not a valid option. Please try again." << endl;
		}
	} while (choice < FIRST_OPTION || choice > LAST_OPTION);
	getline(cin, temp); // flush the newline outta the buffer
	return choice;
}

void executeUserChoice(int choice, SongLibrary& lib) {
	string filename, attribute, attributeVal, newTitle, newArtist, newGenre, trash, newAttribute;
	int indexOfSearchedSong, newRating;
	bool foundSong;
	Song *song, *newSong, *songToEdit;

	switch (choice) {
		case 1:
			cout << "Enter The File Name You Wish To Load: ";
			getline(cin, filename);

			lib.performLoad(filename);

			break;
		case 2:
			cout << "Enter The File Name You Wish To Save To: ";
			getline(cin, filename);

			lib.performSave(filename);

			break;
		case 3: 
			lib.printLibrary();

			break;
		case 4:
			cout << "What Attribute Do You Wish To Sort By? " << "Enter Here: ";
			getline(cin, attribute);

			for (int i = 0; i < attribute.length(); i++) {
				attribute[i] = tolower(attribute[i]);
			}

			lib.setSortAttribute(attribute);

			lib.performSort();

			break;
		case 5:
			cout << "What Attribute Are You Looking For?" << endl << "Enter Here: ";
			getline(cin, attribute);

			cout << "\nEnter What You Are Searching For: ";
			getline(cin, attributeVal);

			song = lib.performSearch(attribute, attributeVal, &foundSong, &indexOfSearchedSong);

			if (foundSong) {
				cout << "\nSong Found" << endl;
				song->displaySong();
			} else {
				cout << "\nSong Wasn't Found" << endl;
			}

			break;
		case 6:
			cout << "\nEnter Title of New Song: ";
			getline(cin, newTitle);

			cout << "\nEnter Artist of New Song: ";
			getline(cin, newArtist);

			cout << "\nEnter Genre of New Song: ";
			getline(cin, newGenre);

			cout << "\nEnter Rating of New Song: ";
			cin >> newRating;

			getline(cin, trash); //Buffer

			newTitle = convertToLowercase(newTitle);
			newArtist = convertToLowercase(newArtist);
			newGenre = convertToLowercase(newGenre);

			newSong = new Song(newTitle, newArtist, newGenre, newRating);

			lib.performInsertSongInOrder(newSong);

			break;
		case 7:
			cout << "What Attribute Are You Looking For To Delete: ";
			getline(cin, attribute);

			cout << "What's The Attribute Called: ";
			getline(cin, attributeVal);

			cout << "Deleteing Now..." << endl;

			lib.performRemoveSong(lib.performSearch(attribute, attributeVal, &foundSong, &indexOfSearchedSong));
			break;
		case 8:
			cout << "What Attribute Are You Looking For To Edit: ";
			getline(cin, attribute);

			cout << "What's The Attribute Called: ";
			getline(cin, attributeVal);

			cout << "What Are You Trying To Change The Attribute To: ";
			getline(cin, newAttribute);

			songToEdit = lib.performSearch(attribute, attributeVal, &foundSong, &indexOfSearchedSong);

			if (foundSong) {
				cout << "Found! Editing Now..." << endl;

				lib.performEditSong(songToEdit, attribute, newAttribute);
			} else {
				cout << "Coudn't Find Song!" << endl;
			}

			break;
		default:
			cout << "Unrecognized menu choice" << endl;
			break;
	}
}

void runMusicManager() {
	SongLibrary lib;
	
	int choice = -1;
	do {
		displayMenu();
		choice = getValidChoice();
		if (choice != QUIT_OPTION) {
			executeUserChoice(choice, lib);
		}
	} while (choice != QUIT_OPTION);
	cout << "Thanks for you using the Music Manager!!" << endl;
}
