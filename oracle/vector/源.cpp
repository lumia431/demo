/* Copyright (c) 2001, 2010, Oracle and/or its affiliates.
All rights reserved. */
/*
   NAME
     occicoll.cpp - OCCI Collections Demo

   DESCRIPTION
     To exhibit simple insert, delete & update operations on table
     having a Nested Table column

   MODIFIED   (MM/DD/YY)
   mvasudev    09/26/10 - Remove HR schema and use SCOTT
   sudsrini    10/22/06 - Username/Password lower case
   sudsrini    07/22/04 - Copyright Info
   idcqe       03/05/01 - Creation

*/

#include <iostream>
#include <string.h>
#include <algorithm>
#include <occi.h>
using namespace oracle::occi;
using namespace std;
const char* SCHEMA = "SYSTEM";
const char* TYPENAME = "SYSTEM.JOURNAL";
typedef vector<string> journal;
const char* dbname = "127.0.0.1/orcl";
const char* user = "SYSTEM";
const char* pwd = "123";
class Journal : public PObject
{

private:
    vector<char*> journal_;

public:
    vector<string> getJournal() const;
    void setJournal(const vector<string>& value);
    void* operator new(size_t size);
    void* operator new(size_t size, const Connection* sess,
        const string& table);
    void* operator new(size_t, void* ctxOCCI_);
    void* operator new(size_t size, const Connection* sess,
        const string& tableName,
        const string& typeName,
        const string& tableSchema,
        const string& typeSchema);
    void operator delete(void* ptr, size_t size);
    string getSQLTypeName() const;
    void getSQLTypeName(Environment* env, void** schemaName,
        unsigned int& schemaNameLen, void** typeName,
        unsigned int& typeNameLen) const;
    Journal();
    Journal(int age, string name);
    Journal(void* ctxOCCI_) : PObject(ctxOCCI_) {};
    static void* readSQL(void* ctxOCCI_);
    virtual void readSQL(AnyData& streamOCCI_);
    static void writeSQL(void* objOCCI_, void* ctxOCCI_);
    virtual void writeSQL(AnyData& streamOCCI_);
    ~Journal();
};

vector<string> Journal::getJournal() const
{
    // return journal_;
}

void Journal::setJournal(const vector<string>& value)
{
    // journal_ = value;
}

void* Journal::operator new(size_t size)
{
    return PObject::operator new(size);
}

void* Journal::operator new(size_t size,
    const Connection* sess,
    const string& table)
{
    return PObject::operator new(size, sess, table, (char*)TYPENAME);
}

void* Journal::operator new(size_t size, void* ctxOCCI_)
{
    return PObject::operator new(size, ctxOCCI_);
}

void* Journal::operator new(size_t size,
    const Connection* sess,
    const string& tableName,
    const string& typeName,
    const string& tableSchema,
    const string& typeSchema)
{
    return PObject::operator new(size, sess, tableName, typeName, tableSchema, typeSchema);
}

string Journal::getSQLTypeName() const
{
    return "";
}

void Journal::operator delete(void* ptr, size_t size)
{
    PObject::operator delete(ptr, size);
}

void Journal::getSQLTypeName(Environment* env,
    void** schemaName,
    unsigned int& schemaNameLen,
    void** typeName,
    unsigned int& typeNameLen) const
{
    PObject::getSQLTypeName(env, &Journal::readSQL, schemaName,
        schemaNameLen, typeName, typeNameLen);
}

Journal::Journal()
{
}

void* Journal::readSQL(void* ctxOCCI_)
{
    Journal* objOCCI_ = new (ctxOCCI_) Journal(ctxOCCI_);
    AnyData streamOCCI_(ctxOCCI_);
    try
    {
        if (!streamOCCI_.isNull())
        {
            objOCCI_->readSQL(streamOCCI_);
        }
    }
    catch (SQLException& excep)
    {
        delete objOCCI_;
        return (void*)NULL;
    }
    return (void*)objOCCI_;
}

void Journal::readSQL(AnyData& streamOCCI_)
{
    // journal_ = streamOCCI_.getString();
}

void Journal::writeSQL(void* objectOCCI_, void* ctxOCCI_)
{
    Journal* objOCCI_ = (Journal*)objectOCCI_;
    AnyData streamOCCI_(ctxOCCI_);

    try
    {
        if (!streamOCCI_.isNull())
        {
            objOCCI_->writeSQL(streamOCCI_);
        }
    }
    catch (SQLException& excep)
    {
        return;
    }
    return;
}

