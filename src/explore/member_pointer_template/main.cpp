#include <cstdio>

//
// Run with g++ main.cpp -o test
//

struct Test
{
public:
    int num;
    const char* string;
};

int main()
{
    Test testInstance;
    testInstance.num = 1;
    testInstance.string = "Hello World.";

    printf("Instantiated struct. \n\tNum: %d. \n\tString: %s\n",
           testInstance.num,
           testInstance.string);
}