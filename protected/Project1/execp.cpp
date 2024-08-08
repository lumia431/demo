#include <iostream>
#include <string.h>
#include "execp.h"


SQLExceptionImpl::SQLExceptionImpl()
{
    ctx_ = new char[4];
    auto a = "123";
    strcpy((char*)ctx_, a);
}

SQLExceptionImpl::~SQLExceptionImpl()
{
    delete ctx_;
}

SQLExceptionImpl::SQLExceptionImpl(const SQLExceptionImpl& excep)
{
    if (excep.ctx_)
    {
        int len = strlen(excep.ctx_);
        ctx_ = new char[len + 1];
        strcpy((char*)ctx_, excep.ctx_);
    }
    else
    {
        ctx_ = nullptr;
    }
}

SQLExceptionImpl& SQLExceptionImpl::operator=(const SQLExceptionImpl& excep)
{
    if (this != &excep)
    {
        if (ctx_ != nullptr)
        {
            delete ctx_;
        }
        if (!excep.ctx_)
        {
            ctx_ = nullptr;
        }
        int len = strlen(excep.ctx_);
        ctx_ = new char[len + 1];
        strcpy((char*)ctx_, excep.ctx_);
    }
    return *this;
}

const char* SQLExceptionImpl::what() const throw()
{
    return ctx_;
}

void SQLExceptionImpl::setErrorCtx(void* ctx)
{
    if (ctx_ != nullptr)
    {
        delete ctx_;
    }
    char* ptr = static_cast<char*>(ctx);
    int len = strlen(ptr);
    ctx_ = new char[len + 1];
    strcpy((char*)ctx_, ptr);
}


const char* SQLException::what() const throw()
{
    return ptr_->what();
}

void SQLException::setErrorCtx(void* ctx)
{
    ptr_->setErrorCtx(ctx);
}

SQLException::SQLException()
{
    SQLExceptionImpl excep;
    ptr_ = &excep;
}

SQLException::SQLException(const SQLException& e)
{
    ptr_ = e.ptr_;
}

void SQLException::operator=(const SQLException& other)
{
    if (this != &other)
    {
        ptr_ = other.ptr_;
    }
}

SQLException::~SQLException() throw()
{
}

