#ifndef DEMO2_ORACLE
# include "demo2.h"
#endif
#include <iostream>
/* GENERATED METHOD IMPLEMENTATIONS FOR THE ADDRESS OBJECT TYPE. */
int CAddress::getState() const
{
	return STATE;
}

void CAddress::setState(const int& value)
{
	STATE = value;
}

OCCI_STD_NAMESPACE::string CAddress::getZip() const
{
	return ZIP;
}

void CAddress::setZip(const OCCI_STD_NAMESPACE::string& value)
{
	ZIP = value;
}

void* CAddress::operator new(size_t size)
{
	return oracle::occi::PObject::operator new(size);
}

void* CAddress::operator new(size_t size,
	const oracle::occi::Connection* sess,
	const OCCI_STD_NAMESPACE::string& table)
{
	return oracle::occi::PObject::operator new(size, sess, table,
		(char*)"LUMINGYANG.PERSON");
}

void* CAddress::operator new(size_t size, void* ctxOCCI_)
{
	return oracle::occi::PObject::operator new(size, ctxOCCI_);
}

void* CAddress::operator new(size_t size,
	const oracle::occi::Connection* sess,
	const OCCI_STD_NAMESPACE::string& tableName,
	const OCCI_STD_NAMESPACE::string& typeName,
	const OCCI_STD_NAMESPACE::string& tableSchema,
	const OCCI_STD_NAMESPACE::string& typeSchema)
{
	return oracle::occi::PObject::operator new(size, sess, tableName,
		typeName, tableSchema, typeSchema);
}

OCCI_STD_NAMESPACE::string CAddress::getSQLTypeName() const
{
	return OCCI_STD_NAMESPACE::string("HR.ADDRESS");
}

void CAddress::getSQLTypeName(oracle::occi::Environment* env,
	void** schemaName,
	unsigned int& schemaNameLen,
	void** typeName,
	unsigned int& typeNameLen) const
{
	PObject::getSQLTypeName(env, &CAddress::readSQL, schemaName,
		schemaNameLen, typeName, typeNameLen);
}

CAddress::CAddress()
{
}

/* initialize MyAddress */
CAddress::CAddress(int state_i, string zip_i)
{
	setState(state_i);
	setZip(zip_i);
}

void* CAddress::readSQL(void* ctxOCCI_)
{
	CAddress* objOCCI_ = new(ctxOCCI_) CAddress(ctxOCCI_);
	oracle::occi::AnyData streamOCCI_(ctxOCCI_);
	try
	{
		if (streamOCCI_.isNull())
			objOCCI_->setNull();
		else
			objOCCI_->readSQL(streamOCCI_);
	}
	catch (oracle::occi::SQLException& excep)
	{
		delete objOCCI_;
		excep.setErrorCtx(ctxOCCI_);
		return (void*)NULL;
	}
	return (void*)objOCCI_;
}

void CAddress::readSQL(oracle::occi::AnyData& streamOCCI_)
{
	STATE = streamOCCI_.getNumber();
	ZIP = streamOCCI_.getString();
}

void CAddress::writeSQL(void* objectOCCI_, void* ctxOCCI_)
{
	CAddress* objOCCI_ = (CAddress*)objectOCCI_;
	oracle::occi::AnyData streamOCCI_(ctxOCCI_);

	try
	{
		if (objOCCI_->isNull())
			streamOCCI_.setNull();
		else
			objOCCI_->writeSQL(streamOCCI_);
	}
	catch (oracle::occi::SQLException& excep)
	{
		excep.setErrorCtx(ctxOCCI_);
	}
	return;
}

void CAddress::writeSQL(oracle::occi::AnyData& streamOCCI_)
{
	streamOCCI_.setNumber(STATE);
	streamOCCI_.setString(ZIP);
}

CAddress::~CAddress()
{
	int i;
}

///* initialize MyAddress */
//MyAddress::MyAddress(string state_i, string zip_i)
//{
//    setState(state_i);
//    setZip(zip_i);
//}
//
///* display all the information in MyAddress */
//void MyAddress::displayInfo()
//{
//    cout << "STATE is" << getState() << endl;
//    cout << "ZIP is" << getZip() << endl;
//}
//
//MyAddress::MyAddress(void* ctxOCCI_) :CAddress(ctxOCCI_)
//{
//}
