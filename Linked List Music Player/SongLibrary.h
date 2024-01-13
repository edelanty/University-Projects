/*
Evan Delanty
3/29/23
Linked Lists
*/

#ifndef SONG_LIBRARY_H
#define SONG_LIBRARY_H

#include <iostream>
#include <fstream>
#include "Song.h"
#include <string>

using namespace std;

class SongLibrary {
	private:
		Song * head;
		string sortAttribute;
	public:
		SongLibrary();
		SongLibrary(const SongLibrary&);
		~SongLibrary();
		Song * getHead() const;
		void setHead(Song *);
		string getSortAttribute() const; 
		void setSortAttribute(string);
		
		void performLoad(string);
		void performSave(string);
		void performSort();
		Song * performSearch(string, string, bool *, int *);
		void performInsertSongInOrder(Song *);
		void performRemoveSong(Song *);
		void performEditSong(Song *, string, string);
		void printLibrary();
};

#endif