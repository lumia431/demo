#include "PObject.h"

PObject::PObject()
{
}

PObject::PObject(const void* ctx)
{
}

PObject::PObject(const PObject& obj)
{
}

PObject::~PObject()
{
}

PObject& PObject::operator=(const PObject& obj)
{
	// TODO: 在此处插入 return 语句
	return *this;
}

void* PObject::operator new(size_t size)
{
	return nullptr;
}
