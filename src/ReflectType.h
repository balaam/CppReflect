#ifndef REFLECTTYPE_H
#define REFLECTTYPE_H
#include <string>
#include <stdlib.h>


typedef void (*ConstructObjectFunc)(void*);
typedef void (*DestructObjectFunc)(void*);

class ReflectType
{
public:
    ReflectType(const std::string& name,
                ConstructObjectFunc ctor,
                DestructObjectFunc dtor,
                int size);

    const std::string& Name() { return mName; }
    void* Create() const;
private:
    std::string mName;
    ConstructObjectFunc mConstructor;
    DestructObjectFunc mDestructor;
    int mSize;
};

#endif

