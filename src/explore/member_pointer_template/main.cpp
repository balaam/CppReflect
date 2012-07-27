#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
//
// Run with g++ main.cpp -o test
//

struct Test
{
public:
    int num;
    const char* string;
};

// 1. First go, but having thrown the type away
//    I was stuck
// template<class T>
// class Field
// {
// private:
//     const char* mName;
//     void* T::* mPointer;
// public:
//     const char* Name() { return mName; }
//     Field(const char* name, void* T::* pointer) :
//         mName(name),
//         mPointer(pointer)
//     {}
// };

// Abstract class, so children can have various types
// We can have a list of abstract classes
class Field
{
public:
    virtual ~Field() {}
    const char* Name() const { return mName; }
    // This could be reflect ... probably!
    virtual std::string ToString(void* instance) const = 0;
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
    TYPE CLASS::* mPointer;
public:
    FieldImpl(const char* name,  TYPE CLASS::* pointer):
        Field(name),
        mPointer(pointer)
        {}

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


// You couldn't have an array of these
// But if they implemented an interface
// you could
template<typename T>
class Reflect
{
public:
    std::vector< Field* > mFields;

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
};



int main()
{
    Reflect<Test> reflect;
    reflect.AddField("num", &Test::num);
    reflect.AddField("string", &Test::string);

    {
        Test testInstance;
        testInstance.num = 1;
        testInstance.string = "Hello World.";

        printf("Instantiated struct. \n\tNum: %d. \n\tString: %s\n",
               testInstance.num,
               testInstance.string);

        reflect.Print(&testInstance);
    }

    {
        Test testInstance;
        testInstance.num = 2;
        testInstance.string = "Second test.";
        reflect.Print(&testInstance);
    }
}