/*
Evan Delanty
3/29/23
Linked Lists
*/

#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <cctype>
#include <string>

using namespace std;

const int MIN_RATING = 1;
const int MAX_RATING = 5;

string convertToLowercase(string);

class Song {
	private:
		string title;
		string artist;
		string genre;
		int rating;
		Song * next;
	public:
		Song();
		Song(string, string, string, int);
		Song(const Song&);
		string getTitle();
		void setTitle(string);
		
		string getArtist();
		void setArtist(string);
		
		string getGenre();
		void setGenre(string);
		
		int getRating();
		void setRating(int);
		
		Song * getNext();
		void setNext(Song *);
		
		void displaySong();
		
		string getStringAttributeValue(string);
};

#endif