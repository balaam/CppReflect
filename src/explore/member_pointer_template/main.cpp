#include <cstdio>
#include <vector>

//
// Run with g++ main.cpp -o test
//

struct Test
{
public:
    int num;
    const char* string;
};


template<class T>
class Field
{
private:
    const char* mName;
    void* T::* mPointer;
public:
    const char* Name() { return mName; }
    Field(const char* name, void* T::* pointer) :
        mName(name),
        mPointer(pointer)
    {}
};

// You couldn't have an array of these
// But if they implemented an interface
// you could
template<class T>
class Reflect
{
public:
    std::vector< Field<T> > mFields;

    void Print(T type)
    {
        typename std::vector< Field<T> >::iterator iter;
        for (iter = mFields.begin();
             iter != mFields.end(); ++iter)
        {
            printf("[%s]\n", iter->Name());

            // Having cast away the type
            // how do I get it back to print it! :)
        }
    }
};

// Iterate through the class and print it's members and values


int main()
{
    Test testInstance;
    testInstance.num = 1;
    testInstance.string = "Hello World.";

    printf("Instantiated struct. \n\tNum: %d. \n\tString: %s\n",
           testInstance.num,
           testInstance.string);

    Reflect<Test> reflect;

    reflect.mFields.push_back(Field<Test>(
        "Num", (void* Test::*) &Test::num));
    reflect.mFields.push_back(Field<Test>(
        "String", (void* Test::*) &Test::string));

    reflect.Print(testInstance);
}