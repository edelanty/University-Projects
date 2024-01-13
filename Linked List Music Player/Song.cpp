/*
Evan Delanty
3/29/23
Linked Lists
*/

#include "Song.h"

//Converts a given string to lowercase and returns the converted string
string convertToLowercase(string s) {
	for (int i = 0; i < s.length(); i++) {
		s[i] = tolower(s[i]);
	}

	return s;
}

//DVC
Song::Song() {
	title = "";
	artist = "";
	genre = "";
	rating = 1;
	next = NULL;
}

//EVC
Song::Song(string titleParam, string artistParam, string genreParam, int ratingParam) {
	title = titleParam;
	artist = artistParam;
	genre = genreParam;
	setRating(ratingParam);
	next = NULL;
}

//Copy Contructor
Song::Song(const Song& other) {
	title = other.title;
	artist = other.artist;
	genre = other.genre;
	rating = other.rating;
	next = NULL;
}

string Song::getTitle() {
	return title;
}

void Song::setTitle(string newTitle) {
	title = convertToLowercase(newTitle);
}

string Song::getArtist() {
	return artist;
}

void Song::setArtist(string newArtist) {
	artist = convertToLowercase(newArtist);
}

string Song::getGenre() {
	return genre;
}

void Song::setGenre(string newGenre) {
	genre = convertToLowercase(newGenre);
}

int Song::getRating() {
	return rating;
}

void Song::setRating(int newRating) {
	if (newRating < MIN_RATING || newRating > MAX_RATING) {
		cout << "Rating must be in [" << MIN_RATING << ", " << MAX_RATING << "]" << endl;
	}
	if (newRating < MIN_RATING) {
		rating = MIN_RATING;
	}
	else if (newRating > MAX_RATING) {
		rating = MAX_RATING;
	}
	else {
		rating = newRating;
	}
}

Song * Song::getNext() {
	return next;
}

void Song::setNext(Song * newNext) {
	next = newNext;
}

//Gets the string attribute value depending on the attribute entered by the user
string Song::getStringAttributeValue(string attribute) {
	if (attribute == "title") {
		return title;
	} else if (attribute == "artist") {
		return artist;
	} else if (attribute == "genre") {
		return genre;
	} else {
		return to_string(rating);
	}
}

//Display's each element of a node
void Song::displaySong() {
	cout << "\nTitle: " << title << endl;
	cout << "Artist: " << artist << endl;
	cout << "Genre: " << genre << endl;
	cout << "Rating: " << rating << endl;
}