#include <iostream>
#include "foo.h"
#include "jsonFile.h"

int main()
{
    std::cout << "Main..."<< std::endl;
    Foo foo;
    foo.test();
    
    jsonFileNamespace::jsonReader fileJSON;
    fileJSON.readFileJSONFromPath("/Users/ntamurejo/Proyectos/Json/jsonmanual.json");

    
    
    return 0;
}
