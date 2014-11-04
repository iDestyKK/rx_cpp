//Generic
#include <iostream>
#include <sstream>

//Custom Headers
#include "classes.h"

//For GML
#define GMEXPORT extern "C" __declspec (dllexport)

using namespace std;

ノート経営 リスト1; //Initialize the global list for loading data.

//Add Functions
GMEXPORT double addNote(double a, double b, double c, double d, double e) {
	//addNote(player_num, position, colour, sustain, keysound);
	リスト1.push_back_note((int) a, (int) b, (int) c, (int) d, (int) e);
	return 1;
}

GMEXPORT double addBPM(double a, double b) {
	//addBPM(pos, BPM);
	リスト1.push_back_bpm((int) a, b);
	return 1;
}

//Set Functions
GMEXPORT double setPlayerCount(double a) {
	リスト1.セットプレイヤーカウント((int) a);
	return 0;
}

GMEXPORT double clearPlayerNotes(double a) {
	リスト1.プレイヤー片付ける((int) a);
	return 0;
}

GMEXPORT double clearAllNotes() {
	リスト1.片付ける();
	return 0;
}

GMEXPORT double sortPlayer(double a) {
	リスト1.ソートノート((int) a);
	return 0;
}

GMEXPORT double sortAllPlayers() {
	リスト1.すべてのソートノート();
	return 0;
}

GMEXPORT double processMS() {
	リスト1.チャートプリペア();
	return 0;
}

GMEXPORT double setResolution(double a) {
	リスト1.セットレゾリューション((int) a);
	return 0;
}

//Get Functions
GMEXPORT double getPlayerCount() {
	return リスト1.プレイヤーカウント();
}

GMEXPORT double getPlayerSize(double a) {
	//getPlayerSize(player_id)
	return リスト1.プレイヤーデータカウント((int) a);
}

GMEXPORT double getNotePos(double a, double b) {
	//getNotePos(player_id, note_id)
	return リスト1.ノート位置((int) a, (int) b);
}

GMEXPORT double getNoteColour(double a, double b) {
	//getNoteColour(player_id, note_id)
	return リスト1.ノート色((int) a, (int) b);
}

GMEXPORT double getNoteSustain(double a, double b) {
	//getNoteSustain(player_id, note_id)
	return リスト1.ノートサステイン((int) a, (int) b);
}

GMEXPORT double getNoteKeySound(double a, double b) {
	//getNoteKeySound(player_id, note_id)
	return リスト1.ノートキーサウンド((int) a, (int) b);
}

GMEXPORT double getNoteMS(double a, double b) {
	//getNoteKeySound(player_id, note_id)
	return リスト1.ノートMS((int) a, (int) b);
}