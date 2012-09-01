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

int main()
{
    Reflect reflect;
    reflect.AddField("num", &Test::num);
    reflect.AddField("string", &Test::string);

    //
    // Use reflection to set an int field
    //
    {
        Test testInstance;
        testInstance.num = 66;
        Field* numField = (Field*) reflect.GetField("num");
        int num = (int)numField->GetPtr(&testInstance);
        printf("NUM:%d\n", num);
        numField->SetPtr(&testInstance, (void*)10);
        num = (int)numField->GetPtr(&testInstance);
        printf("NUM AFTER SET:%d\n", num);
    }


    //
    // Use reflection to get an int field
    //
    {
        Test testInstance;
        testInstance.num = 66;
        Field* numField = (Field*) reflect.GetField("num");
        int num = (int)numField->GetPtr(&testInstance);
        printf("NUM:%d\n", num);
    }



    //
    // Use reflection to print out the class fields and values
    //
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