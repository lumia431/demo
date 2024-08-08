#include"speechmanage.h"
using namespace std;
int main() {
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		cout << "选手编号" << it->first <<'\t'<<"姓名" << it->second.m_Name << '\t'<<"分数" << it->second.m_Score << endl;
	}*/
	int choice = 0;
	while (true) {
		sm.show_Menu();
		cout << "请输入您的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.loadRecord();
			break;
		case 3:
			//sm.clearRecord();
			int head, foot ;
			cin >> head >> foot;
			for (int i = 0; i <= head + 1; i++) {
				if (2 * i + 2 * head == foot) {
					cout << "鸡个数为：" << i << "兔个数为：" << head - i << endl;
					break;
				}
				if (i > head) {
					cout << "数据错误" << endl;
				}
			}
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "选择错误" << endl;
			system("pause");
			break;
		}
	}

	system("pause");
	return 0;
}