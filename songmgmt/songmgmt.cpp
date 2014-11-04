#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>

using namespace std;

typedef unsigned char byte;

#define GMEXPORT extern "C" __declspec (dllexport)

string tmp;

string toupperstr(string a) {
	string tmp = "";
	for (int i = 0; i < a.length(); i++)
		tmp += toupper(a[i]);
	return tmp;
}

class song {
	public:
		//Default Constructor
		song() {
			name   = "";
			artist = "";
			album  = "";
			genre  = "";
			comment = "";
			path = "";
			year   = 0;
			type   = 0;
			albumart = 0;
			length = 0;
		};
		
		//The one we will actually use for God's sake.
		song(string a, string b, string c, int d, string e) {
			name   = string(a);
			artist = string(b);
			album  = string(c);
			year   = d;
			genre  = string(e);
			type   = 0;
			length = 0;
			albumart = 0;
			comment = "";
			path = "";
		};
		
		//Seperator
		song(string a) {
			name   = string(a);
			type   = 1; //This is how we will tell if it is a seperator or song entity. :)
		};

		//Return Functions
		std::string getName    () { return name;     }
		std::string getArtist  () { return artist;   }
		std::string getAlbum   () { return album;    }
		int         getYear    () { return year;     }
		int         getAlbumArt() { return albumart; }
		std::string getGenre   () { return genre;    }
		std::string getComment () { return comment;  }
		int         getType    () { return type;     }
		int         getLength  () { return length;   }
		std::string getPath    () { return path;     }

		//Modification Functions
		void setName    (string a) { name     = string(a); }
		void setArtist  (string a) { artist   = string(a); }
		void setAlbum   (string a) { album    = string(a); }
		void setYear    (int    a) { year     = a;         }
		void setAlbumArt(int    a) { albumart = a;         }
		void setLength  (int    a) { length   = a;         }
		void setGenre   (string a) { genre    = string(a); }
		void setComment (string a) { comment  = string(a); }
		void setType    (int    a) { type     = a;         }
		void setPath    (string a) { path     = string(a); }

	private:
		std::string name;
		std::string artist;
		std::string album;
		std::string genre;
		std::string comment;
		std::string path;
		int year; //We accept music made before 1 AD, just saying.
		int albumart;
		int length;
		unsigned int type;
};

bool string_artistcompare(song a, song b) {
	return toupperstr(a.getArtist() + a.getName()) < toupperstr(b.getArtist() + b.getName());
}

bool string_songcompare(song a, song b) {
	return toupperstr(a.getName()) < toupperstr(b.getName());
}

vector<song> entries;
vector<song> display;

void sortByArtist(vector<song> &entries, vector<song> &output) {
	//First off... clear the goddamn list.
	vector<song> artists;
	output.clear();

	sort(entries.begin(), entries.end(), string_artistcompare); //This'll fix things up for good.

	string cur_name = "";
	for (int i = 0; i < entries.size(); i++) {
		if (entries[i].getArtist() != cur_name) {
			//Add a separator first.
			output.push_back(song(entries[i].getArtist()));

		}

		cur_name = entries[i].getArtist();

		//Finally, add the song entry in.
		output.push_back(entries[i]);
	}
}

void sortBySong(vector<song> &entries, vector<song> &output) {
	//First off... clear the goddamn list.
	vector<song> artists;
	output.clear();

	sort(entries.begin(), entries.end(), string_songcompare); //This'll fix things up for good.

	char cur_name = ' ';
	for (int i = 0; i < entries.size(); i++) {
		if (entries[i].getName()[0] != cur_name) {
			//Add a separator first.
			output.push_back(song(entries[i].getName().substr(0,1)));
		}

		cur_name = entries[i].getName()[0];

		//Finally, add the song entry in.
		output.push_back(entries[i]);
	}
}

