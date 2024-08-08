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
    char msgBuf[100] = { 0 };
    string strSqlSelect = "select * from gp_dupchk";
    string strSqCreate = "create table gp_dupchk(hash_id varchar(32) not null,"
        "file_nm varchar(64),"
        "cdr_item number(10),"
        "call_start_dt number(8) not null,"
        "primary key(hash_id) )";

    string strSqDrop = "drop table if exists gp_dupchk";
    string strSqlInsert = "insert into gp_dupchk values( :1, :2, :3, :4 )";
    unsigned int ret = 0;

    Connection* conn = env->createConnection(name, pass, srvName);//用户名，密码，数据库名
    try
    {

        /* 在OCCI连接对象下创建一个语句对象 */
        pStmt = conn->createStatement();

        /* 关联一条SQL语句到该语句对象 */
        //pStmt->setSQL(strSqDrop);
        /* 执行非查询语句 */
        //pStmt->executeUpdate();
        /* 关联另一条SQL语句到该语句对象 */
        //pStmt->setSQL(strSqCreate);
        //ret = pStmt->executeUpdate();
        pStmt->setMaxIterations(MAX_ARRAYSIZE);

        pStmt->setSQL(strSqlInsert);

        /* 设置迭代最大行数 */
        /* 设置绑定参数的最大大小 */
        pStmt->setMaxParamSize(1, 32);
        pStmt->setMaxParamSize(2, 64);
        pStmt->setMaxParamSize(3, 10);
        pStmt->setMaxParamSize(4, 20);

        for (int i = 0; i < MAX_ARRAYSIZE - 1; i++)
        {
            sprintf(msgBuf, "AAAAAA%d", i);
            /* 设置绑定参数 */
            pStmt->setString(1, msgBuf);
            pStmt->setString(2, "BBBBBB");
            pStmt->setInt(3, 1);
            pStmt->setNumber(4, Number(2));
            /* 添加到迭代器中 */
            pStmt->addIteration();
        }
        /*
         * 添加最后一行绑定参数
         * 不需要addInteration(),
         * 如果调用，将插入一个NULL行
         */
        pStmt->setString(1, "GGGGGG");
        pStmt->setString(2, "HHHHHH");
        //pStmt->setNumber(1, Number(8));//不能更改绑定数据类型
        //pStmt->setNumber(2, Number(8));
        pStmt->setInt(3, 7);
        pStmt->setNumber(4, Number(8));
        /* 执行批量插入 */
        ret = pStmt->executeUpdate();
        for (int i = 0; i < MAX_ARRAYSIZE - 1; i++)
        {
            sprintf(msgBuf, "AAABAA%d", i);
            /* 设置绑定参数 */
            pStmt->setString(1, msgBuf);
            pStmt->setString(2, "BBBBBB");
            pStmt->setInt(3, 1);
            pStmt->setNumber(4, Number(2));
            /* 添加到迭代器中 */
            pStmt->addIteration();
        }
        ret = pStmt->executeUpdate();
        /* 获取实际影响行数 */
        if (pStmt->getUpdateCount() != MAX_ARRAYSIZE) {
            cout << "batch insert failed!" << endl;
        }
        else {
            cout << "batch insert success" << endl;
        }
        cout << "insert getUpdateCount(): " << pStmt->getUpdateCount() << endl;
        /* 释放语句对象资源 */
        conn->terminateStatement(pStmt);
        pStmt = NULL;
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