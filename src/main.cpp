#include "Application.hpp"
#include <iostream>

int main() {
    return Application(
               Interface(std::cin, std::cout)
           ).run();
}
