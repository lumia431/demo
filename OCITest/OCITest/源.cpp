
//#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
//#define LOGERR(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#define OCI_NUMBER_SIZE 22
#define POS_OR_NEG 0x80//128
#define POS_INT 0xC1//192
#define NEG_INT 0x3E//62
#define TRAILLING 0x66//102
#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
//#include<output_Container.h>
//#include<spdlog/spdlog.h>
//#include<spdlog/logger.h>
//#include<spdlog/sinks/daily_file_sink.h>
using namespace std;
//std::shared_ptr<spdlog::logger> m_logger;
#pragma pack(1)

struct MyOCITime
{
	unsigned char OCITimeHH;                          /* hours; range is 0 <= hours <=23 */
	unsigned char OCITimeMI;                     /* minutes; range is 0 <= minutes <= 59 */
	unsigned char OCITimeSS;                     /* seconds; range is 0 <= seconds <= 59 */
};
typedef struct MyOCITime MyOCITime;

struct MyOCIDate
{
	signed short OCIDateYYYY;         /* gregorian year; range is -4712 <= year <= 9999 */
	unsigned char OCIDateMM;                          /* month; range is 1 <= month < 12 */
	unsigned char OCIDateDD;                             /* day; range is 1 <= day <= 31 */
	MyOCITime OCIDateTime;                                               /* time */
};
typedef struct MyOCIDate MyOCIDate;

#pragma pack()
struct OCINumber
{
	unsigned OCINumberPart[OCI_NUMBER_SIZE];
};

double my_pow(double number, int exp)
{
	double result = number;

	if (exp > 0)
	{
		for (int k = 1; k < exp; k++)
		{
			result = result * number;
		}
		return result;
	}
	else if (exp == 0)
		return 1;
	else if (exp < 0)
	{
		result = (double)1;
		for (int k = 0; k > exp; k--)
		{
			result = result / number;
		}
		return result;
	}
	return 1;
}

int intarrayToint(const int* num, int* result)
{
	*result = 0;
	int length = -1;
	int pos_or_neg = 1;
	int exp = 0;
	int begin = -1;

	for (int k = 0; k <= OCI_NUMBER_SIZE; k++)
	{
		if (num[k] != 0)
		{
			begin = k;
			length = num[begin];
			break;
		}
	}
	if (length > 0)
	{
		pos_or_neg = num[begin + 1] >= POS_OR_NEG ? 1 : -1;
		exp = num[begin + 1] >= POS_OR_NEG ? num[begin + 1] - POS_INT : NEG_INT - num[begin + 1];
		for (int k = begin + 2; k <= begin + length; k++)
		{
			*result = *result + num[k] * my_pow(100, exp--);
		}
	}
	*result *= pos_or_neg;
	return 1;
}

int intarrayToOCINum(const int* num, OCINumber* result)
{
	int			begin = -1;
	bool		is_positive = true;

	/* look for the first significant bit */
	for (int k = 0; k < OCI_NUMBER_SIZE; ++k)
	{
		if (num[k] != 0)
		{
			begin = k;

			break;
		}
	}
	if (begin == -1)
	{
		result->OCINumberPart[0] = 0;
		return 1;
	}
	result->OCINumberPart[0] = num[begin];
	int			length = num[begin];

	is_positive = num[begin + 1] >= POS_OR_NEG ? true : false;
	if (is_positive)
	{
		result->OCINumberPart[1] = num[begin + 1];
		for (int i = begin + 2; i <= begin + num[begin]; ++i)
		{
			result->OCINumberPart[i - begin] = num[i] + 1;
		}
	}
	else
	{
		result->OCINumberPart[1] = num[begin + 1];
		result->OCINumberPart[0] = num[begin] + 1;
		for (int i = begin + 2; i <= begin + num[begin]; ++i)
		{
			result->OCINumberPart[i - begin] = TRAILLING - 1 - num[i];
		}
		if (num[begin] < OCI_NUMBER_SIZE - 1)
			result->OCINumberPart[num[begin] + 1] = TRAILLING;

	}
	return 1;
}

