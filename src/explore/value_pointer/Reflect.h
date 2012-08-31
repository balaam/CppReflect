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

public:
    Field* GetField(const char* name) const
    {
        for (std::vector<Field*>::const_iterator iter = mFields.begin(); iter != mFields.end(); ++iter)
        {
            if((*iter)->Name() == name)
            {
                return (*iter);
            }
        }
        return NULL;
    }
};


#endif