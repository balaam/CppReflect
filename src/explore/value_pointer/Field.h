#ifndef FIELD_H
#define FIELD_H

#include "Reflect.h"

// Meta information about a field in a class.
// Field is an abstract class.
// Fields can be different types,
// The field type information is kept in a child class


class Field
{
public:
    virtual ~Field() {}
    const char* Name() const { return mName; }
    // This could be reflect ... probably!
    virtual std::string ToString(void* instance) const = 0;
    virtual void* GetPtr(void* instance) { return NULL; }
protected:
    Field(const char* name)  :
        mName(name) {}
private:
    const char* mName;
};


template<typename CLASS, typename TYPE>
class FieldImpl : public Field
{
private:
    // This points to the field, given an instance object
    TYPE CLASS::* mPointer;
public:
    FieldImpl(const char* name,  TYPE CLASS::* pointer):
        Field(name),
        mPointer(pointer)
        {}


    virtual void* GetPtr(void* instance)
    {
        CLASS* typedInstance = static_cast<CLASS*>(instance);
        return (void*)((*typedInstance).*mPointer);
    }

    virtual std::string ToString(void* instance) const
    {
        // Throwing away the type can be avoided
        // but this works as proof of concept.
        CLASS* typedInstance = (CLASS*) instance;
        std::stringstream ss;
        ss << "[" << Name() << "]: "
        << (*typedInstance).*mPointer;
        return ss.str();
    }

};

#endif