int intTointarray(signed int num, int* result)
{
	signed int	number = num;
	bool		is_positive = number > 0 ? true : false;
	bool		begun = false;
	int			begin = 0;
	int			end = 0;
	int			k = OCI_NUMBER_SIZE - 1;
	int			exp = 1;

	if (num == 0)
	{
		result[0] = 1;
		result[1] = POS_OR_NEG;
		return 1;
	}
	int			number_pos = num;

	if (number < 0)
	{
		number_pos = 0 - number;
	}
	while (number_pos > 0)
	{
		result[k] = number_pos % 100;
		if (!begun && result[k] != 0)
		{
			begun = true;
			begin = k;
		}
		if (result[k] != 0)
			end = k;


		number_pos /= 100;
		k--;
		exp++;
	}
	result[k--] = is_positive ? POS_INT + exp - 2 : NEG_INT - exp + 2;
	result[k] = begin - end + 2;
	return 1;
}

int OCINumberFromInt(const void* inum, OCINumber* number)
{

	bool		is_positive = true;
	int			int_OCI_NUMBER_SIZE[OCI_NUMBER_SIZE] = { 0 };

	if (1)
	{
		int			snum = 0;
		snum = *(int*)inum;
		intTointarray(snum, int_OCI_NUMBER_SIZE);
		int a = 0;
		intarrayToint(int_OCI_NUMBER_SIZE, &a);
		intarrayToOCINum(int_OCI_NUMBER_SIZE, number);
	}

	return 1;
}

inline void GetSplitLen(const std::string& str, std::vector<int>& splitLen, char delim)
{
	splitLen.clear();

	size_t start = str.find_first_not_of(delim, 0);       // 分割到的字符串的第一个字符
	size_t position = str.find_first_of(delim, start);    // 分隔符的位置
	while (position != std::string::npos || start != std::string::npos) {
		// [start, position) 为分割下来的字符串
		splitLen.push_back(str.substr(start, position - start).size());
		start = str.find_first_not_of(delim, position);
		position = str.find_first_of(delim, start);
	}
}

inline void GetSplitLen(char** str, std::vector<int>& splitLen, char delim)
{
	char* p = *str;
	int len = strlen(p);
	char* token = (char*)malloc(len);
	while (*p != '\0')
	{
		int i = 0;
		while (*p != delim && *p != '\0')
		{
			token[i++] = *p++;
		}
		token[i] = '\0';
		splitLen.push_back(strlen(token));
		if (*p == delim)
			p++;

		*str = p;
	}
	free(token);
}

inline void tolower(char* ch)
{
	int len = strlen(ch);
	for (int i = 0; i < len; ++i)
	{
		if (ch[i] >= 'A' && ch[i] <= 'Z')
		{
			ch[i] += 32;
		}
	}
}

