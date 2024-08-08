#ifndef DEMO2_ORACLE
# define DEMO2_ORACLE

#ifndef OCCI_ORACLE
# include <occi.h>
#endif

using namespace std;
using namespace oracle::occi;

/* GENERATED DECLARATIONS FOR THE ADDRESS OBJECT TYPE. */
class CAddress : public oracle::occi::PObject {

private:
    int STATE;
    OCCI_STD_NAMESPACE::string ZIP;

public:
    int getState() const;
    void setState(const int& value);
    OCCI_STD_NAMESPACE::string getZip() const;
    void setZip(const OCCI_STD_NAMESPACE::string& value);
    void* operator new(size_t size);
    void* operator new(size_t size, const oracle::occi::Connection* sess,
        const OCCI_STD_NAMESPACE::string& table);
    void* operator new(size_t, void* ctxOCCI_);
    void* operator new(size_t size, const oracle::occi::Connection* sess,
        const OCCI_STD_NAMESPACE::string& tableName,
        const OCCI_STD_NAMESPACE::string& typeName,
        const OCCI_STD_NAMESPACE::string& tableSchema,
        const OCCI_STD_NAMESPACE::string& typeSchema);
    string  getSQLTypeName() const;
    void getSQLTypeName(oracle::occi::Environment* env, void** schemaName,
        unsigned int& schemaNameLen, void** typeName,
        unsigned int& typeNameLen) const;
    CAddress();
    CAddress(int state_i, string zip_i);
    CAddress(void* ctxOCCI_) : oracle::occi::PObject(ctxOCCI_) { };
    static void* readSQL(void* ctxOCCI_);
    virtual void readSQL(oracle::occi::AnyData& streamOCCI_);
    static void writeSQL(void* objOCCI_, void* ctxOCCI_);
    virtual void writeSQL(oracle::occi::AnyData& streamOCCI_);
    ~CAddress();
};

// declarations for the MyAddress class.
//class MyAddress : public CAddress
//{
//public:
//    MyAddress(string state_i, string zip_i);
//    void displayInfo();
//    MyAddress(void* ctxOCCI_);
//};

/* changes end here */
#endif