#include <cstdio>

//
// Run with g++ main.cpp -o test
//

struct Test
{
public:
    int num;
};


int main()
{
    //
    // How to get pointer to a field of a class.
    //

    Test testInstance;
    testInstance.num = 1;
    int Test::*  ptrA = &Test::num;  // T::*
    printf("%d\n", (testInstance.*ptrA));

    // Use this pointer to point to another instance
    {
        Test testB;
        testB.num = 3;
        printf("%d\n", (testB.*ptrA));
    }

    //
    // Stripped of type information. Potentially could be used to hold all
    // pointers to each field in an array.
    // Note: No instance of the class is needed to setup these pointers.
    //
    {
        void* Test::* strippedPointer = (void* Test::*) ptrA;
        printf("Stripped Pointer:%d\n", (int)(testInstance.*strippedPointer));
    }

    //
    // Strip from the start no cast
    //
    {
        void* Test::* strippedPointer = (void* Test::*) &Test::num;  // T::*
        printf("Stripped Pointer:%d\n", (int)(testInstance.*strippedPointer));
    }
}