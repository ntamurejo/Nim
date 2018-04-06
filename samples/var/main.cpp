#include <iostream>
#include "foo.h"
#include "jsonFile.h"

const std::string JSON_FILE = "/Users/ntamurejo/Proyectos/Json/jsonmanual.json";

int main()
{
    std::cout << "Main..."<< std::endl;
    Foo foo;
    foo.test();
    
    jsonFileNamespace::jsonReader fileJSON;
    fileJSON.readFileJSONFromPath(JSON_FILE);

    
    
    return 0;
}
