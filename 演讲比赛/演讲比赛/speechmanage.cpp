#include "speechmanage.h"
SpeechManager::SpeechManager() {
	this->initspeech();
	this->createSpeaker();
	
	
}
SpeechManager::~SpeechManager() {

}
void  SpeechManager::show_Menu(){
	cout << "************欢迎参加演讲比赛**************" << endl;
	cout << "************1.开始演讲比赛****************" << endl;
	cout << "************2.查看往届记录****************" << endl;
	cout << "************3.清空比赛记录****************" << endl;
	cout << "************0.退出比赛程序****************" << endl;
	cout << "******************************************" << endl;
	cout << endl;
}
void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	exit(0);
}
void  SpeechManager::initspeech() {
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
}
void SpeechManager::createSpeaker() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i <nameseed.size(); i++) {
		string name = "选手";
		name += nameseed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] =0;
		}
		this->v1.push_back(i + 10001);
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}
void SpeechManager::startSpeech() {
	for (this->m_Index = 1; this->m_Index < 3; this->m_Index++) {
		this->speechDraw();
		this->speechContest();
		this->showScore();
	}
	this->saveRecord();
	cout << "~~~~~~~~~~~~~~~本届比赛到此结束~~~~~~~~~~~~~~" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::speechDraw() {
	cout << "第" << this->m_Index << "轮比赛正在进行" << endl;
	cout << "抽签后的演讲顺序如下:" << endl;
	if (this->m_Index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for_each(v1.begin(), v1.end(), print);
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for_each(v2.begin(), v2.end(),print);
	}
	cout << endl;
	system("pause");
}
void print(int val){
	cout << val << " ";
}
void SpeechManager::speechContest() {
    cout << "第" << this->m_Index << "轮比赛正在进行" << endl;
	multimap<double, int, greater<double> > groupScore;
	int num = 0;
	vector<int>src;
	if (this->m_Index == 1) {
		src = v1;
	}
	else
	{
		src = v2;
	}
	for (vector<int>::iterator it = src.begin(); it != src.end(); it++) {
		num++;
		deque<double>d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(),greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.f);
		double avg = sum / (double) d.size();
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		groupScore.insert(make_pair(avg, *it));
		/*cout << "选手编号为:  " << *it << "  姓名:  " << this->m_Speaker[*it].m_Name << "  得分:  " << setprecision(4)<<avg;
		cout << endl;*/
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次:" << endl;
			for (multimap<double, int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "选手编号为:  " << it->second << "  姓名:  " << this->m_Speaker[it->second].m_Name << "  得分:  " << setprecision(4) << this->m_Speaker[it->second].m_Score[this->m_Index - 1];
				cout << endl;
			}
			int count = 0;
			for (multimap<double, int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++) {
				if (this->m_Index == 1) {
					this->v2.push_back(it->second);
				}
				if (this->m_Index == 2) {
					this->victory.push_back(it->second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "~~~~~~~~~~~~~~第" << this->m_Index << "轮比赛结束~~~~~~~~~~~~~~~" << endl;
	system("pause");
	cout << endl;
}
void SpeechManager::showScore() {
	cout << "~~~~~~~~~~~~第" << this->m_Index << "轮晋级选手信息:~~~~~~~~~~~" << endl;
	vector<int>src;
	if (this->m_Index == 1) {
		src = v2;
	}
	else
	{
		src = victory;
	}
	for (vector<int>::iterator it = src.begin(); it != src.end(); it++) {
		cout << "选手编号为:  " << *it << "  姓名:  " << this->m_Speaker[*it].m_Name << "  得分:  " << setprecision(4) << this->m_Speaker[*it].m_Score[this->m_Index-1];
		cout << endl;
	}
	system("pause");
	system("cls");
	this->show_Menu();
}
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = this->victory.begin(); it != victory.end(); it++) {
		ofs<<*it<<","<< this->m_Speaker[*it].m_Score[1]<<",";
	}
	ofs << endl;
	ofs.close();
	cout << "~~~~~~~~~~~~~~~~记录已经保存~~~~~~~~~~~~~~~~~" << endl;
}
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv",ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		this->fileIsEmpty = true;
		cout << "文件为空" << endl;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 1;
	while (ifs >> data) {
		//cout << data << endl;
		vector<string>v;
		int pos = -1;
		int start = 0;
		while (true) {
			pos = data.find(',', start);
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);
			start = pos + 1;
			v.push_back(temp);
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++) {
		cout << "第" << it->first << "届冠军编号：" << it->second[0] << "得分：" << it->second[1] << endl;
	}
	system("pause");
	system("cls");
}
void SpeechManager::clearRecord() {
	cout << "是否确定清空文件" << endl;
	cout << "1、是" << endl;
	cout << "2、否" << endl;
	int select;
	cin >> select;
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initspeech();
		this->createSpeaker();
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}