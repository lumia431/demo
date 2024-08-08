#include <iostream>
#include <string.h>
#include <algorithm>
#include <string>
#include <vector>
#include <time.h>
#include <occi.h>
#define MAX_ARRAYSIZE 100
using namespace std;
using namespace::oracle::occi;

int main()
{
	float f = 3.1415;
	double d = 6.6789;
	memcpy(&f, &d, 4);
	Environment* env = Environment::createEnvironment(Environment::OBJECT);
	string name = "system";
	string pass = "123";
	string srvName = "localhost:1521/orcl";
	//string name = "lumingyang";
	//string pass = "lu123456";
	//string srvName = "121.36.15.2:55446/orcl";
	Statement* pStmt = NULL;
	ResultSet* pRs = NULL;

	Connection* conn = env->createConnection(name, pass, srvName);//用户名，密码，数据库名
	try
	{
		/*
			总结来说，MetaData::ATTR_OBJ_NAME 用于获取数据库对象（如表、视图）的名称，
			而 MetaData::ATTR_NAME 用于获取数据库对象的属性（如列、类型）的名称。
		*/

		/* 在OCCI连接对象下创建一个语句对象 */
		pStmt = conn->createStatement();
		auto metaData = conn->getMetaData("TEST_ADDRESS");
		//cout << metaData.getInt(MetaData::ATTR_DATA_SIZE) << endl;//Illegal attribute passed
		auto data = metaData.getVector(MetaData::ATTR_LIST_COLUMNS);
		auto d = data[1].getString(MetaData::ATTR_NAME);//COL1
		auto d2 = data[1].getString(MetaData::ATTR_TYPE_NAME);//2
		//cout << data[0].getInt(MetaData::ATTR_NAME) << endl;// Attribute type is not appropriate
		cout << data[0].getString(MetaData::ATTR_TYPE_NAME) << endl;//系统自带的类型获取的字符串为空
		cout << data[0].getInt(MetaData::ATTR_DATA_SIZE) << endl;
		metaData = conn->getMetaData(d2);//PTYPE_TYPE
		cout << metaData.getString(MetaData::ATTR_NAME) << endl;
		auto d3 = metaData.getVector(MetaData::ATTR_LIST_TYPE_ATTRS);//COL1
		for (auto& dd : d3)
		{
			auto d4 = dd.getInt(MetaData::ATTR_PTYPE);//PTYPE_TYPE_ATTR
			cout << dd.getString(MetaData::ATTR_NAME) << endl;//自定义类型的属性（如年龄、姓名）
			cout << dd.getString(MetaData::ATTR_TYPE_NAME) << endl;//自定义类型的属性获取的不为空，为CHAR
			cout << dd.getInt(MetaData::ATTR_CHAR_SIZE) << endl;//自定义类型的属性获取的不为空，为CHAR
			cout << metaData.getBoolean(MetaData::ATTR_IS_NULL) << endl;

		}
		auto rs = pStmt->executeQuery("select *from tbl_01");
		auto m = rs->getColumnListMetaData();
		for (auto& mm : m)
		{
			cout << mm.getInt(MetaData::ATTR_PTYPE) << endl;//PTYPE_COL
		}
	}
	catch (SQLException& ex)
	{
		cout << "ErrorCode: " << ex.getErrorCode() << endl;
		cout << ex.getMessage() << endl;
		cout << "insert getUpdateCount(): " << pStmt->getUpdateCount() << endl;
	}
	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);
	cout << "iterationDemo Success" << endl;
	return 0;
}