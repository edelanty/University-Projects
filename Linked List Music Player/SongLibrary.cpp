/*
Evan Delanty
3/29/23
Linked Lists
*/

#include "SongLibrary.h"

//DVC
SongLibrary::SongLibrary() {
	head = NULL; 
	sortAttribute = "title";
}

//Copy Constructor
SongLibrary::SongLibrary(const SongLibrary& other) {
	head = other.head; // fixed?
	sortAttribute = other.sortAttribute;
}

//Destructor
SongLibrary::~SongLibrary() {
	if(head == NULL) {
		return;
	}

	Song * cur = head;
	Song * prev = NULL;

	while(cur != NULL) {
		prev = cur;
		cur = cur->getNext();
		delete prev;
	}
}

Song * SongLibrary::getHead() const {
	return head;
}

// TODO: finish this function
void SongLibrary::setHead(Song * newHead) {
	if (head != NULL) {
		delete head;
	}

	head = newHead;
}

string SongLibrary::getSortAttribute() const {
	return sortAttribute;
}

void SongLibrary::setSortAttribute(string newSortAttribute) {
	sortAttribute = newSortAttribute;
}

/*
Class Member function performLoad
This function takes in a string parameter 'filename' and opens a file with that string name.
Function takes input from the file, and places it as an EVC to a dynamically allocated array newSong.
This newSong is passed into a sorting function, which places the songs together sorted by the users command or the DVC (title)
The file is then closed.
*/
void SongLibrary::performLoad(string filename) {
	ifstream infile;
	string title, artist, genre, trash;
	int rating;

	infile.open(filename);

	if (!infile.is_open()){
		cout << "Failed to open file" << endl;
		return;
	}

	while (!infile.eof()) {
		getline(infile, title);
		getline(infile, artist);
		getline(infile, genre);
		infile >> rating;

		getline(infile, trash);
		getline(infile, trash);

		Song *newSong = new Song(title, artist, genre, rating);
		performInsertSongInOrder(newSong);
	}

	infile.close();
}

/*
Class Member function performSave has a single parameter in the form of a string 'filename'. This name is used to open an output file.
Once the output file is open information respective to each index of the songs array is outputted to the file.
The output file is then closed.
*/
void SongLibrary::performSave(string filename) {
	ofstream outfile;

	cout << "\nSaving To " << filename << endl;

	outfile.open(filename);

	Song * cur = head;

	while (cur != NULL) {
		outfile << cur->getTitle() << endl; 
		outfile << cur->getArtist() << endl;
		outfile << cur->getGenre() << endl;
		outfile << cur->getRating() << endl;

		if (cur->getNext() != NULL) {
			outfile << endl;
		}
		
		cur = cur->getNext();
	}

	outfile.close();
}

/*
Class Member function performSort takes in a single parameter 'attribute'. Attribute represents what the user wants to sort the library by.
This can be any attribute, a sort is done (swaps smallest) (always sorts from 1 - 5, and alphabetically by first letter)
*/
void SongLibrary::performSort() {
	if (head == NULL) {
		return;
	}

	Song * newHead = head;
	head = NULL;

	Song * cur = newHead;
	Song * next;

	while (cur != NULL) {
		next = cur->getNext();
		this->performInsertSongInOrder(cur);
		cur = next;
	}
}

/*
Class Member function performSearch takes in a two string parameters, both user inputs, and two output parameters in the form
of the found song bool and found song's index. The function searches through the list until the attribute values match.
Output parameters determine if the song was found, and the index of the song. The function will return a Song if found, and NULL if nothing.
*/
Song * SongLibrary::performSearch(string searchAttribute, string searchAttributeValue, bool * found, int * index) {
	int counter = 0;

	if (head == NULL) {
		cout << "Empty List";

		return NULL;
	}

	searchAttribute = convertToLowercase(searchAttribute);
	searchAttributeValue = convertToLowercase(searchAttributeValue);

	Song * cur = head;

	while (cur != NULL) {
		if (cur->getStringAttributeValue(searchAttribute) == searchAttributeValue) {
			*found = true;
			*index = counter;

			return cur;
		}

		cur = cur->getNext();
		counter++;
	}

	return NULL;
}

/*
Member Function performInsertSongInOrder takes in a Song pointer of the song to insert (attributes) and iterates through a linked list
by assigning the current node to the previous node and moving the current node to the next node. It compares the values of the attributes
and determines where in the list the node belongs.
returns void
*/
void SongLibrary::performInsertSongInOrder(Song * songToInsert) {
	if (head == NULL) {
		head = songToInsert;
		head->setNext(NULL);
		return;
	}

	Song * cur = head;
	Song * prev = NULL;

	// Moves the two node pointers along the list
    while (cur != nullptr && cur->getStringAttributeValue(sortAttribute) < songToInsert->getStringAttributeValue(sortAttribute)) { 
        prev = cur;
        cur = cur->getNext();
    }

    // Handles case of insertion at the front
    if (prev == nullptr) {
        songToInsert->setNext(head);
        head = songToInsert;
    } else { // Handles case of insertion anywhere else in the list
        prev->setNext(songToInsert);
        songToInsert->setNext(cur);
    }
}

/*
Class Member function performRemoveSong takes a single parameter 'songToRemove'. This function assigns the head memory address to a pointer 'cur'
it will iterate through a list until cur is at the node of the song to remove. Once this is done, it will go through a series of if statements
that determines whether to move to the next node, and delete the previous one, or if the value couldn't be found.
*/
void SongLibrary::performRemoveSong(Song * songToRemove) {
	Song *cur = head;
	Song *prev = nullptr;

	while (cur != NULL && cur != songToRemove) {
		prev = cur;
		cur = cur->getNext();
	}

	if (prev == NULL) {
		head = head->getNext();

		delete cur;
	} else if (cur == NULL) {
		cout << "Couldn't Find Value" << endl;
	} else {
		prev->setNext(cur->getNext());

		delete cur;
	}
}

/*
Class Member function performEditSong iterates through the list until cur is at the node in which the songToEdit was declared
Since we are on that node, if the attribute wished to be changed is correctly entered, it will execute a series of if statements that
sets the attribute to the new attribute value.
*/
void SongLibrary::performEditSong(Song * songToEdit, string attribute, string newAttributeValue) {
	if (head == NULL) {
		return;
	}

	attribute = convertToLowercase(attribute);
	newAttributeValue = convertToLowercase(newAttributeValue);

	cout << "Editing " << songToEdit->getTitle() << "'s " << attribute << endl;

	Song * cur = head;

	while (cur != songToEdit) {
		cur = cur->getNext();
	}

	if (attribute == "title") {
		cur->setTitle(newAttributeValue);
	} else if (attribute == "artist") {
		cur->setArtist(newAttributeValue);
	} else if (attribute == "genre") {
		cur->setGenre(newAttributeValue);
	} else {
		cur->setRating(stoi(newAttributeValue));
	}
}

/*
Iterates through the list and each node/song is outputed to the terminal until the end of the linked list
*/
void SongLibrary::printLibrary() {
	Song * cur = head;

	while (cur != NULL) {
		cur->displaySong();
		cur = cur->getNext();
	}
}