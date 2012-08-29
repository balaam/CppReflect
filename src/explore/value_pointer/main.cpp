#include <cstdio>
#include <vector>
#include <string>
#include <sstream>

#include "Reflect.h"

struct Test
{
public:
    int num;
    const char* string;
};

// What I'd like to do
//
// Reflect reflect(Test())
// reflect.AddField("num", &Test::num)
//
// Test t;
// t.num = 12;
//
//
//
// int* num = (int*)reflect.GetPtr(t,"num");

// void* Reflect::GetPtr(T instance, "num")
// {
//     foreach field do
//       if field.name == "num" then
//           return field:GetPtr(instance)
//     return null;
// }
//
// But all fields are abstract
// The parent class is not templated
// Templated functions can't be overload!
// Could cast it to it's base
// Field f;
// var stripped = FieldImpl<Test, int>(f)
// But then I'd need a second type :(
//
// I could take in a meta class and work from there
// GetPointer(Reflect f, "num")
// But that needs to wrap the original type up!
// Which brings me back to what I was doing eariler.

// Next steps look at the handler
// and implement something simialr
// Look particularly at the inner class
// template specialisation implementations

//
// // Prints 12 from the pointer
// print("%d", num);
//
//


int main()
{
    Test t;
    Reflect reflect(t);
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