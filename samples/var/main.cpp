#include <iostream>
#include "foo.h"

int main()
{
    std::cout << "Main..."<< std::endl;
    Foo foo;
    foo.test();
    
    return 0;
}
