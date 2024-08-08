#ifndef DEMO2_ORACLE
#include "demo2.h"
#endif

#include <vector>
#include <string>
#include <iostream>
using namespace std;
using namespace::oracle;

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

inline std::vector<std::string> split(char* str)
{
	std::vector<std::string> vec;

	if (str == nullptr)
	{
		return vec;
	}
	int len = strlen(str);
	if (len < 2)
	{
		return vec;
	}
	if (str[0] == '"' && str[len - 1] == '"')
	{
		str += 1;
		str[len - 2] = '\0';
	}
	len = strlen(str);
	str[0] = ',';
	str[len - 1] = ',';
	bool inQuotation = false;
	int quotationCount = 0;
	int last = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (inQuotation && str[i] == '"')
		{
			++quotationCount;
		}
		if (str[i] == ',')
		{
			if (quotationCount % 2 == 0)
			{
				if (i > 0)
				{
					vec.emplace_back(str + last + 1, i - last - 1);
					cout << str[i] << endl;
					cout << str[i + 1] << endl;
				}
				inQuotation = false;
				quotationCount = 0;
				last = i;
				if (str[i + 1] == '"')
				{
					inQuotation = true;
					quotationCount = 0;
				}
			}
		}
	}
	return vec;
}

inline void ToUpper(const char* ch, char* out)
{
	int len = strlen(ch);
	for (int i = 0; i < len; ++i)
	{
		if (ch[i] >= 'a' && ch[i] <= 'z')
		{
			out[i] = ch[i] - 32;
		}
		else
		{
			out[i] = ch[i];
		}
	}
}

class A {
public:
	A(void *p) {
		v_ = (vector<string>*)p;
	}
	void f()
	{
		v_->emplace_back("123");
		v_->emplace_back("456");
	}
private:
	vector<string>* v_;
};

const unsigned int COL_SIZE[45] = { 8, 8, sizeof(int32_t), 12, 10, 20, 15, 30, 1, 1, 4, 4, sizeof(int64_t), sizeof(int32_t), 1, 8, 1,
								   sizeof(int32_t), 1, sizeof(int64_t), 1, 12, sizeof(int32_t), 1, 1, 1, sizeof(int64_t), sizeof(int64_t),
								   8, 8, 8, 8, 8, 8, 15, sizeof(int32_t), sizeof(int64_t), 10, 20, sizeof(int64_t), 8, 15, 20, sizeof(int32_t), sizeof(int32_t) };

int main()
{
	//constexpr int ROW_NUM = 1;
	//int64_t* value12 = (int64_t*)malloc(ROW_NUM * COL_SIZE[12]);
	//int valInt = 1;
	//for (int i = 0; i < ROW_NUM; ++i)
	//{
	//	memcpy((char*)value12 + i * (COL_SIZE[12]), &valInt, COL_SIZE[12]);
	//}
	//cout << value12[0] << endl;
	string ssstr = "21321";
	auto uuu = "SkSiijSOK123Lds";
	char out1[128] = {};
	ToUpper(uuu, out1);
	auto ttt = "abc1233";
	char schema[12] = {};
	char typname[12] = {};
	char sql[12] = {};
	sscanf(ttt, "%[^.].%s", schema, typname);
	strcpy(schema, "abc");
	printf("%05d\n", 1);
	char ccc[11] = "123456789\t";
	char* cc = new char[3];
	memcpy(cc, ccc, 3);
	double ff = 11111111111.12;
	cout << ff << endl;
	char* itemstart = NULL;
	char* dstptr = NULL;
	char* dstendptr = NULL;
	auto ptr = "123456789";
	itemstart = dstptr = dstendptr = (char *)ptr;
	auto aaa = *dstendptr++;
	char str[] = "\"(123,2343,231231,\"12312\")\"";
	unsigned int aa = 0;
	auto out = split(str);
	cout << out[0] << out[1] << out[2] << out[3] << endl;
	//string str = "PwsdwW";
	//tolower((char*)str.c_str());
	//const char* str = "www.abc";

	//char addr[64] = "";
	//char port[64] = "";
	//int ret;

	//ret = sscanf(str, "%[^.].%s", addr, port);
	//Environment* env = Environment::createEnvironment();
	string test{ "'abc\"de'fg\"" };
	int pos = 0;
	while (pos < test.size())
	{
		if (test[pos] == '"')
		{
			test.insert(pos, "\"");
			pos += 2;
		}
		else if(test[pos] == '\'')
		{
			test.insert(pos, "'");
			pos += 2;
		}
		else
		{
			++pos;
		}
	}
	vector<string>v;
	{
		A a(&v);
		a.f();
	}
	Environment* env = Environment::createEnvironment(Environment::OBJECT);
	//string name = "system";
	//string pass = "123";
	//string srvName = "localhost:1521/orcl";
	string name = "lumingyang";
	string pass = "lu123456";
	string srvName = "121.36.15.2:55446/orcl";
	try {
		oracle::occi::Map* mapOCCI_ = env->getMap();//需要Environment::OBJECT,没有按对象模式进行初始化
		mapOCCI_->put("LUMINGYANG", "PERSON", &CAddress::readSQL, &CAddress::writeSQL);//未找到类型 "SYSTEM"."ADDRESS8"
		//mapOCCI_->put("SYSTEM", "MAN", &CAddress::readSQL, &CAddress::writeSQL);
		Connection* conn = env->createConnection(name, pass, srvName);//用户名，密码，数据库名
		/* Call the OTT generated function to register the mappings */
		/* create a persistent object of type ADDRESS in the database table,
		   ADDR_TAB */
		   //Statement* st = conn->createStatement("select ref(a) from addr_tab a");
		AnyData any{conn};
		any.setFromString("123");
		any.setFromString("456");
		auto r1 = any.getAsString();
		CAddress* addr1 = new(conn, "PERSON_TBL") CAddress(1, "1");//对象不存在或标记为删除
		//CAddress* addr1 = new CAddress(1, "lumia");
		conn->commit();
		Statement* st = conn->createStatement("insert into test_man values(1,:1)");
		st->setAutoCommit(true);

		//auto commit = st->getAutoCommit();
		//st->setInt(1, 1);
		st->setObject(1, addr1);//需要Environment::OBJECT,需要注册读写方法,读/写 SQL 的方法未注册
		auto ret = st->executeUpdate();
		ResultSet* rs = st->executeQuery("select * from test_man");
		if (rs->next())
		{
			//rs->getObject(1);//readSQL
			auto a = (CAddress*)rs->getObject(2);//readSQL
			cout << a->getState() << endl;
			cout << a->getZip() << endl;
			//r1 = rs->getRef(1);
			//auto b = r1->isNull();//只要使用r1->，就会调用readSQL
			//auto a1 = r1->getState();
			//auto a2 = r1->getZip();
		}
		st->closeResultSet(rs);
		conn->terminateStatement(st);
		env->terminateConnection(conn);
	}

	catch (SQLException x)

	{
		cout << x.what() << endl;
	}
	Environment::terminateEnvironment(env);
	return 0;
}