void Journal::writeSQL(AnyData& streamOCCI_)
{
    // streamOCCI_.setString(journal_);
}

Journal::~Journal()
{
    int i;
}

class occicoll
{
private:
    Environment* env;
    Connection* conn;
    Statement* stmt;
    string tableName;
    string typeName;

public:
    occicoll(string user, string passwd, string db)
    {
        env = Environment::createEnvironment(Environment::OBJECT);
        conn = env->createConnection(user, passwd, db);
    }

    ~occicoll()
    {
        env->terminateConnection(conn);
        Environment::terminateEnvironment(env);
    }

    void setTableName(string s)
    {
        tableName = s;
    }

    void createTable()
    {
    }

    /**
     * Insertion of a row
     */
    void insertRow()
    {
        int c1 = 11;
        journal c2;

        c2.push_back((char*)"LIFE");
        c2.push_back((char*)"TODAY");
        c2.push_back((char*)"INVESTOR");

        cout << "Inserting row with jid = " << 11 << " and journal_tab (LIFE, TODAY, INVESTOR )" << endl;
        try
        {
            stmt = conn->createStatement(
                "INSERT INTO journal_tab (jid, jname) VALUES (:x, :y)");
            stmt->setInt(1, c1);
            setVector(stmt, 2, c2, "JOURNAL");
            stmt->executeUpdate();
        }
        catch (SQLException ex)
        {
            cout << "Exception thrown for insertRow" << endl;
            cout << "Error number: " << ex.getErrorCode() << endl;
            cout << ex.getMessage() << endl;
        }
        cout << "Insertion - Successful" << endl;
        conn->terminateStatement(stmt);
    }

    // Displaying all the rows of the table
    void displayAllRows()
    {
        auto stmtCreate = conn->createStatement();
        stmtCreate->executeUpdate("DECLARE num NUMBER; \
							BEGIN \
							SELECT \
								count( 1 ) INTO num \
							FROM \
								user_tables \
							WHERE \
								table_name = upper( 'journal_test' ); \
							IF \
								num > 0 THEN \
								execute IMMEDIATE 'drop table journal_test'; \
							END IF; \
							END;");
        stmtCreate->executeUpdate("DECLARE num NUMBER; \
							BEGIN \
							SELECT \
								count( 1 ) INTO num \
							FROM \
								user_tables \
							WHERE \
								table_name = upper( 'journal_store' ); \
							IF \
								num > 0 THEN \
								execute IMMEDIATE 'drop table journal_store'; \
							END IF; \
							END;");
        stmtCreate->executeUpdate("DECLARE num NUMBER; \
							BEGIN \
							SELECT \
								count( 1 ) INTO num \
							FROM \
								user_tables \
							WHERE \
								table_name = upper( 'journal' ); \
							IF \
								num > 0 THEN \
								execute IMMEDIATE 'drop type journal'; \
							END IF; \
							END;");

        stmtCreate->executeUpdate("CREATE OR REPLACE TYPE journal AS VARRAY(3) OF VARCHAR2(50)");
        // stmtCreate->executeUpdate("create table journal_tbl of journal");
        stmtCreate->executeUpdate("CREATE TABLE journal_test (jid NUMBER, jname journal)");
        stmtCreate->executeUpdate("INSERT INTO journal_test (jid, jname) VALUES (22, journal ('NATION', 'TIMES'))");
        stmtCreate->executeUpdate("INSERT INTO journal_test (jid, jname) VALUES (33, journal ('CRICKET', 'ALIVE'))");
        cout << "Displaying all the rows of the table" << endl;
        stmt = conn->createStatement(
            "SELECT jid, jname FROM journal_test order by jid");
        env = Environment::createEnvironment(Environment::OBJECT);
        Map* mapOCCI_ = env->getMap();
        mapOCCI_->put(SCHEMA, "JOURNAL", &Journal::readSQL, &Journal::writeSQL);
        conn = env->createConnection(user, pwd, dbname);
        journal c2;

        ResultSet* rs = stmt->executeQuery();
        try
        {
            while (rs->next())
            {
                cout << "jid: " << rs->getInt(1) << endl;
                cout << "jname: ";
                getVector(rs, 2, c2);
                for (int i = 0; i < c2.size(); ++i)
                    cout << c2[i] << " ";
                cout << endl;
            }
        }
        catch (SQLException ex)
        {
            cout << "Exception thrown for displayRow" << endl;
            cout << "Error number: " << ex.getErrorCode() << endl;
            cout << ex.getMessage() << endl;
        }
        stmt->closeResultSet(rs);
        conn->terminateStatement(stmt);

    } // End of displayAllRows()