void sortByArtistOld(vector<song> &entries, vector<song> &output) {
	//First off... clear the goddamn list.
	output.clear();

	string cur_name = "";
	for (int i = 0; i < entries.size(); i++) {
		if (entries[i].getArtist() != cur_name)
			//Add a separator first.
			output.push_back(song(entries[i].getArtist()));

		cur_name = entries[i].getArtist();

		//Finally, add the song entry in.
		output.push_back(entries[i]);
	}
}

GMEXPORT double addSong(char* a, char* b, char* c, double d, char* e) {
	//a - Song Name
	//b - Artist
	//c - Album
	//d - Year
	//e - Genre
	entries.push_back(song(a, b, c, d, e));
	return 0;
}

GMEXPORT double addSongGML() {
	//a - Song Name
	//b - Artist
	//c - Album
	//d - Year
	//e - Genre
	entries.push_back(song());
	return 0;
}

//Get Functions
//NOTE: I "would" add overwrite support for the already listed entries but there is no point in it.
//Feel free to add it in if you want.
GMEXPORT double setSongName(double a, char* b) {
	entries[a].setName(b);
	return 0;
}

GMEXPORT double setSongArtist(double a, char* b) {
	entries[a].setArtist(b);
	return 0;
}

GMEXPORT double setSongAlbum(double a, char* b) {
	entries[a].setAlbum(b);
	return 0;
}

GMEXPORT double setSongYear(double a, double b) {
	entries[a].setYear(b);
	return 0;
}

GMEXPORT double setSongGenre(double a, char* b) {
	entries[a].setGenre(b);
	return 0;
}

GMEXPORT double setSongLength(double a, double b) {
	entries[a].setLength(b);
	return 0;
}

GMEXPORT double setSongAlbumArt(double a, double b) {
	entries[a].setAlbumArt(b);
	return 0;
}

GMEXPORT double setSongComment(double a, char* b) {
	entries[a].setComment(b);
	return 0;
}

GMEXPORT double setSongPath(double a, char* b) {
	entries[a].setPath(b);
	return 0;
}

GMEXPORT const char* getSongName(double a, double b) {
	if (b)
		tmp = display[a].getName();
	else
		tmp = entries[a].getName();
	return tmp.c_str();
}

GMEXPORT const char* getSongArtist(double a, double b) {
	if (b)
		tmp = display[a].getArtist();
	else
		tmp = entries[a].getArtist();
	return tmp.c_str();
}

GMEXPORT const char* getSongAlbum(double a, double b) {
	if (b)
		tmp = display[a].getAlbum();
	else
		tmp = entries[a].getAlbum();
	return tmp.c_str();
}

GMEXPORT double getSongYear(double a, double b) {
	if (b)
		return display[a].getYear();
	else
		return entries[a].getYear();
}

GMEXPORT const char* getSongGenre(double a, double b) {
	if (b)
		tmp = display[a].getGenre();
	else
		tmp = entries[a].getGenre();
	return tmp.c_str();
}

GMEXPORT double getSongType(double a, double b) {
	if (b)
		return display[a].getType();
	else
		return entries[a].getType();
}

GMEXPORT double getSongLength(double a, double b) {
	if (b)
		return display[a].getLength();
	else
		return entries[a].getLength();
}

GMEXPORT const char* getSongComment(double a, double b) {
	if (b)
		return display[a].getComment().c_str();
	else
		return entries[a].getComment().c_str();
}

GMEXPORT const char* getSongPath(double a, double b) {
	if (b)
		return display[a].getPath().c_str();
	else
		return entries[a].getPath().c_str();
}

GMEXPORT double getSongAlbumArt(double a, double b) {
	if (b)
		return display[a].getAlbumArt();
	else
		return entries[a].getAlbumArt();
}

GMEXPORT double getCount(double a) {
	if (a)
		return (double)display.size();
	else
		return (double)entries.size();
}

GMEXPORT double sortList(double a) {
	//a - method
	switch ((int)a) {
		case 0:
			//Sort by Artist... which I was going to do anyways.
			sortByArtist(entries, display);
			break;
		case 1:
			//Sort by Artist... which I was going to do anyways.
			sortBySong(entries, display);
			break;
	}
	return 0;
}