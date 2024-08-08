#pragma once
#include"speaker.h"
using namespace std;
class SpeechManager{
public:
	SpeechManager();
	~SpeechManager();
	void show_Menu();
	void exitSystem();
	void initspeech();
	void createSpeaker();
	void startSpeech();
	void speechDraw();
	void speechContest();
	void showScore();
	void saveRecord();
	void loadRecord();
	void clearRecord();
	bool fileIsEmpty;
	map<int, vector<string>>m_Record;
	vector<int>v1;
	vector<int>v2;
	vector<int>victory;
	map<int, Speaker>m_Speaker;
	int m_Index;
};
void print(int val);