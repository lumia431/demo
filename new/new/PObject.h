#pragma once
class PObject
{
public:
    PObject();
    PObject(const void* ctx);
    PObject(const PObject& obj);
    virtual ~PObject();
    PObject& operator=(const PObject& obj);
    void* operator new(size_t size);

private:

    void* objHeader_;
};