#define CLASS() class __attribute__((annotate("reflect-class")))
#define PROPERTY() __attribute__((annotate("reflect-property")))

#include <string>
#include <vector>

CLASS() User
{
public:
    PROPERTY()
    int id;

    PROPERTY();
    std::string name;
    
    PROPERTY();
    std::vector<std::string> pets;
};
