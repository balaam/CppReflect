#ifndef REFLECT_H
#define REFLECT_H

#include <vector>
#include <cstdio>
#include "Field.h"

// You couldn't have an array of these
// But if they implemented an interface
// you could
//template<typename T>
class Reflect
{
public:
    std::vector< Field* > mFields;

public:

    template<typename T>
    void Print(T* instance)
    {
        typename std::vector< Field* >::iterator iter;
        for (iter = mFields.begin();
             iter != mFields.end(); ++iter)
        {
            printf("%s\n", (*iter)->ToString((void*)instance).c_str());
        }
    }

    template <typename CLASS, typename TYPE>
    void AddField(const char* name, TYPE CLASS::* fieldPtr)
    {
        mFields.push_back(new FieldImpl<CLASS, TYPE>(name, fieldPtr));
    }
private:
    class Holder
    {
    public:
        public: void* GetPtr() const { return NULL; }
    protected:
        Holder() {};
        ~Holder() {};
    };

    template <typename CLASS> struct HolderBase;
    template <typename CLASS> struct HolderPtr;

    Holder* mHolder;

public:
    template<typename CLASS>
    Reflect(const CLASS& _object);

    template<typename CLASS>
    Reflect(CLASS* _pObject);
};

template<typename CLASS> struct
Reflect::HolderBase : public Reflect::Holder
{
};

template<typename CLASS> struct
Reflect::HolderPtr : public Reflect::HolderBase<CLASS>
{
    HolderPtr(const CLASS* _pObject) :
        mObject(const_cast<CLASS*>(_pObject)) {}
    CLASS* mObject;
};

// Allow the holder to hold basic types
template<> struct Reflect::HolderBase<bool>           : public Reflect::Holder {};
template<> struct Reflect::HolderBase<const char>     : public Reflect::Holder {};
template<> struct Reflect::HolderBase<char>           : public Reflect::Holder {};
template<> struct Reflect::HolderBase<signed char>    : public Reflect::Holder {};
template<> struct Reflect::HolderBase<unsigned char>  : public Reflect::Holder {};
template<> struct Reflect::HolderBase<short>          : public Reflect::Holder {};
template<> struct Reflect::HolderBase<unsigned short> : public Reflect::Holder {};
template<> struct Reflect::HolderBase<int>            : public Reflect::Holder {};
template<> struct Reflect::HolderBase<unsigned int>   : public Reflect::Holder {};
template<> struct Reflect::HolderBase<long>           : public Reflect::Holder {};
template<> struct Reflect::HolderBase<unsigned long>  : public Reflect::Holder {};
template<> struct Reflect::HolderBase<float>          : public Reflect::Holder {};
template<> struct Reflect::HolderBase<double>         : public Reflect::Holder {};

template <typename CLASS>
Reflect::Reflect(const CLASS& _Object)
{
    mHolder = new HolderPtr<CLASS>(&_Object);
}


template <typename CLASS>
Reflect::Reflect(CLASS* _pObject)
{
    mHolder = new HolderPtr<CLASS>(_pObject);
}

#endif