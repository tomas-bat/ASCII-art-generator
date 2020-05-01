#include "Application.hpp"
#include <iostream>

using namespace std;

int main() {
    return Application(
               Interface(cin, cout)
           ).run();
}
