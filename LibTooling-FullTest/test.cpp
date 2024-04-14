#include <iostream>

struct X { int i; };

int y = 0;

int foo(const X& x, char c, double d) {
    int i=2;

    std::cout << "Wurst" << y << std::endl;

    return x.i * i;
}


