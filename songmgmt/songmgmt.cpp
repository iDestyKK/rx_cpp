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

vector< vector<song> > entries;
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

GMEXPORT double addSong(char* a, char* b, char* c, double d, char* e, int list_id) {
	//a - Song Name
	//b - Artist
	//c - Album
	//d - Year
	//e - Genre
	entries[list_id].push_back(song(a, b, c, d, e));
	return 0;
}

GMEXPORT double addSongGML(double list_id) {
	//a - Song Name
	//b - Artist
	//c - Album
	//d - Year
	//e - Genre
	entries[list_id].push_back(song());
	return 0;
}

//Get Functions
//NOTE: I "would" add overwrite support for the already listed entries but there is no point in it.
//Feel free to add it in if you want.
GMEXPORT double setSongName    (double a, char*  b, double list_id) { entries[list_id][a].setName    (b); return 0; }
GMEXPORT double setSongArtist  (double a, char*  b, double list_id) { entries[list_id][a].setArtist  (b); return 0; }
GMEXPORT double setSongAlbum   (double a, char*  b, double list_id) { entries[list_id][a].setAlbum   (b); return 0; }
GMEXPORT double setSongYear    (double a, double b, double list_id) { entries[list_id][a].setYear    (b); return 0; }
GMEXPORT double setSongType    (double a, double b, double list_id) { entries[list_id][a].setType    (b); return 0; }
GMEXPORT double setSongGenre   (double a, char*  b, double list_id) { entries[list_id][a].setGenre   (b); return 0; }
GMEXPORT double setSongLength  (double a, double b, double list_id) { entries[list_id][a].setLength  (b); return 0; }
GMEXPORT double setSongAlbumArt(double a, double b, double list_id) { entries[list_id][a].setAlbumArt(b); return 0; }
GMEXPORT double setSongComment (double a, char*  b, double list_id) { entries[list_id][a].setComment (b); return 0; }
GMEXPORT double setSongPath    (double a, char*  b, double list_id) { entries[list_id][a].setPath    (b); return 0; }

GMEXPORT double listClear() {
	entries.clear();
	display.clear();
	return 0;
}

//These are the Get Entry Functions
GMEXPORT const char* getSongName_Entry    (double a, double list_id) { tmp = entries[list_id][a].getName(); return tmp.c_str(); }
GMEXPORT const char* getSongArtist_Entry  (double a, double list_id) { tmp = entries[list_id][a].getArtist(); return tmp.c_str(); }
GMEXPORT const char* getSongAlbum_Entry   (double a, double list_id) { tmp = entries[list_id][a].getAlbum(); return tmp.c_str(); }
GMEXPORT double      getSongYear_Entry    (double a, double list_id) { return entries[list_id][a].getYear(); }
GMEXPORT const char* getSongGenre_Entry   (double a, double list_id) { tmp = entries[list_id][a].getGenre(); return tmp.c_str(); }
GMEXPORT double      getSongType_Entry    (double a, double list_id) { return entries[list_id][a].getType(); }
GMEXPORT double      getSongLength_Entry  (double a, double list_id) { return entries[list_id][a].getLength(); }
GMEXPORT const char* getSongComment_Entry (double a, double list_id) { return entries[list_id][a].getComment().c_str(); }
GMEXPORT const char* getSongPath_Entry    (double a, double list_id) { return entries[list_id][a].getPath().c_str(); }
GMEXPORT double      getSongAlbumArt_Entry(double a, double list_id) { return entries[list_id][a].getAlbumArt(); }
GMEXPORT double      getCount_Entry       (double list_id) { return (double)entries[list_id].size(); }

//These are the Set Display Functions
GMEXPORT const char* getSongName_Display    (double a) { tmp = display[a].getName(); return tmp.c_str(); }
GMEXPORT const char* getSongArtist_Display  (double a) { tmp = display[a].getArtist(); return tmp.c_str(); }
GMEXPORT const char* getSongAlbum_Display   (double a) { tmp = display[a].getAlbum(); return tmp.c_str(); }
GMEXPORT double      getSongYear_Display    (double a) { return display[a].getYear(); }
GMEXPORT const char* getSongGenre_Display   (double a) { tmp = display[a].getGenre(); return tmp.c_str(); }
GMEXPORT double      getSongType_Display    (double a) { return display[a].getType(); }
GMEXPORT double      getSongLength_Display  (double a) { return display[a].getLength();}
GMEXPORT const char* getSongComment_Display (double a) { return display[a].getComment().c_str(); }
GMEXPORT const char* getSongPath_Display    (double a) { return display[a].getPath().c_str(); }
GMEXPORT double      getSongAlbumArt_Display(double a) { return display[a].getAlbumArt(); }
GMEXPORT double      getCount_Display       (        ) { return (double)display.size(); }

GMEXPORT double      getCount_Entries       (        ) { return (double)entries.size(); }

GMEXPORT double addToEntries() {
	entries.resize(entries.size() + 1); //Let STL handle it... I'm seriously too lazy right now.
	return 0;
}

GMEXPORT double sortList(double a, double list_id) {
	//a - method
	switch ((int)a) {
		case -1:
			//No Sorting...
			display = entries[list_id];
			break;
		case 0:
			//Sort by Artist... which I was going to do anyways.
			sortByArtist(entries[list_id], display);
			break;
		case 1:
			//Sort by Artist... which I was going to do anyways.
			sortBySong(entries[list_id], display);
			break;
	}
	return 0;
}