int main() {
	vector<int> vv{ 1,2,3 };
	auto it = find(vv.begin(), vv.end(), 2);
	auto nb = distance(vv.begin(), it);
	char* cc = new char[16];
	int aa = 12;
	memcpy(cc, &aa, 4);
	auto dd = *(int *)cc;
	string ssst{ "SksdSldF" };
	tolower((char *)ssst.c_str());
	char* buf = (char*)malloc(1024 * 1024 * 300);
	const int SUM = 395;
	for (int i = 0; i < 1; ++i)
	{
		int index = 0;
		strcpy(buf + SUM * i + index, "aaaaaaaa\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "aaaaaaaa\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "111\t"); // 4
		index += 4;
		sprintf(buf + SUM * i + index, "%05d\t", i); // 6
		index += 6;
		strcpy(buf + SUM * i + index, "aaaaaaaaaa\t"); // 11
		index += 11;
		strcpy(buf + SUM * i + index, "aaaaaaaaaaaaaaaaaaaa\t"); // 21
		index += 21;
		strcpy(buf + SUM * i + index, "aaaaaaaaaaaaaaa\t"); // 16
		index += 16;
		strcpy(buf + SUM * i + index, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\t"); // 31
		index += 31;
		strcpy(buf + SUM * i + index, "a\t"); // 2
		index += 2;
		strcpy(buf + SUM * i + index, "a\t"); // 2
		index += 2;
		strcpy(buf + SUM * i + index, "aaaa\t"); // 5
		index += 5;
		strcpy(buf + SUM * i + index, "aaaa\t"); // 5
		index += 5;
		strcpy(buf + SUM * i + index, "11111111\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "11111111\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "a\t"); // 2
		index += 2;
		strcpy(buf + SUM * i + index, "aaaaaaaa\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "a\t"); // 2
		index += 2;
		strcpy(buf + SUM * i + index, "11111111\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "a\t"); // 2
		index += 2;
		strcpy(buf + SUM * i + index, "111111111.111\t"); // 14
		index += 14;
		strcpy(buf + SUM * i + index, "a\t"); // 2
		index += 2;
		strcpy(buf + SUM * i + index, "aaaaaaaaaaaa\t"); // 13
		index += 13;
		strcpy(buf + SUM * i + index, "1\t"); // 2
		index += 2;
		strcpy(buf + SUM * i + index, "a\t"); // 2
		index += 2;
		strcpy(buf + SUM * i + index, "a\t"); // 2
		index += 2;
		strcpy(buf + SUM * i + index, "a\t"); // 2
		index += 2;
		strcpy(buf + SUM * i + index, "11111111\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "11111111\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "aaaaaaaa\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "aaaaaaaa\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "aaaaaaaa\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "aaaaaaaa\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "aaaaaaaa\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "aaaaaaaa\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "aaaaaaaaaaaaaaa\t"); // 16
		index += 16;
		strcpy(buf + SUM * i + index, "11\t"); // 3
		index += 3;
		strcpy(buf + SUM * i + index, "11111111\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "aaaaaaaaaa\t"); // 11
		index += 11;
		strcpy(buf + SUM * i + index, "aaaaaaaaaaaaaaaaaaaa\t"); // 21
		index += 21;
		strcpy(buf + SUM * i + index, "11111111\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "aaaaaaaa\t"); // 9
		index += 9;
		strcpy(buf + SUM * i + index, "aaaaaaaaaaaaaaa\t"); // 16
		index += 16;
		strcpy(buf + SUM * i + index, "aaaaaaaaaaaaaaaaaaaa\t"); // 21
		index += 21;
		strcpy(buf + SUM * i + index, "111\t"); // 4
		index += 4;
		strcpy(buf + SUM * i + index, "111\n"); // 4
		index += 4;
	}
	int bufLen = strlen(buf);
	char* firstLine = new char[bufLen];
	int lineLen = 0;
	std::vector<int> splitLen;
	sscanf(buf, "%[^\n]%n", firstLine, &lineLen);
	GetSplitLen(&firstLine, splitLen, '\t');
	//auto ff1 = "123323";
	//int64_t lll = 0;
	////auto fff2 = atoi(ff1);
	//sscanf(ff1, "%lld", &lll);
	//cout << lll << endl;
	//float fff = 0;
	//stringstream ssss;
	//sscanf(ff1, "%f", &fff);
	//cout << fff << endl;
	//char ccc[2][3];
	//auto cc1 = ccc[1];
	//unsigned char col[7];
	////col[0] = 0x3c;
	////col[1] = 1;
	////col[2] = 1;
	////col[3] = 1;
	////col[4] = 0x0a;
	////col[5] = 0x7B;
	////col[6] = 0x78;
	//col[0] = 0x78;
	//col[1] = 0x7B;
	//col[2] = 0x0a;
	//col[3] = 1;
	//col[4] = 1;
	//col[5] = 1;
	//col[6] = 0x3c;
	//long long data = 0;
	//memcpy(&data, col, 7);
	//int t = 1 + 23 / 100;
	////memcpy(col, &data, 7);
	//auto s = "123123\neqeq\trf";
	//char* ss2 = new char[30];
	//memset(ss2, 0, 30);
	//memcpy(ss2, s, 3);
	//cout << ss2 << endl;
	//char* first_line = new char[100];
	//int num_chars = 0;
	//// 用sscanf函数将第一行读取到first_line数组中
	//sscanf(s, "%[^\n]%n", first_line, &num_chars);
	//vector<int> v;
	//SplitStr(s, v, '\t');
	//string buf;
	//cout << strcpy((char*)buf.c_str(), s) << endl;
	//stringstream s1(s);
	//string line;
	//getline(s1, line);
	//cout << line << endl;
	//stringstream s2(s);
	//getline(s2, line);
	//cout << line << endl;
	//auto s = "0";
	//int64_t a = 0x01010101010101;
	//MyOCIDate date;
	//memcpy(&date, &a, 7);
	//short ss = 0;
	//void* ptr = &ss;
	//int val = -123456;
	//*(int*)ptr = val;
	//auto aa = val & 0x0000;
	//OCINumber ociNumber;
	//int a = 8000;//2 194 81
	//int b = 80;//2 193 81
	//int c = 800000;//2 195 81
	//int d = 810000;//2 195 82
	//int e = 8512321;//2 195 82
	//int f = 1;//2 195 82
	//OCINumberFromInt(&e, &ociNumber);
	system("pause");
	return 0;
}