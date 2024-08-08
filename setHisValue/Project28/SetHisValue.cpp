#include "SetHisValue.h"

using  std::cout;
SetHisValue::~SetHisValue()
{
	m_fileName.clear();
	m_tagNames.clear();
	m_Datas.clear();
	this->m_dbApi.Disconnect();
	this->m_dbApi.UnSetDefaultInstance();
}

void SetHisValue::Run()
{
	getFiles();//get all file names from dir
	if (m_fileName.size()<1)
	{
		cout << "m_fileName.number = none" << endl;
		return;
	}

	WriteLog( "file size ="+to_string(m_fileName.size()));

	if (!connectflg)
	{
		if (getTagName() < 0)
		{
			WriteLog("getTagName error!");
		}
	}
	cout << "getTagName over!" << endl;
	if (testflg)
	{
		Test();
	}
	else
	{
		if (GetData() < 0)
		{
			cout << "ReadData error!" << endl;
		}
	}
}

int SetHisValue::Init()
{
	string tagdir = "./tagName";
	if (_access(tagdir.c_str(), 0) == -1)
	{
		int flag = _mkdir(tagdir.c_str());

		if (flag == 0)
		{
			WriteLog("mkdir successfully");
		}
		else
		{
			WriteLog("mkdir fail");
		}
	}
	string pointdir = "./point";
	if (_access(pointdir.c_str(), 0) == -1)
	{
		int flag = _mkdir(pointdir.c_str());

		if (flag == 0)
		{
			WriteLog("mkdir successfully");
		}
		else 
		{
			WriteLog("mkdir fail");
		}
	}
	std::ifstream file("./config.ini");
	if (!file)
	{
		WritePrivateProfileString("Config", "Add", "127.0.0.1", "./config.ini");
		WritePrivateProfileString("Config", "Port", "7000", "./config.ini");
		WritePrivateProfileString("Config", "DbID", "101", "./config.ini");
		WritePrivateProfileString("Config", "Path", "./point", "./config.ini");
		WritePrivateProfileString("Config", "Prefix", "SM1:", "./config.ini");
		WritePrivateProfileString("Config", "Interval", "1000", "./config.ini");
		WritePrivateProfileString("Config", "Test", "0", "./config.ini");
	}
	char* lpPath = new char[MAX_PATH];
	char* add_ = new char[20];
	char* path_ = new char[100];
	char* pref_ = new char[100];
	char* dbID = new char[100];
	int port_;
	int test_;
	strcpy_s(lpPath, MAX_PATH, "./config.ini");

	GetPrivateProfileString("Config", "Add", "", add_, 20, lpPath);
	GetPrivateProfileString("Config", "Path", "", path_, 100, lpPath);
	GetPrivateProfileString("Config", "Prefix", "", pref_, 100, lpPath);
	GetPrivateProfileString("Config", "DbID", "", dbID, 100, lpPath);
	port_ = GetPrivateProfileInt("Config", "Port", 0, lpPath);
	interval = GetPrivateProfileInt("Config", "Interval", 0, lpPath);
	test_ = GetPrivateProfileInt("Config", "Test", 0, lpPath);
	
	delete[] lpPath;
	string addstr = (string)add_;
	filePath = (string)path_;
	m_prefix = (string)pref_;
	dbID_ = (string)dbID;
	delete[]dbID;
	delete[] add_;
	m_info.addr = StringToWstring(addstr);
	m_info.port = port_;
	testflg = test_;
	if (m_dbApi.Connect(m_info) < 0)
	{
		connectflg = false;
		cout << "connect error" << endl;
	}
	return 0;
}

void SetHisValue::Test()
{
	if (GetDatas() < 0)
	{
		cout << "ReadData error!" << endl;
	}
	while (1)
	{
		cout << "put in the name of point:" << endl;
		string str;
		cin >> str;
		if (str == "0")
		{
			break;
		}
		for (auto & m_test : m_Test[str])
		{
			cout << m_test << endl;
		}
	}
}

int SetHisValue::WriteTagName(string &strArg)
{
	std::ofstream ofile(strArg, (std::ios::ate | std::ios::out));

	for (set<string>::iterator it = (++m_tagNames.cbegin());it!= m_tagNames.cend();++it)
	{
		ofile <<*it<< endl;
	}
	ofile.close();
	return 0;
}

