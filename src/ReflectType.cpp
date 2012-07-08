#include "ReflectType.h"

ReflectType::ReflectType(const std::string& name,
                        ConstructObjectFunc ctor,
                        DestructObjectFunc dtor,
                        int size)
{
    mName = name;
    mConstructor = ctor;
    mDestructor = dtor;
    mSize = size;
}

void* ReflectType::Create() const
{
    void* obj = (void*)malloc(mSize);
    mConstructor(obj);
    return obj;
};