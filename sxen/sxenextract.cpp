#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

typedef unsigned char byte;

#define GMEXPORT extern "C" __declspec (dllexport)

//Global Return String
string RetString;
string song_name = "", song_author = "", song_genre = "", song_album = "", song_length = "", song_comment = "", song_year = "";

string tostring(int integer) {
	string res;
	ostringstream convert;
	convert << integer;
	return convert.str();
}

unsigned int VLQ_to_int(ifstream &pak) {
	unsigned int total = 0;

	//It is a little messy but gets the job done rather fast.
	string bits = "";
	byte b;
	do {
		b = pak.get();
		string seq = "";
		for (int i = 0; i < 7; i++) {
			seq = tostring((b & (1 << i)) != 0) + seq;
		}
		bits = bits + seq;
	} while ((b & (1 << 7)) != 0);

	for (unsigned int i = 0; i < bits.length(); i++) {
		total += pow((double)2, (double)bits.length() - (i + 1)) * (bits[i] != '0');
	}

	//cout << bits << endl;
	return total;
}

void extract_sxen_v01(ifstream &pak, string path) {
	unsigned char length;
	unsigned int fsize;
	vector<byte> file;
	string name = "";
	string cur_dir = "";
	ofstream fp;
	while (pak.eof() == false) {
		switch (pak.get()) {
			case 0x00:
				//File.
				length = pak.get();

				//Grab the Name of the file
				for (int i = 0; i < (int)length; i++) {
					name += pak.get();
				}

				//Get the length of the file (In Bytes)
				fsize = VLQ_to_int(pak);

				file.clear();
				file.resize(fsize);

				pak.read((char*) &file[0], fsize);

				fp.open(path + name, ios::binary);
				fp.write((char*) &file[0],fsize);
				fp.close();

				//Clear out information
				name = "";
				break;
			case 0xFF:
				//Marker.
				length = pak.get();
				string marker = "";
				for (int i = 0; i < (int)length; i++) {
					marker += pak.get();
				}
				cur_dir = marker;
				break;
		}
	}
}

void extract_sxen_v02(ifstream &pak, string path) {
	unsigned int length;

	//Name
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_name += pak.get(); }
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_author += pak.get(); }
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_year += pak.get(); }
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_length += pak.get(); }
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_genre += pak.get(); }
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_album += pak.get(); }
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_comment += pak.get(); }

	//The rest is literally the same as version 1. Carry on.
	extract_sxen_v01(pak, path);
}

void ExtractInformation(ifstream &pak) {
	unsigned int length;

	//Name
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_name += pak.get(); }
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_author += pak.get(); }
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_year += pak.get(); }
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_length += pak.get(); }
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_genre += pak.get(); }
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_album += pak.get(); }
	length = pak.get();
	for (int i = 0; i < (int)length; i++) { song_comment += pak.get(); }
}

void extractSXEN(string filepath, string directory) {
	//Resetting Name Variables
	song_name = "";
	song_author = "";
	song_genre = "";
	song_album = "";
	song_length = "";
	song_comment = "";
	song_year = "";

	string filename = filepath;
	string path = directory;

	ifstream pak;
	pak.open(filename, ios::binary);
	//Carry on by skipping header for now (lazy at 2:46 AM).
	pak.seekg(0x0D);

	//Get Version Number
	unsigned int version_number = (pak.get() * 256) + pak.get();
	switch (version_number) {
		case 1: extract_sxen_v01(pak, path); break;
		case 2: extract_sxen_v02(pak, path); break;
	}
	pak.close();
}

GMEXPORT double ExtractSXENContentsToFolder(char* a, char* b) {
	std::string filepath(a);
	std::string directory(b);
	extractSXEN(filepath, directory);
	return 0;
}

GMEXPORT double GetSXENInformation(char* a) {
	//Resetting Name Variables
	song_name = "";
	song_author = "";
	song_genre = "";
	song_album = "";
	song_length = "";
	song_comment = "";
	song_year = "";

	std::string filepath(a);
	ifstream pak;
	pak.open(filepath, ios::binary);
	pak.seekg(0x0D);

	//Get Version Number
	unsigned int version_number = (pak.get() * 256) + pak.get();
	switch (version_number) {
		case 1: break;
		case 2: ExtractInformation(pak); break;
	}
	pak.close();
	return 0;
}

//Functions for Returning the actual Song Details...
GMEXPORT const char* GetSongName() {
	return song_name.c_str();
}

GMEXPORT const char* GetSongAuthor() {
	return song_author.c_str();
}

GMEXPORT const char* GetSongGenre() {
	return song_genre.c_str();
}

GMEXPORT const char* GetSongAlbum() {
	return song_album.c_str();
}

GMEXPORT const char* GetSongLength() {
	return song_length.c_str();
}

GMEXPORT const char* GetSongComment() {
	return song_comment.c_str();
}

GMEXPORT const char* GetSongYear() {
	return song_year.c_str();
}