int SetHisValue::GetData()
{
	int fileIndex = 0;
	int lineIndex = 0;
	int pointIndex = 0;	
	TagData tag;
	tag.status = 1;
	string data_;
	FILETIME ft;
	vector <string> linedata;
	vector<string>tagNames;
	for (auto &fileList : m_fileName)
	{
		string filepath = filePath + "\\"+fileList;
		ifstream istrm(filepath);
		if (!istrm)
		{
			return -1;
		}

		while (getline(istrm, data_))
		{
			pointIndex = 0;
			if (lineIndex == 0)
			{
				string strTemp(data_, 10);
				SplitTagName(strTemp, tagNames, "\t");
				lineIndex++;
				continue;
			}
			DataProcess(data_, linedata);
			Time_tToFileTime(StrToTime(linedata.front()),&ft);
			tag.timestamp = ft;
			for (auto it=(++linedata.begin()); it!=linedata.end();++it)
			{
				tag.value = (atof(it->c_str()));
				m_Datas[tagNames[pointIndex]].push_back(tag);
				pointIndex++;
			}
			linedata.clear();
			lineIndex++;
		}
		tagNames.clear();
		cout << "read over ,fileID = " + to_string(fileIndex) << endl;
		istrm.close();
		/*remove(filepath.c_str());*/
		lineIndex = 0;
		fileIndex++;
	}
	SetValue();
	return 0;
}

int SetHisValue::GetDatas()
{
	int fileIndex = 0;
	int lineIndex = 0;
	int pointIndex = 0;
	string data_;
	vector <string> linedata;
	vector<string>tagNames;
	for (auto &fileList : m_fileName)
	{
		string strTest = "";
		string filepath = filePath + "\\" + fileList;
		ifstream istrm(filepath);
		if (!istrm)
		{
			return -1;
		}

		while (getline(istrm, data_))
		{
			pointIndex = 0;
			if (lineIndex == 0)
			{
				string strTemp(data_, 10);
				SplitString(strTemp, tagNames, "\t");
				lineIndex++;
				continue;
			}
			
			DataProcess(data_, linedata);
			for (auto it = (++linedata.cbegin()); it != linedata.cend(); ++it)
			{
				m_Test[tagNames[pointIndex]].push_back(fileList + '\t'+" column = " + to_string(pointIndex + 1)
					+ '\t'+" time= " + linedata.front() + '\t'+" value= " + *it);
				pointIndex++;
			}
			linedata.clear();
			break;
		}
		cout << "read over ,fileID = " + to_string(fileIndex) << endl;
		istrm.close();
		/*remove(filepath.c_str());*/
		lineIndex = 0;
		fileIndex++;
		tagNames.clear();
	}
	return 0;
}

int SetHisValue::SetValue()
{
	cout << "start setvalue" << endl;
	vector<wstring>tagname;
	vector <TAGID> tagIDList;
	for (auto &datas : m_Datas)
	{
		tagname.push_back(StringToWstring(dbID_ + "." + datas.first));
		if (m_dbApi.GetTagIDByTagName(tagname, tagIDList) < 0)
		{
			cout << "get tagID error tagName = " + datas.first << endl;
			continue;
		}
		long scanIdx = 1;
		while ((scanIdx*interval) <= datas.second.size())
		{
			if (!m_dbApi.Connected())
			{
				cout << "connect failed" << endl;
				while (1)
				{
					if (m_dbApi.Connect(m_info) >= 0)
					{
						cout << "reconnect success" << endl;
						break;
					}
					Sleep(10000);
				}
			}
			if (((scanIdx + 1)*interval) > datas.second.size())
			{
				
				vector<TagData>data_(datas.second.begin() + (interval*(scanIdx - 1)), datas.second.end());
				int ret = m_dbApi.SetHistoryValues(tagIDList.back(), data_);
				if (ret >= 0)
				{
					cout << "set value success tagID = " + to_string(tagIDList.back().tagID) << endl;
					
				}
				else
				{
					cout << "set value fail" + to_string(tagIDList.back().tagID) << endl;
				}
				break;
			}
			vector<TagData> data_(datas.second.begin() + (interval*(scanIdx - 1)), datas.second.begin() + (interval)*scanIdx);
			int ret = m_dbApi.SetHistoryValues(tagIDList.back(), data_);
			if (ret >= 0)
			{
				cout << "set value success tagID = " + to_string(tagIDList.back().tagID) << endl;

			}
			else
			{

				cout << "set value fail" + to_string(tagIDList.back().tagID) << endl;
			}
			scanIdx++;
		}
		scanIdx = 1;
		tagIDList.clear();
		tagname.clear();
	}
	cout << "set history over" << endl;
	return 0;
}

