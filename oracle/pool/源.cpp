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
	string name = "c##lumia";
	string pass = "123";
	string srvName = "localhost:1521/orcl";
	//string name = "lumingyang";
	//string pass = "lu123456";
	//string srvName = "121.36.15.2:55446/orcl";
	Statement* pStmt = NULL;
	ResultSet* pRs = NULL;
	Connection* conn = NULL;
	try
	{
		auto pool = env->createConnectionPool("SYSTEM", "123", srvName);
		conn = pool->createConnection(name, pass);
		auto stmt = conn->createStatement();
		auto rs = stmt->executeQuery("select user from dual");
		rs->next();
		auto user = rs->getString(1);
	}
	catch (SQLException& ex)
	{
		cout << "ErrorCode: " << ex.getErrorCode() << endl;
		cout << ex.getMessage() << endl;
	}
	env->terminateConnection(conn);
	Environment::terminateEnvironment(env);
	return 0;
}