    // Deleting a row of the nested table of strings
    void deleteRow(int c1, string str)
    {
        cout << "Deleting a row of the nested table of strings" << endl;
        stmt = conn->createStatement(
            "SELECT jname FROM journal_test WHERE jid = :x");
        journal c2;
        stmt->setInt(1, c1);

        ResultSet* rs = stmt->executeQuery();
        try
        {
            if (rs->next())
            {
                getVector(rs, 1, c2);
                c2.erase(find(c2.begin(), c2.end(), str));
            }
            stmt->closeResultSet(rs);

            stmt->setSQL("UPDATE journal_test SET jname = :x WHERE jid = :y");
            stmt->setInt(2, c1);
            setVector(stmt, 1, c2, "JOURNAL");
            stmt->executeUpdate();
        }
        catch (SQLException ex)
        {
            cout << "Exception thrown for delete row" << endl;
            cout << "Error number: " << ex.getErrorCode() << endl;
            cout << ex.getMessage() << endl;
        }

        cout << "Deletion - Successful" << endl;
        conn->commit();
        conn->terminateStatement(stmt);
    } // End of deleteRow (int, string)

    // Updating a row of the nested table of strings
    void updateRow(int c1, string str)
    {
        cout << "Updating a row of the nested table of strings" << endl;
        stmt = conn->createStatement(
            "SELECT jname FROM journal_test WHERE jid = :x");

        journal c2;

        stmt->setInt(1, c1);
        ResultSet* rs = stmt->executeQuery();
        try
        {
            if (rs->next())
            {
                getVector(rs, 1, c2);
                c2[0] = (char*)str.c_str();
            }
            stmt->closeResultSet(rs);

            stmt->setSQL("UPDATE journal_test SET jname = :x WHERE jid = :y");
            stmt->setInt(2, c1);
            setVector(stmt, 1, c2, "JOURNAL");
            stmt->executeUpdate();
        }
        catch (SQLException ex)
        {
            cout << "Exception thrown for updateRow" << endl;
            cout << "Error number: " << ex.getErrorCode() << endl;
            cout << ex.getMessage() << endl;
        }

        cout << "Updation - Successful" << endl;
        conn->commit();
        conn->terminateStatement(stmt);
    } // End of UpdateRow (int, string)

    void cleanup()
    {
        stmt = conn->createStatement("DELETE FROM journal_test");
        stmt->execute();
        stmt->setSQL("INSERT INTO journal_test (jid, jname) VALUES (22, journal ('NATION', 'TIMES'))");
        stmt->executeUpdate();
        stmt->setSQL("INSERT INTO journal_test (jid, jname) VALUES (33, journal ('CRICKET', 'ALIVE'))");
        stmt->executeUpdate();
        conn->commit();
        conn->terminateStatement(stmt);
    }

}; // end of class occicoll

int main(void)
{
    const int LEN = 20 * 1024 * 1024;
    char* c = new char[LEN + 1];
    for (int i = 0; i < LEN; ++i)
    {
        c[i] = 'a';
    }
    char* c2 = new char[LEN + 1];
    strcpy(c2, c);
    try
    {
        cout << "occicoll - Exhibiting simple insert, delete & update operations"
            " on table having a Nested Table column"
            << endl;
        occicoll* demo = new occicoll(user, pwd, dbname);

        cout << "Displaying all rows before the operations" << endl;
        demo->displayAllRows();

        demo->insertRow();

        demo->deleteRow(11, "TODAY");

        demo->updateRow(33, "New_String");

        cout << "Displaying all rows after all the operations" << endl;
        demo->displayAllRows();

        demo->cleanup();
        delete (demo);
        cout << "occicoll - done" << endl;
    }
    catch (SQLException ea)
    {
        cerr << "Error running the demo: " << ea.getMessage() << endl;
    }
}
