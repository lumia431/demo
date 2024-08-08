#pragma once
#include <exception>
#include "ptr.h"

class SQLExceptionImpl;

class SQLException : public std::exception
{
public:

	const char* what() const throw();

	virtual void setErrorCtx(void* ctx);

	SQLException();

	SQLException(const SQLException& e);

	void operator=(const SQLException& other);

	virtual ~SQLException() throw();

protected:

	Ptr<SQLExceptionImpl> ptr_;
	SQLException(SQLExceptionImpl* ptr);

	friend SQLException SQLExceptionCreate(int errorCode);
	friend SQLException SQLExceptionCreate(void* handle,
		int handleType);
	friend class BatchSQLException;
};

class SQLExceptionImpl
{
public:
	SQLExceptionImpl();
	SQLExceptionImpl(const SQLExceptionImpl& excep);
	SQLExceptionImpl& operator=(const SQLExceptionImpl&);
	~SQLExceptionImpl();
	const char* what() const throw();
	void setErrorCtx(void* ctx);

private:
	const char* ctx_;
};