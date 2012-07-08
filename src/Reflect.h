#ifndef REFLECT_H
#define REFLECT_H

#include <map>
#include <string>
#include "ReflectType.h"

class Reflect
{
public:
    // This odd bit of code ensures the class instance in intialised first
    // The instance is a global, scoped to the function which will remain
    // in memory until the program is closed.
    static Reflect& Instance()
    {
        static Reflect instance;
        return instance;
    }

    template <typename TYPE>
    ReflectType* CreateType(const std::string& name);

private:
    std::map<std::string, ReflectType*> mTypeMap;
private:
    // This is a singleton, so hide constructor related methods.
    Reflect() {};
    ~Reflect() {};
    Reflect(Reflect const&) {};
    Reflect& operator=(Reflect const&){return Reflect::Instance();}
};

template <typename TYPE> void ConstructObject(void* object)
{
    // Placement new to call the constructor
    new (object) TYPE;
}

template <typename TYPE> void DestructObject(void* object)
{
    // Explicit call of the destructor
    ((TYPE*)object)->TYPE::~TYPE();
}

template <typename TYPE>
ReflectType* Reflect::CreateType(const std::string& name)
{
    return new ReflectType(name);
}

#endif