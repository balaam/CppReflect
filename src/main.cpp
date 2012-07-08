#include <cstdio>
#include "Reflect.h"
#include "ReflectType.h"
#include "Example.h"

int main()
{
    printf("Hello\n");
    ReflectType * t = Reflect::Instance().CreateType<Example>("Example");
    printf("%s\n", t->Name().c_str());
    Example* e  = (Example*)t->Create();
    printf("%s\n", e->Test());
    // What do want to happen?
    // Want to get a type descriptor
    // const Meta<Example>& meta = Reflect.Instance():GetMeta("Example")
    // Example* e = meta.Construct();

    // Also would be good to clone
    // Example e* somexaplme;
    // Example e2* someexample.meta.Clone();
}