void SetHisValue::getFiles()
{
	//char buf1[256] = { 0 };
	//_getcwd(buf1, sizeof(buf1));
	//char buf2[20] = { 0 };
	//strcpy(buf2, buf1);
	//strcat(buf2, "\\point");
	string pointstr = "dir " + filePath + " /B > ./fname.txt";
	//const char *a =("dir %s /B > D:\\fname.txt", pointstr.c_str());
	system(pointstr.c_str());
	ifstream fReadFName("./fname.txt");
	string tName;
	while (getline(fReadFName, tName))
	{
		m_fileName.push_back(tName);
	}
}

int  SetHisValue::getTagName()
{
	string data_;
	string dataStr;
	string strArg = "./tagName/" + m_prefix.substr(0, m_prefix.size() - 1) + ".csv";
	int fileIndex = 0;
	for (auto &fileList : m_fileName)
	{
		string filepath (filePath + "\\" + fileList);
		ifstream istrm(filepath);
		if (!istrm)
		{
			return -1;
		}
		getline(istrm, data_);
		stringstream input(data_);
		while (input >> dataStr)
		{
			m_tagNames.insert(m_prefix+ dataStr);
		}
		WriteTagName(strArg);
		fileIndex++;
		data_.clear();
	}
	return 0;
}

void SetHisValue::WriteLog(std::string log) {
	try
	{
		std::ofstream ofs;
		time_t t = time(0);
		char tmp[64];
		strftime(tmp, sizeof(tmp), "[%Y-%m-%d %X]", localtime(&t));
		ofs.open("./log.log", std::ofstream::app);

		ofs << tmp << " - ";
		ofs.write(log.c_str(), log.size());
		ofs << std::endl;
		ofs.close();
		FILE * pFile;
		long size;
		pFile = fopen("./log.log", "rb");

		fseek(pFile, 0, SEEK_END);   ///将文件指针移动文件结尾
		size = ftell(pFile); ///求出当前文件指针距离文件开始的字节数
		fclose(pFile);
		if (size > 10000000)
		{
			remove("./log.log");
		}
		
	}
	catch (...)
	{
	}

}

void SetHisValue::DataProcess(string & data_, vector<string>& dat)
{
	SplitString(data_, dat, "\t");
	for (auto &linedat : dat)
	{
		//for (string::size_type i = 0; i < linedat.size(); i++)
		//{
		//	if (isdigit(linedat[i]))
		//	{
		//		linedat = linedat.substr(i, linedat.size() - i - 2);
		//		break;
		//	}
		//	if (i == linedat.size() - 1)
		//	{
		//		if (!isdigit(linedat[linedat.size() - 1]))
		//		{
		//			linedat = "0";
		//			break;
		//		}
		//	}
		//}
		if (linedat.size() < 3)
		{
			linedat = "0";
			continue;
		}
		for (string::size_type i = 0; i < linedat.size(); i++)
		{
			if (isdigit(linedat[i]))
			{
				linedat = linedat.substr(i, linedat.size() - i - 2);
				break;
			}
		}
	}
}

time_t StrToTime(const std::string& str) {
	char* ptr = (char*)str.c_str();
	tm tmTemp;
	int year, month, day, hour, minute, second = 0;
	auto ret = sscanf_s(ptr, "%d/%d/%d %d:%d:%d", &month, &day, &year, &hour, &minute, &second);
	tmTemp.tm_year = year - 1900;
	tmTemp.tm_mon = month - 1;
	tmTemp.tm_mday = day;
	tmTemp.tm_hour = hour;
	tmTemp.tm_min = minute;
	tmTemp.tm_sec = second;
	tmTemp.tm_isdst = 0;
	time_t tTemp = mktime(&tmTemp);
	return tTemp;
}

void inline Time_tToFileTime(time_t t, FILETIME *ft)
{
	LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
	ft->dwLowDateTime = (DWORD)ll;
	ft->dwHighDateTime = (DWORD)(ll >> 32);
}

std::wstring StringToWstring(const std::string str)
{// string转wstring
	unsigned len = str.size() * 2;// 预留字节数
	setlocale(LC_CTYPE, "");     //必须调用此函数
	wchar_t *p = new wchar_t[len];// 申请一段内存存放转换后的字符串
	mbstowcs(p, str.c_str(), len);// 转换
	std::wstring str1(p);
	delete[] p;// 释放申请的内存
	return str1;
}

void SplitString(const string& s, vector<string>& v, const string& c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

void SetHisValue::SplitTagName(const string & s, vector<string>& v, const string & c)
{
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (string::npos != pos2)
	{
		v.push_back(m_prefix+s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(m_prefix+s.substr(pos1));
}
