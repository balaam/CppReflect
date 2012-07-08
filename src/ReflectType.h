#ifndef REFLECTTYPE_H
#define REFLECTTYPE_H

typedef void (*ConstructObjectFunc)(void*);
typedef void (*DestructObjectFunc)(void*);

class ReflectType
{
public:
    ReflectType(const std::string& name) {}
private:
    std::string mName;
    ConstructObjectFunc mConstructor;
    DestructObjectFunc mDestructor;
};

#endif

